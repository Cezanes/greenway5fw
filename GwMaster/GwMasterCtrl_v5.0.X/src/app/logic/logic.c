#include "logic.h"

#include "hal/pin32.h"

#include "lib/utils.h"

#include "sal/debug.h"
#include "sal/buttons.h"
#include "sal/timer.h"

#include "sas/storage.h"
#include "sas/rmsg_type.h"
#include "sas/canbus.h"

#include "cfg/app_config.h"
#include "cfg/hw_config.h"

#include "app/sem/chronos.h"
#include "app/net/radio.h"


typedef struct __attribute__ ((packed))
{
   uint16_t crc;
   uint16_t size;
} StorageHeader;

static struct
{
   size_t timer_ping;
   size_t radio_bw;
   size_t boot_timestamp;
   
   bool use_broadcast_time;
   bool req_broadcast_time;
   bool gps_time_available;
   size_t timer_spread_time;
   
   bool remote_ctrl;

   uint8_t sch_buff[SIGNAL_MAX_SCHEDULE_SIZE];
} lg;


//////////////////////////////////////////////////////////////////////////////


static void lg_on_timer_spread(void);
static void lg_on_button(const BtnEventType);


//////////////////////////////////////////////////////////////////////////////


void logic_init()
{
   btn_add_handler(kBtnIndex0, &lg_on_button);
   
   if (app_config.net.addr_local == 0)
      lg.remote_ctrl = true;
   
   lg.use_broadcast_time = true;
   lg.req_broadcast_time = lg.use_broadcast_time;
   lg.timer_spread_time = timer_add(&lg_on_timer_spread, TM_SEC_T0_TICK(10), false, true);
}

void logic_start()
{
   DateTime dt;
   if(rtc_get_datetime(&dt))
   {
      lg.boot_timestamp = dte_get_epoch(&dt);
   }
}

uint32_t logic_get_uptime(void)
{
   DateTime dt;
   if(rtc_get_datetime(&dt))
   {
      return dte_get_epoch(&dt) - lg.boot_timestamp;
   }
   
   return 0;
}

void logic_service()
{
   
}


//////////////////////////////////////////////////////////////////////////////


void on_msg_event(const size_t id, const size_t event)
{
   DBG(kLvlInfo, "logic, msg event: %s", lora_event_str(event));
}

void on_msg_progress(const size_t id, const uint32_t sent, const uint32_t total)
{
   DBG(kLvlInfo, "logic, msg data %u/%u", sent, total);
}

static void lg_on_button(const BtnEventType event)
{
   if(event == kBtnEventPressed)
   {
      DBG(kLvlInfo, "logic, button ");
   
      //cell_report_new_state();
      
      lg.req_broadcast_time = true;

      return;
      
      DBG(kLvlVerb, "logic, radio bw %u", lg.radio_bw);
   
      uint8_t data[4];
      for(size_t i = 0; i < COUNT(data); i++)
         data[i] = i;
      
      RaMsgHead * msg = (RaMsgHead *)&data[0];
      *msg = (RaMsgHead){
        .cmd = 11,
        .dest = 1,
        .network = 1,
        .source = 1,
      };
      
      const RmsgMessageContext context = {
         .id = 100,
         .dest = 1,
         .msg = msg,
         .size = sizeof(data),
         .req_ack = true,
         .event = &on_msg_event,
         .progress = &on_msg_progress,
      };
      
      radio_send(&context);
      
      return;
   }
   
   if(event == kBtnEventLongPressed)
   {
      
      return;
      
      
      lg.radio_bw++;
      if(lg.radio_bw >= 8)
         lg.radio_bw = 0;

      radio_config(lg.radio_bw);
      
      DBG(kLvlVerb, "logic, radio bw %u", lg.radio_bw);
      return;
   }
}


///////////////////////////////////////////////////////   Serial Link   ///////////////////////////////////////////////////////


uint32_t logic_slink_get_time(void)
{
   return chronos_get_time();
}

void logic_slink_set_time(const uint32_t time)
{
   logic_broadcast_time(time);
   chronos_set_time(time, 0);
}

size_t logic_slink_set_config(const NetworkConfig * network, const RadioConfig * config)
{
   app_config.radio = *config;
   
   app_config.net.addr_local = network->addr_local;
   app_config.net.addr_network = network->addr_network;

   size_t ret = app_config_write();

   lora_update_config(config);
   radio_config(app_config.radio.bandwidth_index);
   
   return ret;
}

size_t logic_slink_set_local_prog(const SignalNetwork * netw)
{
   const uint8_t * dest = storage_get_ptr(kStorageSemProg);
   const uint32_t dest_size = storage_get_size(kStorageSemProg);
   
   if(netw->size < sizeof(SignalNetwork) || netw->size > dest_size)
   {
      DBG(kLvlWarn, "logic, sem prog write invalid size %u, max %u", netw->size, dest_size);
      return kErrorSize;
   }
   
   uint16_t crc = utils_crc16t(&netw->crc + 1, netw->size - sizeof(netw->crc), CRC_START_CCITT_1D0F);
   if(netw->crc != crc)
   {
      DBG(kLvlWarn, "logic, sem prog write crc error %04X vs %04X", crc, netw->crc);
      return kErrorCrc;
   }
   
   if(netw->controller_count == 0)
   {
      DBG(kLvlError, "logic, sem prog has no controllers");
      return kErrorConfig;
   }
   
   const SignalController * recv_ctrl = (const SignalController *) (netw + 1);
   
   if(netw->id != app_config.net.addr_network)
   {
      DBG(kLvlWarn, "logic, network ID mismatch %u vs %u", netw->id, app_config.net.addr_network);
      return kErrorId;
   }
   
   if(recv_ctrl->id != app_config.net.addr_local)
   {
      DBG(kLvlWarn, "logic, ctrl ID mismatch %u vs %u", recv_ctrl->id, app_config.net.addr_local);
      return kErrorId;
   }
   
   sem_suspend(true);
   
   if(!storage_erase(kStorageSemProg) ||
      !storage_write(kStorageSemProg, dest, netw, netw->size))
   {
      DBG(kLvlError, "logic, sem prog flash error");
      return kErrorFlash;
   }
   
   if(app_config.timezone != netw->timezone)
   {
      app_config.timezone = netw->timezone;
      app_config_write();
   }
   
   const SignalNetwork * dest_netw = (const SignalNetwork *) dest;
   const SignalController * ctrl = (const SignalController *) (dest_netw + 1);
   
   sem_set_program(ctrl);
   sem_suspend(false);

   if (ctrl->schedule_count > 0)
   {
      const SignalSchedule * sch = (const SignalSchedule *) (ctrl + 1);
   
      DBG(kLvlInfo, "logic, network '%s', id %u, size %u", netw->name, netw->id, netw->size);

      sem_print_port(ctrl);

      while (sch != NULL)
      {
         sem_print_sch(sch);
         sch = sem_next_sch(ctrl, sch);
      }
   }
   else
   {
      DBG(kLvlWarn, "logic, controller has no schedules");
   }

   return kOK;
}

const SignalNetwork * logic_slink_get_prog(void)
{
   const SignalNetwork * netw = storage_get_ptr(kStorageSemProg);
   const uint32_t dest_size = storage_get_size(kStorageSemProg);
   
   if (netw->size == 0)
   {
      return NULL;
   }
   
   if(netw->size < sizeof(SignalNetwork) || netw->size > dest_size)
   {
      //DBG(kLvlWarn, "logic, sem prog invalid size, not available");
      return NULL;
   }
   
   uint16_t crc = utils_crc16t(&netw->crc + 1, netw->size - sizeof(netw->crc), CRC_START_CCITT_1D0F);
   if(netw->crc != crc)
   {
      //DBG(kLvlWarn, "logic, sem prog crc err, not available");
      return NULL;
   }
   
   return netw;
}

static size_t send_network_prog(const SignalNetwork * netw, const uint8_t host)
{
   if(!lora_available())
   {
      DBG(kLvlWarn, "radio, rfm95 not available");
      return kErrorRadio;
   }
   
   uint8_t * blob_data;
   size_t blob_capacity;
   
   radio_get_buff(&blob_data, &blob_capacity);
   
   if(netw->size < sizeof(SignalNetwork) || netw->size + sizeof(RaMsgNetworkProg) > blob_capacity)
   {
      DBG(kLvlWarn, "logic, sem netw size too big %u vs %u", netw->size + sizeof(RaMsgNetworkProg), blob_capacity);
      return kErrorSize;
   }

   if(radio_is_busy())
   {
      DBG(kLvlWarn, "logic, sem netw radio is busy");
      return kErrorRadio;
   }
   
   size_t netw_size = netw->size;
   
   memmove(&blob_data[blob_capacity - netw_size], netw, netw_size);
   
   RaMsgNetworkProg * msg = (RaMsgNetworkProg *)blob_data;
   
   *msg = (RaMsgNetworkProg) {
      .head = {
         .cmd = kRadioMsgNetwProg,
         .dest = host,
         .network = netw->id,
      },
      .ttl = 50,
   };
   
   memcpy(msg + 1, &blob_data[blob_capacity - netw_size], netw_size);
   //memcpy(msg + 1, netw, netw->size);

   const RmsgMessageContext context = {
      .id = radio_get_new_blob_id(),
      .msg = &msg->head,
      .dest = host,
      .size = sizeof(RaMsgNetworkProg) + netw_size,
      .req_ack = true,
      .event = &on_msg_event,
      .progress = &on_msg_progress,
   };

   if(!radio_send(&context))
      return kErrorRadio;
   
   return kOK;
}

size_t logic_slink_set_remote_prog(const SignalNetwork * netw)
{
   uint16_t crc = utils_crc16t(&netw->crc + 1, netw->size - 2, CRC_START_CCITT_1D0F);
   if(netw->crc != crc)
   {
      DBG(kLvlWarn, "logic, sem netw write crc error %04X vs %04X", crc, netw->crc);
      return kErrorCrc;
   }
   
   if(netw->controller_count == 0)
   {
      DBG(kLvlWarn, "logic, sem netw controller count is 0");
      return kErrorConfig;
   }
   
   const SignalController * ctrl = sem_next_ctrl(netw, NULL);
   
   if(ctrl == NULL)
   {
      DBG(kLvlError, "logic, sem remote prog controller count is 0");
      return kErrorConfig;
   }
   
   if(ctrl->id == app_config.net.addr_local)
   {
      DBG(kLvlWarn, "logic, sem remote prog same cannot send to own id %u", app_config.net.addr_local);
      return kErrorId;
   }
   
   if(app_config.net.addr_local == 0)
      app_config.net.addr_network = netw->id;
   
   return send_network_prog(netw, ctrl->id);
}

size_t logic_slink_set_netw(const SignalNetwork * netw)
{
   uint16_t crc = utils_crc16t(&netw->crc + 1, netw->size - 2, CRC_START_CCITT_1D0F);
   if(netw->crc != crc)
   {
      DBG(kLvlWarn, "logic, sem netw write crc error %04X vs %04X", crc, netw->crc);
      return kErrorCrc;
   }
   
   if(app_config.net.addr_local == 0)
      app_config.net.addr_network = netw->id;
   
   if(netw->id != app_config.net.addr_network)
   {
      DBG(kLvlWarn, "logic, sem netw invalid network id %u vs %u", netw->id, app_config.net.addr_network);
      return kErrorId;
   }
   
   if(netw->controller_count == 0)
   {
      DBG(kLvlWarn, "logic, sem netw controller count is 0");
      return kErrorConfig;
   }
   
   bool found = false;
   bool next = false;
   uint8_t next_host = 0;
   
   const SignalController * ctrl = sem_next_ctrl(netw, NULL);
   
   NetworkConfig ncfg = {
      .node_count = 0,
   };
   
   do
   {
      if (ncfg.node_count < COUNT(ncfg.node_list))
      {
         ncfg.node_list[ncfg.node_count++] = ctrl->id;
      }
      
      if(found && !next)
      {
         if(ctrl->id == app_config.net.addr_local)
         {
            DBG(kLvlError, "logic, sem netw found our ID twice");
            return kErrorConfig;
         }
         
         next_host = ctrl->id;
         next = true;
      }
      
      if (!found && ctrl->id == app_config.net.addr_local)
      {
         found = true;
         uint32_t size = ctrl->size + sizeof(SignalNetwork);
         
         if(size > sizeof(lg.sch_buff))
         {
            DBG(kLvlError, "logic, cannot use ctrl temp buff, size too small %u vs %u", size, sizeof(lg.sch_buff));
         }
         else
         {
            SignalNetwork * cur_net = (SignalNetwork * )lg.sch_buff;
            *cur_net = *netw;

            cur_net->controller_count = 1;
            cur_net->size = size;
            memcpy(cur_net + 1, ctrl, ctrl->size);

            cur_net->crc = utils_crc16t(&cur_net->crc + 1, cur_net->size - sizeof(cur_net->crc), CRC_START_CCITT_1D0F);

            size_t ret = logic_slink_set_local_prog(cur_net);
            if(kOK != ret)
            {
               DBG(kLvlError, "logic, could not write sem data, %u", ret);
            }
         }
      }
      
      ctrl = sem_next_ctrl(netw, ctrl);
      
   } while(ctrl != NULL);
   
   if (!found)
   {
      DBG(kLvlError, "logic, sem netw no configuration found for this controller %u", app_config.net.addr_local);
      return kErrorConfig;
   }
   
   app_config.net.node_count = ncfg.node_count;
   memcpy(app_config.net.node_list, ncfg.node_list, sizeof(ncfg.node_list));
   app_config_write();
   
   if (next)
   {
      return send_network_prog(netw, next_host);
   }
   
   return kOK;
}

///////////////////////////////////////////////////////    GPS    ///////////////////////////////////////////////////////

void logic_broadcast_time(const uint32_t time)
{
   RaMsgTime msg = (RaMsgTime) {
      .head = {
         .cmd = kRadioMsgTime,
         .dest = LORA_HOST_BROADCAST,
      },
      .time = time,
      .jitter = lora_air_time(sizeof(msg)),
   };
   
   radio_send_simple(&msg.head, sizeof(RaMsgTime));
}

void logic_on_gps_status(bool available, uint32_t epoch)
{
   if (available)
   {
      chronos_gps_time_upd(epoch);
   }
   
   if(lg.use_broadcast_time)
   {
      if (lg.gps_time_available != available)
      {
         if (available)
         {
            timer_set_period(lg.timer_spread_time, TM_MIN_T0_TICK(10) * app_config.net.addr_network + app_config.net.addr_local * TM_SEC_T0_TICK(5));
            timer_reset(lg.timer_spread_time);
            lg.req_broadcast_time = true;
         }
         else
         {
            timer_disable(lg.timer_spread_time);
         }

         lg.gps_time_available = available;
      }

      if (available && lg.req_broadcast_time)
      {
         lg.req_broadcast_time = false;
         logic_broadcast_time(epoch);
      }
   }
}

static void lg_on_timer_spread(void)
{
   lg.req_broadcast_time = true;
}

void logic_have_gps_time(const bool have)
{
   /*if(have)
   {
      timer_set_period(lg.timer_gps_spread, TM_SEC_T0_TICK(10 + 10 * app_config.radio.addr_local));
      timer_reset(lg.timer_gps_spread);
   }
   else
   {
      timer_disable(lg.timer_gps_spread);
   }*/
}

///////////////////////////////////////////////////////   Radio Link   ///////////////////////////////////////////////////////

size_t logic_rlink_set_netw(const SignalNetwork * netw)
{
   return logic_slink_set_netw(netw);
}

bool logic_rlink_is_remote(void)
{
   return lg.remote_ctrl;
}