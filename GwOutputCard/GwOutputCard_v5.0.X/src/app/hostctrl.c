#include "types.h"
#include "hostctrl.h"
#include "power_msg.h"

#include "hal/sys.h"

#include "sas/debug.h"
#include "sas/timer.h"

#include "ssl/canbus.h"
#include "ssl/bulbctrl.h"

#include "cfg/app_config.h"



enum
{
   kPwrErrTransmit  = 1 << 0,
   kPwrErrPortRange = 1 << 1,
   kPwrErrPortPin   = 1 << 2,
};

typedef struct
{
   HCtrlConfig config;

   uint32_t sig_map;
   uint32_t last_sig_map;
   
   uint32_t last_burnt_map;
   uint32_t last_output_fail_map;
   
   bool host_sig;
   bool host_sig_sec_mark;
   
   bool have_sig;
   bool sent_monitor_data;
   uint32_t last_sig_ts;
   
   uint32_t errors;
} HCtrlInternal;


//////////////////////////////////////////////////////////////////////////////////////////////


static HCtrlInternal hctrl;

static void send_status(void);

//////////////////////////////////////////////////////////////////////////////////////////////


static void on_recv_msg(const CanMsg * msg)
{
   PwrMsg pmsg = {
      .id = msg->id,
      .data = {msg->data[0], msg->data[1]},
   };
   
   if((pmsg.src_type != kPwrMsgDevTypeCtrl) ||
      (pmsg.src_addr != kPwrMsgAddrFirst) ||
      (pmsg.dst_type != kPwrMsgDevTypePwrOutput) ||
      (pmsg.dst_addr != app_config.addr_local && pmsg.dst_addr != kPwrMsgAddrAny))
   {
      //DBG(kLvlDbg, "hctrl, skipped CAN msg %u %u:%u %u:%u", pmsg.cmd, pmsg.src_addr, pmsg.src_type, pmsg.dst_addr, pmsg.dst_type);
      return;
   }
   
   switch(pmsg.cmd)
   {
      case kPwrMsgOutCmdReset:
      {
         bulb_ctrl_clear();
         bulb_ctrl_monitor(true);
         send_status();
         break;
      }
      
      case kPwrMsgOutCmdSignal16:
      {
         hctrl.host_sig = true;
         uint8_t flags = pmsg.po.sig16.flags;
         hctrl.sig_map = pmsg.po.sig16.value;
         
         bulb_ctrl_set_map(hctrl.sig_map);
         
         if (flags & PwrMsgOutSig16FlagSecMark)
            hctrl.host_sig_sec_mark = true;
         
         break;
      }
      
      case kPwrMsgOutCmdConfig:
      {
         bulb_ctrl_set_cfg(pmsg.po.cfg.burnt_timeout, pmsg.po.cfg.main_power_timeout);
         break;
      }
      
      default:
      {
         DBG(kLvlDbg, "hctrl, unhandled CAN msg %u %u:%u %u:%u", pmsg.cmd, pmsg.src_addr, pmsg.src_type, pmsg.dst_addr, pmsg.dst_type);
         break;
      }
   }
}

static void send_msg(PwrMsg * pmsg, size_t size)
{
   pmsg->src_addr = app_config.addr_local;
   pmsg->src_type = kPwrMsgDevTypePwrOutput;
   pmsg->dst_addr = kPwrMsgAddrFirst;
   pmsg->dst_type = kPwrMsgDevTypeCtrl;
   
   CanMsg can_msg = {
      .id = pmsg->id,
      .size = size,
      .data = {
         pmsg->data[0],
         pmsg->data[1],
      },
   };
   
   can_send_msg(&can_msg);
}

static void send_status(void)
{
   uint32_t bulb_burnt_map = bulb_ctrl_burnt_bulb_map();
   uint32_t triac_failed_map = bulb_ctrl_burnt_triac_map();

   size_t flags = 0;
   
   if(!bulb_ctrl_have_power())
      flags |= kPwrMsgOutFlagPowerDown;
   
   if(triac_failed_map > 0)
      flags |= kPwrMsgOutFlagFailedOutput;
   
   if (bulb_burnt_map > 0)
      flags |= kPwrMsgOutFlagBurntBulb;
   
   PwrMsg pmsg = {
      .cmd = kPwrMsgOutCmdStatus,
      .po = {
         .status = {
            .flags = flags,
            .input = 0,
            .burnt = bulb_burnt_map,
            .failed = triac_failed_map,
         },
      },
   };
   
   send_msg(&pmsg, sizeof(pmsg.po.status));
}

static void on_transmit_error(void)
{
   
}

static void check_errors(void)
{
   uint32_t bulb_burnt_map = bulb_ctrl_burnt_bulb_map();
   uint32_t output_burnt_map = bulb_ctrl_burnt_triac_map();
   
   if(hctrl.last_burnt_map != bulb_burnt_map)
   {
      DBG(kLvlWarn, "hostctrl, burnt: %X", bulb_burnt_map);
      hctrl.last_burnt_map = bulb_burnt_map;
   }
   
   if(hctrl.last_output_fail_map != output_burnt_map)
   {
      DBG(kLvlWarn, "hostctrl, failed triac: %X", output_burnt_map);
      //bulb_ctrl_monitor(false);
      hctrl.last_output_fail_map = output_burnt_map;
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////


void hctrl_init(const HCtrlConfig * config)
{
   hctrl = (HCtrlInternal) {
      .config = *config
   };
   
   CanBusConfig bus_cfg = config->can;
   bus_cfg.on_recv_msg = on_recv_msg;
   
   pin_write(&config->pin_led_error, 0);
   pin_write(&config->pin_led_warning, 0);
   pin_output(&config->pin_led_error);
   pin_output(&config->pin_led_warning);
   
   can_init(&bus_cfg);
}

void hctrl_start(void)
{
   
}

void hctrl_send_feedback(void)
{
   if(hctrl.sent_monitor_data)
      return;
   
   if(timer_tick() - hctrl.last_sig_ts >= 50 + app_config.addr_local * 5)
   {
      hctrl.sent_monitor_data = true;
      send_status();
      check_errors();
      
      /*
      uint16_t list[12];
      
      for(size_t i = 0; i < 12; i++)
      {
         list[i] = hw_config.bulb_ctrl.active_feedback_cnt[i];
      }
      
      DBGHEX(kLvlDbg, "lst: ", list, sizeof(list));
      
      for(size_t i = 0; i < 12; i++)
      {
         list[i] = hw_config.bulb_ctrl.inactive_feedback_cnt[i];
      }
      
      DBGHEX(kLvlDbg, "lst: ", list, sizeof(list));
      DBGLN(kLvlDbg);
      */
   }
}

void hctrl_service(void)
{
   can_service();

   if(can_recv_overflow())
   {
      DBG(kLvlError, "hctrl, CAN recv buffer overflow");
   }
   
   if(hctrl.errors)
   {
      sys_disable_ints();
      uint32_t errors = hctrl.errors;
      hctrl.errors = 0;
      sys_enable_ints();
   
      if(errors & kPwrErrTransmit)
      {
         DBG(kLvlError, "pctrl, transmit error");
      }

      if(errors & kPwrErrPortRange)
      {
         DBG(kLvlError, "pctrl, port set out of range");
      }

      if(errors & kPwrErrPortPin)
      {
         DBG(kLvlError, "pctrl, pin set out of range");
      }
   }
   
   if(hctrl.sig_map != hctrl.last_sig_map)
   {
      hctrl.last_sig_map = hctrl.sig_map;
      //DBG(kLvlDbg, "hctrl, sigmap %4X", hctrl.sig_map);
   }
   
   if(hctrl.host_sig)
   {
      hctrl.host_sig = false;
      
      if(!hctrl.have_sig)
      {
         DBG(kLvlInfo, "pctrl, receiving signal from host");
      }
      
      if (hctrl.host_sig_sec_mark)
      {
         hctrl.host_sig_sec_mark = false;
         pulse_start(kPulseHostSync);
      }
      
      hctrl.sent_monitor_data = false;
      hctrl.have_sig = true;
      hctrl.last_sig_ts = timer_tick();
   }
   
   if(hctrl.have_sig)
   {
      if(timer_tick() - hctrl.last_sig_ts >= 1100)
      {
         hctrl.have_sig = false;
         DBG(kLvlWarn, "pctrl, lost signal from host");
         bulb_ctrl_clear();
      }
   }
   
   hctrl_send_feedback();
}