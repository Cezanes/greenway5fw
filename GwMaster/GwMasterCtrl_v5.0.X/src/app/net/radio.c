
#include "radio.h"

#include "sal/timer.h"
#include "sal/debug.h"

#include "drv/rfm95.h"

#include "app/logic/logic.h"
#include "app/sem/chronos.h"
#include "cfg/hw_config.h"

/////////////////////////////////////////////////////////////////////////////////////////////

enum 
{
   kRmsgStatusIdle = 0,
   kRmsgStatusWaitingAck,
   kRmsgStatusBlob,
};

static const char * state_str[] = 
{
  "Idle",
  "WaitingAck",
  "Blob",
};

static struct 
{
   size_t state;
   
   bool use_timeout;
   size_t timeout_retry_count;
   uint32_t last_received_stamp;
   uint32_t request_timestamp;
   uint32_t response_timeout;
   uint32_t msg_process_period;
   
   uint8_t last_blob_id;
   
   size_t segment_size;
   uint32_t ota_header_period;
   uint32_t ota_byte_period;
   
   uint8_t * blob_buff;
   size_t blob_buff_size;
   
   const RadioConfig * radio_cfg;
   
   RmsgMessageContext msg_context;
} radio;


/////////////////////////////////////////////////////////////////////////////////////////////


static void radio_msg_ack(const RaMsgHead * msg, uint32_t size);
static void radio_msg_nack(const RaMsgHead * msg, uint32_t size);
static void radio_msg_unsupported(const RaMsgHead * msg, uint32_t size);
static void radio_msg_hello(const RaMsgHead * msg, uint32_t size);
static void radio_msg_forward(const RaMsgHead * msg, uint32_t size);
static void radio_msg_blob(const RaMsgHead * msg, uint32_t size);

static void radio_msg_net_prog(const RaMsgHead * msg, uint32_t size);
static void radio_msg_time(const RaMsgHead * msg, uint32_t size);

static void radio_blob_int_send(RaMsgHead * msg, const uint32_t size);
static void radio_blob_on_busy(const bool busy);
static void radio_blob_on_msg_recv(const RaMsgHead * msg, const uint32_t size);

static void radio_sent(uint32_t duration);
static void radio_state(const size_t state);
static void radio_activate_timeout(bool on);


/////////////////////////////////////////////////////////////////////////////////////////////


void radio_init(const NetworkConfig * radio_data, const RadioConfig * radio_cfg, const HwRadioConfig * hwcfg)
{
   radio.blob_buff = hwcfg->rx_buff;
   radio.blob_buff_size = hwcfg->rx_buff_size;
   radio.msg_process_period = radio_cfg->msg_process_period;
   radio.radio_cfg = radio_cfg;
   
   const BlobConfig blob_config = 
   {
      .buff = radio.blob_buff,
      .buff_size = radio.blob_buff_size,
      .on_recv_msg = &radio_blob_on_msg_recv,
      .on_send_msg = &radio_blob_int_send, 
      .on_busy = &radio_blob_on_busy,
      .burst_count = radio_cfg->blob_burst_count,
      .msg_process_period = radio_cfg->msg_process_period,
   };
   
   lora_init(radio_data, radio_cfg, hwcfg);
   
   lora_add_handler(kRadioMsgAck,         &radio_msg_ack);
   lora_add_handler(kRadioMsgNack,        &radio_msg_nack);
   lora_add_handler(kRadioMsgUnsupported, &radio_msg_unsupported);
   lora_add_handler(kRadioMsgHello,       &radio_msg_hello);
   lora_add_handler(kRadioMsgForward,     &radio_msg_forward);
   lora_add_handler(kRadioMsgBlob,        &radio_msg_blob);
   lora_add_handler(kRadioMsgNetwProg,    &radio_msg_net_prog);
   lora_add_handler(kRadioMsgTime,        &radio_msg_time);
   
   lora_set_cb(radio_sent);
      
   rmsg_blob_init(&blob_config);   
   radio_state(kRmsgStatusIdle);
}

void ioc_D13_change(void)
{
   lora_int_sig();
}

void radio_config(size_t index)
{
   const LoraMode * mode = lora_bandwidth(index);
   
   if(mode == NULL)
      return;
   
   radio.segment_size = mode->segment_size;
   radio.ota_byte_period = mode->ota_byte_period;
   radio.ota_header_period = mode->ota_header_period;
   
   radio.msg_process_period = app_config.radio.msg_process_period;
   
   const BlobSessionConfig blob_config = {
      .segment_size = mode->segment_size,
      .ota_byte_period = mode->ota_byte_period,
      .ota_header_period = mode->ota_header_period,
   };
   
   rmsg_blob_config(&blob_config);
}

void radio_start(void)
{
   lora_start();
   radio_config(radio.radio_cfg->bandwidth_index);
}

bool radio_is_busy(void)
{
   return (radio.state != kRmsgStatusIdle);
}

void radio_get_buff(uint8_t ** const buff, size_t * const size)
{
   *buff = radio.blob_buff;
   *size = radio.blob_buff_size;
}

uint8_t radio_get_new_blob_id()
{
   return ++radio.last_blob_id;
}

static void radio_state(const size_t state)
{
   if (radio.state != state)
   {
      DBG(kLvlVerb, "rmsg, state %s", state_str[state]);
      
      if(state == kRmsgStatusIdle)
         radio_activate_timeout(false);
   }
   
   switch(state)
   {
      case kRmsgStatusIdle:
      {
         radio.msg_context = (RmsgMessageContext){0};
         break;
      }
     
      case kRmsgStatusWaitingAck:
      {
         radio_activate_timeout(true);
         break;
      }
   }
   
   
   radio.state = state;
}

static void radio_send_ack(uint8_t dest, uint8_t cmd)
{
   RaMsgAck msg = {
     .head =  {
        .cmd = kRadioMsgAck,
        .dest = dest,
        
        
     },
     .acked_cmd = cmd,
   };
   
   lora_send(&msg.head, sizeof(msg));
}

static void radio_send_nack(uint8_t dest, uint8_t cmd, uint8_t reason)
{
   RaMsgNack msg = {
     .head =  {
        .cmd = kRadioMsgNack,
        .dest = dest,
     },
     .nacked_cmd = cmd,
     .reason = reason,
   };
   
   lora_send(&msg.head, sizeof(msg));
}

///////////////////////////////////////////////////////   Handlers   ///////////////////////////////////////////////////////


static void radio_ack_timeout(void)
{
   if (radio.state != kRmsgStatusWaitingAck)
   {
      DBG(kLvlError, "rmsg, ack timeout but not in WaitAck state (%s)", state_str[radio.state]);
      return;
   }   
   
   DBG(kLvlWarn, "rmsg, ack timeout, resending...");
   
   lora_send((RaMsgHead *)radio.blob_buff, radio.msg_context.size);
}

static void radio_ack_fail(void)
{
   if (radio.state != kRmsgStatusWaitingAck)
   {
      DBG(kLvlError, "rmsg, ack failed but not in WaitAck state (%s)", state_str[radio.state]);
      return;
   }   
   
   DBG(kLvlWarn, "rmsg, ack timeout, target unreachable");
   
   if (radio.msg_context.event)
      (*radio.msg_context.event)(radio.msg_context.id, kRmsgEventDestUnreachable);
   
   radio_state(kRmsgStatusIdle);
}

static void radio_activate_timeout(bool on)
{
   if(on)
   {
      radio.request_timestamp = timer_tick();
      radio.use_timeout = true;
      radio.timeout_retry_count = RMSG_MSG_RETRY_COUNT;
   }
   else
   {
      radio.use_timeout = false;
   }
}

static void radio_check_timeout(void)
{
   if (radio.use_timeout)
   {
      uint32_t tick = timer_tick();
      if(tick - radio.request_timestamp > radio.response_timeout)
      {
         if(radio.timeout_retry_count)
         {
            radio.timeout_retry_count--;
            radio.request_timestamp = tick;
            radio_ack_timeout();
         }
         else
         {
            radio.use_timeout = false;
            radio_ack_fail();
         }
      }
   }
}

bool radio_send_simple(RaMsgHead * msg, const uint32_t size)
{
   if (rmsg_blob_busy())
   {
      DBG(kLvlError, "rmsg, cannot send message, blob busy");
      return false;
   }
   
   if (size > LORA_MAX_MSG_SIZE)
   {
      DBG(kLvlError, "rmsg, msg size too big, use blob");
      return false;
   }
   
   lora_send(msg, size);
   
   return true;
}

bool radio_send(const RmsgMessageContext * context)
{
   if(!lora_available())
   {
      DBG(kLvlError, "rmsg, lora not available");
      return false;
   }
   
   if (context == NULL)
   {
      DBG(kLvlError, "rmsg, provided NULL rmsg context");
      return false;
   }
   
   if (rmsg_blob_busy())
   {
      DBG(kLvlError, "rmsg, cannot send message, blob busy");
      return false;
   }
   
   if (radio.state != kRmsgStatusIdle)
   {
      DBG(kLvlError, "rmsg, cannot send message, rmsg busy");
      return false;
   }
   
   uint8_t * buff;
   size_t buff_size;
      
   rmsg_blob_get_buff(&buff, &buff_size);
   
   if (context->size > buff_size)
   {
      DBG(kLvlError, "rmsg, blob send size too big %u vs %u", context->size, buff_size);
      return false;
   }
   
   radio.msg_context = *context;
   
   if(context->msg != NULL)
      memcpy(buff, context->msg, context->size);
   
   if (context->size > LORA_MAX_MSG_SIZE)
   {
      lora_prepare_send((RaMsgHead * )buff, context->size);
      return rmsg_blob_send(context);
   }
   else
   {
      radio.response_timeout = radio.ota_header_period + radio.ota_byte_period * context->size;
      radio.response_timeout += radio.ota_header_period + radio.ota_byte_period * sizeof(RaMsgAck);
      radio.response_timeout += radio.msg_process_period;
      radio.request_timestamp = timer_tick();
      lora_send(context->msg, context->size);
      radio_state(kRmsgStatusWaitingAck);
   }
   
   return true;
}

static void radio_blob_int_send(RaMsgHead * msg, const uint32_t size)
{
   lora_send(msg, size);
}

static void radio_blob_on_busy(const bool busy)
{
   if (busy)
   {
      if (radio.state != kRmsgStatusIdle)
      {
         DBG(kLvlError, "rmsg, blob got busy but not in idle %s", state_str[radio.state]);
      }
      else
      {
         radio_state(kRmsgStatusBlob);
      }
   }
   else
   {
      if (radio.state != kRmsgStatusBlob)
      {
         DBG(kLvlError, "rmsg, blob got idle but not in blob %s", state_str[radio.state]);
      }
      else
      {
         radio_state(kRmsgStatusIdle);
      }
   }
}

static void radio_blob_on_msg_recv(const RaMsgHead * msg, const uint32_t size)
{
   lora_handle_msg(msg, size);
}

static void radio_sent(uint32_t duration)
{
   if (radio.state == kRmsgStatusBlob)
   {
      rmsg_blob_msg_tx_done(duration);
   }
   else
   {
      DBG(kLvlDbg, "rmsg, msg sent %s, %u", state_str[radio.state], duration);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////


static void radio_msg_ack(const RaMsgHead * msg, uint32_t size)
{
   DBG(kLvlVerb, "rmsg, received Ack");
   
   if (radio.state == kRmsgStatusWaitingAck)
   {
      if (radio.msg_context.event)
         (*radio.msg_context.event)(radio.msg_context.id, kRmsgEventDone);
      
      radio_state(kRmsgStatusIdle);
   }
}

static void radio_msg_nack(const RaMsgHead * msg, uint32_t size)
{
   DBG(kLvlWarn, "rmsg, received Nack");
   
   if (radio.state == kRmsgStatusWaitingAck)
   {
      if (radio.msg_context.event)
         (*radio.msg_context.event)(radio.msg_context.id, kRmsgEventRefused);
      
      radio_state(kRmsgStatusIdle);
   }
}

static void radio_msg_unsupported(const RaMsgHead * msg, uint32_t size)
{
   const RaMsgUnsupported * msg_uns = (const RaMsgUnsupported * ) msg;
   DBG(kLvlWarn, "rmsg, destination does not support message %u", msg_uns->unsupported_cmd);
   
   if (radio.state == kRmsgStatusWaitingAck)
   {  
      if (radio.msg_context.event)
         (*radio.msg_context.event)(radio.msg_context.id, kRmsgEventRefused);
      
      radio_state(kRmsgStatusIdle);
   }
}

static void radio_msg_hello(const RaMsgHead * msg, uint32_t size)
{
   
}

static void radio_msg_blob(const RaMsgHead * msg, uint32_t size)
{
   rmsg_blob_handle_msg(msg, size);
}

static bool is_near(const uint8_t id)
{
   if (app_config.net.node_count == 0)
      return false;
   
   int our = -1;
   int his = -1;
   for(int i = 0; i < app_config.net.node_count; i++)
   {
      if (app_config.net.node_list[i] == app_config.net.addr_local)
      {
         our = i;
      }
      
      if (app_config.net.node_list[i] == id)
      {
         his = i;
      }
   }
   
   if (our < 0 || his < 0)
      return false;
   
   if (our < his)
   {
      return his - our == 1;
   }
   else
   {
      return our - his == 1;
   }
}

static uint8_t closest_node(const uint8_t id)
{
   if (app_config.net.node_count == 0)
      return kRadioAddrInvalid;
   
   int our = -1;
   int his = -1;
   for(int i = 0; i < app_config.net.node_count; i++)
   {
      if (app_config.net.node_list[i] == app_config.net.addr_local)
      {
         our = i;
      }
      
      if (app_config.net.node_list[i] == id)
      {
         his = i;
      }
   }
   
   if (our < 0 || his < 0)
      return kRadioAddrInvalid;
   
   if (our < his)
   {
      if (our == (int)app_config.net.node_count - 1)
         return kRadioAddrInvalid;
      our++;
   }
   else
   {
      if (our == 0)
         return kRadioAddrInvalid;
      our--;
   }
   
   return app_config.net.node_list[our];
}

static void radio_msg_forward(const RaMsgHead * msg, uint32_t size)
{
   RaMsgForward * fw = (RaMsgForward *) msg;
   
   if (fw->dest == app_config.net.addr_local)
   {
      lora_handle_msg(&(fw + 1)->head, size - sizeof(RaMsgForward));
   }
   else
   {
      if(fw->ttl > 0)
         fw->ttl++;
      
      if(!fw->ttl)
      {
         DBG(kLvlWarn, "rmsg, forward msg dropped coz ttl");
         return;
      }
      
      uint8_t next = closest_node(fw->dest);
      
      if (next != kRadioAddrInvalid)
         fw->head.dest = next;
      else fw->head.dest = fw->dest;
      
      lora_send(&fw->head, size);
   }
}

static void radio_msg_net_prog(const RaMsgHead * msg, uint32_t size)
{
   const RaMsgNetworkProg * prog_msg = (const RaMsgNetworkProg *) msg;
   
   if(size < sizeof(RaMsgNetworkProg))
   {
      radio_send_nack(msg->source, msg->cmd, kErrorSize);
      return;
   }
   
   const SignalNetwork * netw = (const SignalNetwork *) (prog_msg + 1);
   
   DBG(kLvlInfo, "rmsg, received prog network from %u", msg->source);
   
   uint8_t source = msg->source;
   size_t ret = logic_rlink_set_netw(netw);
      
   if(kOK == ret)
      radio_send_ack(source, kRadioMsgNetwProg);
   else radio_send_nack(source, kRadioMsgNetwProg, ret);
}

static void radio_msg_time(const RaMsgHead * msg, uint32_t size)
{
   const RaMsgTime * msg_timer = (const RaMsgTime *) msg;
   chronos_rad_time_upd(msg_timer->time, msg_timer->jitter);
}

void radio_service()
{
   lora_service();
   rmsg_blob_service();
   radio_check_timeout();
}