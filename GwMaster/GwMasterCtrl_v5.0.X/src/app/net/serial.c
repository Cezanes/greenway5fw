#include "serial.h"

#include "sal/debug.h"
#include "sas/server.h"
#include "app/sem/sem_objects.h"
#include "app/logic/logic.h"
#include "cfg/app_config.h"
#include "app/edge/edge_msg.h"
#include "app/edge/edge.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static struct
{
   const ServerConfig * config;
} serial;


/////////////////////////////////////////////////////////////////////////////////////////////


static void serial_msg_hello(size_t itf, const SeMsgHead * msg);
static void serial_msg_info(size_t itf, const SeMsgHead * msg);
static void serial_msg_get_sem_prog(size_t itf, const SeMsgHead * msg);
static void serial_msg_set_sem_prog(size_t itf, const SeMsgHead * msg);
static void serial_msg_get_config(size_t itf, const SeMsgHead * msg);
static void serial_msg_set_config(size_t itf, const SeMsgHead * msg);
static void serial_msg_get_time(size_t itf, const SeMsgHead * msg);
static void serial_msg_set_time(size_t itf, const SeMsgHead * msg);
static void serial_msg_set_sem_netw(size_t itf, const SeMsgHead * msg);

static void serial_msg_set_sms(size_t itf, const SeMsgHead * msg);


/////////////////////////////////////////////////////////////////////////////////////////////

/*
static void reply(size_t itf, size_t id, size_t endp)
{
   server_send(itf, NULL, 0, id, endp);
}

static void ack(size_t itf, size_t id)
{
   SeMsgAck msg = {
      .head = {
         .id = kMsgSlinkAck,
         .size = sizeof(SeMsgAck),
      },
      .acked_msg = id,
   };
   
   server_send_msg(itf, &msg.head);
}

static void nack(size_t itf, uint16_t id, size_t reason)
{
   SeMsgNack msg = {
      .head = {
         .id = kMsgSlinkNack,
         .size = sizeof(SeMsgNack),
      },
      .nacked_msg = id,
      .reason = (uint8_t)reason,
   };
   
   server_send_msg(itf, &msg.head);
}

static void serial_msg_hello(size_t itf, const SeMsgHead * msg)
{
   reply(itf, 0, kMsgSlinkHello);
}

static void serial_msg_info(size_t itf, const SeMsgHead * msg)
{
   SeMsgInfo info = {
      .head = {
         .id = kMsgSlinkInfo, 
         .size = sizeof(SeMsgInfo)
      },
      .description = "Red Spektrum Green Wave", // WTF... coz it works
      .rx_buff_size = server_rx_buff_size(),
   };
   
   server_send_msg(itf, &info.head);
}

static void serial_msg_set_sem_prog(size_t itf, const SeMsgHead * msg)
{
   const SeMsgProg * msg_prog = (const SeMsgProg *) msg;
   const SignalNetwork * netw = (const SignalNetwork *)(msg_prog + 1);
      
   size_t ret;
   if(msg_prog->remote)
      ret = logic_slink_set_remote_prog(netw);
   else ret = logic_slink_set_local_prog(netw);
      
   if(kOK == ret)
      ack(itf, kMsgSlinkSetSemProg);
   else nack(itf, kMsgSlinkSetSemProg, ret);
}

static void serial_msg_get_sem_prog(size_t itf, const SeMsgHead * recv_msg)
{
   const SignalNetwork * netw = logic_slink_get_prog();

   if(netw == NULL)
   {
      nack(itf, kMsgSlinkGetSemProg, kErrorNoData);
      return;
   }
   
   SeMsgProg msg = {
      .head = {
         .size = sizeof(SeMsgProg) + netw->size,
         .id = kMsgSlinkSetSemProg,
      },
      .remote = false,
   };
      
   server_begin_send_msg(itf, &msg.head, sizeof(SeMsgProg));
   server_continue_data_msg(itf, netw, netw->size);
   server_finalize_msg(itf);
}

static void serial_msg_get_config(size_t itf, const SeMsgHead * msg)
{
   SeMsgConfig msg_config = {
     .head = {
        .size = sizeof(SeMsgConfig),
        .id = kMsgSlinkSetConfig,
     },
     .radio = app_config.radio,
   };

   server_send_msg(itf, &msg_config.head);
}

static void serial_msg_set_config(size_t itf, const SeMsgHead * msg)
{
   const SeMsgConfig * msg_config = (const SeMsgConfig *)msg;
   
   const NetworkConfig nc = {
      .addr_local = msg_config->addr_local, 
      .addr_network = msg_config->addr_network
   };
   
   size_t ret = logic_slink_set_config(&nc, &msg_config->radio);

   if(kOK == ret)
      ack(itf, kMsgSlinkSetConfig);
   else nack(itf, kMsgSlinkSetConfig, ret);
}

static void serial_msg_get_time(size_t itf, const SeMsgHead * msg)
{
   uint32_t time = logic_slink_get_time();
   
   SeMsgTime msg_time = {
     .head = {
        .size = sizeof(SeMsgTime),
        .id = kMsgSlinkSetTime,
     },
     .time = time,
   };

   server_send_msg(kSlinkItfAll, &msg_time.head);
}

static void serial_msg_set_time(size_t itf, const SeMsgHead * msg)
{
   const SeMsgTime * msg_time = (const SeMsgTime *) msg;
   logic_slink_set_time(msg_time->time);
   ack(itf, kMsgSlinkSetTime);
}

static void serial_msg_set_sem_netw(size_t itf, const SeMsgHead * msg)
{
   const SignalNetwork * netw = (const SignalNetwork *)(msg + 1);
      
   size_t ret = logic_slink_set_netw(netw);
   if(kOK == ret)
      ack(itf, kMsgSlinkSetNetProg);
   else nack(itf, kMsgSlinkSetNetProg, ret);
}


/////////////////////////////////////////////////////////////   SMS    //////////////////////////////////////////////////////


static void serial_msg_set_sms(size_t itf, const SeMsgHead * msg)
{
   const SeMsgSetSms * msgs = (const SeMsgSetSms *) msg;
   size_t text_size = msgs->head.size - sizeof(SeMsgSetSms);
   
   cell_receive_sms(itf, msgs->phone_nr, (const char *)(msgs + 1), text_size);
}


/////////////////////////////////////////////////////////////   Public    //////////////////////////////////////////////////////


void serial_send_msg_old(size_t itf, SeMsgHead * msg)
{
   server_send_msg(itf, msg);
}


void serial_send_sms_msg(size_t itf, const char * no, const char * text, size_t len)
{
   SeMsgSetSms msg = {
     .head = {
        .size = sizeof(SeMsgSetSms) + len,
        .id = kMsgSlinkSetSms,
     },
   };
   
   msg.phone_nr[sizeof(msg.phone_nr) - 1] = '\0';
   
   int i = 0;
   for(; i < sizeof(msg.phone_nr); i++)
   {
      msg.phone_nr[i] = no[i];
      if(no[i] == '\0')
         break;
   }
   
   server_begin_send_msg(itf, &msg.head, sizeof(SeMsgSetSms));
   server_continue_data_msg(itf, text, len);
   server_finalize_msg(itf);
}

static void serial_msg_edge_proc_sms(size_t itf, const SeMsgHead * msg)
{
 * uint8_t phone_nr[16] = {0};
   
   strncpy(phone_nr, data, sizeof(phone_nr) - 1);
   
   cell_receive_sms(itf, phone_nr, (const char *)&(((const char *)data)[sizeof(phone_nr)]), size - sizeof(phone_nr));
 
   const SeMsgSetSms * msgs = (const SeMsgSetSms *) msg;
   size_t text_size = msgs->head.size - sizeof(SeMsgSetSms);
   
   cell_receive_sms(itf, msgs->phone_nr, (const char *)(msgs + 1), text_size);
}*/


void serial_send_msg(size_t itf, const void * msg, size_t size, size_t id, size_t ep)
{
   server_send(itf, msg, size, id, ep);
}


static void serial_on_msg_ctrl_get(size_t itf, const void * data, size_t size)
{
   DataCtrlReq req;
   
   if (!edge_parse_ctrl_get(&req, data, size))
   {
      DBG(kLvlError, "serial, failed to deserialize ctrl req, %s:", data);
      return;
   }
   
   if (!memcmp(req.what, "status", 7))
   {
      edge_send_ctrl_status();
   }
}

static void serial_on_msg_ctrl_set_config(size_t itf, const void * data, size_t size)
{
   DataCtrlConfig cfg;
   
   if (!edge_parse_ctrl_set_config(&cfg, data, size))
   {
      DBG(kLvlError, "serial, failed to deserialize set config, %s:", data);
      return;
   }
   
   logic_set_new_config(&cfg);
}

static void serial_on_msg_ctrl_set_title(size_t itf, const void * data, size_t size)
{
   DataCtrlTitle title;
   
   if (!edge_parse_ctrl_set_title(&title, data, size))
   {
      DBG(kLvlError, "serial, failed to deserialize set title, %s:", data);
      return;
   }
   
   logic_set_title(&title);
}

static void serial_on_msg_mon_sms(size_t itf, const void * data, size_t size)
{
   DataMonSms msg;
   if (!edge_parse_mon_sms(&msg, data, size))
   {
      DBG(kLvlError, "serial, failed to deserialize mon sms, %s:", data);
      return;
   }
   
   cell_receive_sms(itf, msg.nr, msg.text, strlen(msg.text));
}


/////////////////////////////////////////////////////////////   Public    //////////////////////////////////////////////////////


void serial_init(const ServerConfig * config)
{
   serial.config = config;
   
   server_init(config);
   
   /*server_add_handler(kSlinkItfPc, kMsgSlinkHello, 0, &serial_msg_hello);
   server_add_handler(kSlinkItfPc, kMsgSlinkInfo, 0, &serial_msg_info);
   server_add_handler(kSlinkItfPc, kMsgSlinkGetSemProg, 0, &serial_msg_get_sem_prog);
   server_add_handler(kSlinkItfPc, kMsgSlinkSetSemProg, 0, &serial_msg_set_sem_prog);
   server_add_handler(kSlinkItfPc, kMsgSlinkGetConfig, 0, &serial_msg_get_config);
   server_add_handler(kSlinkItfPc, kMsgSlinkSetConfig, 0, &serial_msg_set_config);
   server_add_handler(kSlinkItfPc, kMsgSlinkGetTime, 0, &serial_msg_get_time);
   server_add_handler(kSlinkItfPc, kMsgSlinkSetTime, 0, &serial_msg_set_time);
   server_add_handler(kSlinkItfPc, kMsgSlinkSetNetProg, 0, &serial_msg_set_sem_netw);
   server_add_handler(kSlinkItfPc, kMsgSlinkSetSms, 0, &serial_msg_set_sms);*/
   
   
   server_add_handler(kSlinkItfEdge, kMsgSlinkCtrlGet, kSlinkEpServer, &serial_on_msg_ctrl_get);
   server_add_handler(kSlinkItfEdge, kMsgSlinkCtrlSetConfig, kSlinkEpServer, &serial_on_msg_ctrl_set_config);
   server_add_handler(kSlinkItfEdge, kMsgSlinkCtrlSetTitle, kSlinkEpServer, &serial_on_msg_ctrl_set_title);
   
   server_add_handler(kSlinkItfEdge, kMsgSlinkMonSms, kSlinkEpMonitor, &serial_on_msg_mon_sms);

}

void serial_start(void)
{
   server_start();
}

void serial_service(void)
{
   server_service();
}