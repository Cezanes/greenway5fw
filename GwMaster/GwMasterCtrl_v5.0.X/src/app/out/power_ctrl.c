#include "types.h"
#include "power_ctrl.h"
#include "power_msg.h"

#include "hal/sys.h"

#include "sal/debug.h"
#include "sal/timer.h"

#include "cfg/app_config.h"

#include "sas/canbus.h"

enum
{
   kPwrErrTransmit  = 1 << 0,
   kPwrErrPortRange = 1 << 1,
   kPwrErrPortPin   = 1 << 2,
};


typedef struct
{
   uint32_t signal;
   uint32_t burnt;
   uint32_t failed;
   uint32_t input;
   uint32_t time_stamp;
   
   size_t missing_responses;
   
   uint32_t last_burnt;
   uint32_t last_time_stamp;
} PowerBoard;


typedef struct
{
   uint32_t unpowered;
   uint32_t last_unpowered;
   
   uint32_t disconnected;
   uint32_t last_disconnected;
   
   uint32_t failed;
   uint32_t last_failed;
   
   PowerBoard board[16];
   
   bool req_print_metrics;
   
   PCtrlConfig config;
   PCtrlSetup setup;
   uint32_t errors;
} PCtrlInternal;


//////////////////////////////////////////////////////////////////////////////////////////////


static PCtrlInternal pctrl;


//////////////////////////////////////////////////////////////////////////////////////////////


static void handle_ctrl_status(size_t id, size_t flags, uint32_t burnt_map, uint32_t failed_map, uint32_t input_map)
{
   if(id >= pctrl.setup.pctrl_count)
      return;
   
   uint32_t mask = 1U << id;
   
   if(flags & kPwrMsgOutFlagPowerDown)
      pctrl.unpowered |= mask;
   else
      pctrl.unpowered &= ~mask;
   
   if(flags & kPwrMsgOutFlagFailedOutput)
      pctrl.failed |= mask;
   else
      pctrl.failed &= ~mask;
   
   pctrl.disconnected &= ~mask;
   
   //DBG(kLvlVerb, "hctrl, status %u %u", id, pctrl.connected);
   
   pctrl.board[id].burnt = burnt_map;
   pctrl.board[id].failed = failed_map;
   pctrl.board[id].input = input_map;
   pctrl.board[id].time_stamp = _CP0_GET_COUNT();
}


//////////////////////////////////////////////////////////////////////////////////////////////


void pctrl_on_recv_msg(const CanMsg * msg)
{
   // DBG(kLvlInfo, "hctrl, received CAN msg %X %X", msg->data[0], msg->data[1]);
   
   PwrMsg pmsg = {
      .id = msg->id,
      .data = {msg->data[0], msg->data[1]},
   };
   
   if((pmsg.src_type != kPwrMsgDevTypePwrOutput) ||
      (pmsg.dst_type != kPwrMsgDevTypeCtrl))
      //(pmsg.dst_addr != app_config.net.addr_local))
   {
      // DBG(kLvlVerb, "hctrl, skipped CAN msg %u %u:%u %u:%u", pmsg.cmd, pmsg.src_addr, pmsg.src_type, pmsg.dst_addr, pmsg.dst_type);
      return;
   }
   
   size_t id = pmsg.src_addr - kPwrMsgAddrFirst;
   
   switch(pmsg.cmd)
   {
      case kPwrMsgOutCmdStatus:
      {
         handle_ctrl_status(id, pmsg.po.status.flags, pmsg.po.status.burnt, pmsg.po.status.failed, pmsg.po.status.input);
         break;
      }
      
      default:
      {
         DBG(kLvlDbg, "hctrl, unhandled CAN msg %u %u:%u %u:%u", pmsg.cmd, pmsg.src_addr, pmsg.src_type, pmsg.dst_addr, pmsg.dst_type);
         break;
      }
   }
}

static void send_signal(size_t id, bool led_sync)
{
   PwrMsg msg = {
      .dst_addr = kPwrMsgAddrFirst + id,
      .dst_type = kPwrMsgDevTypePwrOutput,
      .src_addr = kPwrMsgAddrFirst,
      .src_type = kPwrMsgDevTypeCtrl,
      .cmd = kPwrMsgOutCmdSignal16,
      .po = {
         .sig16 = {
            .value = pctrl.board[id].signal,
            .flags = led_sync ? PwrMsgOutSig16FlagSecMark : 0,
         },
      },
   };
   
   if(!can_send(msg.id, msg.data, 8))
   {
      pctrl.errors |= kPwrErrTransmit;
   }
}


//////////////////////////////////////////////////////////////////////////////////////////////

static void print_metrics(void)
{
   for(size_t i = 0; i < pctrl.setup.pctrl_count; i++)
   {
      if(pctrl.board[i].last_burnt != pctrl.board[i].burnt)
      {
         DBG(kLvlWarn, "hctrl, burnt bulbs on P%u: %X", i + kPwrMsgAddrFirst, pctrl.board[i].burnt);
         pctrl.board[i].last_burnt = pctrl.board[i].burnt;
      }
   }
   
   if(pctrl.last_unpowered != pctrl.unpowered)
   {
      uint32_t mask = 1;
      
      for(size_t i = 0; i < pctrl.setup.pctrl_count; i++, mask <<= 1)
      {
         if(!(pctrl.last_unpowered & mask) && (pctrl.unpowered & mask))
         {
            DBG(kLvlWarn, "hctrl, board power P%u: OFF", i + kPwrMsgAddrFirst);
         }
         
         if((pctrl.last_unpowered & mask) && !(pctrl.unpowered & mask))
         {
            DBG(kLvlWarn, "hctrl, board power P%u: ON", i + kPwrMsgAddrFirst);
         }
      }
      
      pctrl.last_unpowered = pctrl.unpowered;
   }
   
   if(pctrl.last_disconnected != pctrl.disconnected)
   {
      uint32_t mask = 1;
      
      for(size_t i = 0; i < pctrl.setup.pctrl_count; i++, mask <<= 1)
      {
         if(!(pctrl.last_disconnected & mask) && (pctrl.disconnected & mask))
         {
            DBG(kLvlWarn, "hctrl, board disconnected P%u", i + kPwrMsgAddrFirst);
         }
         
         if((pctrl.last_disconnected & mask) && !(pctrl.disconnected & mask))
         {
            DBG(kLvlWarn, "hctrl, board reconnected P%u", i + kPwrMsgAddrFirst);
         }
      }
      
      pctrl.last_disconnected = pctrl.disconnected;
   }
   
   if(pctrl.last_failed != pctrl.failed)
   {
      uint32_t mask = 1;
      
      for(size_t i = 0; i < pctrl.setup.pctrl_count; i++, mask <<= 1)
      {
         if(!(pctrl.last_failed & mask) && (pctrl.failed & mask))
         {
            DBG(kLvlWarn, "hctrl, board triac failed P%u", i + kPwrMsgAddrFirst);
         }
         
         if((pctrl.last_failed & mask) && !(pctrl.failed & mask))
         {
            DBG(kLvlWarn, "hctrl, board triac working now? P%u", i + kPwrMsgAddrFirst);
         }
      }
      
      pctrl.last_failed = pctrl.failed;
   }
}


//////////////////////////////////////////////////////////////////////////////////////////////


void pctrl_init(const PCtrlConfig * config)
{
   pctrl = (PCtrlInternal){0};
   can_init(&config->can);
}

void pctrl_pswitch_set(bool en)
{
   PwrMsg msg = {
      .dst_addr = kPwrMsgAddrAny,
      .dst_type = kPwrMsgDevTypePwrSplit,
      .src_addr = kPwrMsgAddrFirst,
      .src_type = kPwrMsgDevTypeCtrl,
      .cmd = en ? kPwrMsgSplitCmdSetFlags : kPwrMsgSplitCmdClearFlags,
      .ps = {
         .status = {
            .flags = kPwrMsgSplitFlagActive,
         },
      },
   };
   
   if(!can_send(msg.id, msg.data, 8))
   {
      pctrl.errors |= kPwrErrTransmit;
   }
}

void pctrl_scan_boards(void)
{
   PwrMsg msg = {
      .dst_addr = kPwrMsgAddrFirst,
      .dst_type = kPwrMsgDevTypePwrOutput,
      .src_addr = kPwrMsgAddrFirst,
      .src_type = kPwrMsgDevTypeCtrl,
      .cmd = kPwrMsgOutCmdReset,
   };
   
   for(size_t i = 0; i < pctrl.setup.pctrl_count; i++)
   {
      msg.dst_addr = kPwrMsgAddrFirst + i;
      
      if(!can_send(msg.id, msg.data, 8))
      {
         pctrl.errors |= kPwrErrTransmit;
      }
      
      timer_delay_ms(10);
   }
}

bool pctrl_setup(const PCtrlSetup * setup)
{
   if(setup->pctrl_count >= COUNT(pctrl.board))
   {
      DBG(kLvlError, "sem, port count too high %u vs %u", setup->pctrl_count, COUNT(pctrl.board));
      return false;
   }
   
   DBG(kLvlVerb, "pctrl, ctrl count %u", setup->pctrl_count);
      
   pctrl.setup = *setup;

   pctrl_clear_status();
   pctrl_scan_boards();
   
   return true;
}


void pctrl_clear_outs(void)
{
   for(size_t i = 0; i < COUNT(pctrl.board); i++)
   {
      pctrl.board[i].signal = 0;
   }
}

void pctrl_clear_status(void)
{
   PwrMsg msg = {
      .dst_addr = kPwrMsgAddrAny,
      .dst_type = kPwrMsgDevTypePwrSplit,
      .src_addr = kPwrMsgAddrFirst,
      .src_type = kPwrMsgDevTypeCtrl,
      .cmd = kPwrMsgSplitCmdReset,
   };
   
   if(!can_send(msg.id, msg.data, 8))
   {
      pctrl.errors |= kPwrErrTransmit;
   }
   
   for(size_t i = 0; i < pctrl.setup.pctrl_count; i++)
   {
      pctrl.board[i].burnt = 0;
      pctrl.board[i].last_burnt = 0;
   }
   
   pctrl.unpowered = 0;
   pctrl.disconnected = 0;
   pctrl.failed = 0;
   
   msg = (PwrMsg) {
      .dst_addr = kPwrMsgAddrAny,
      .dst_type = kPwrMsgDevTypePwrOutput,
      .src_addr = kPwrMsgAddrFirst,
      .src_type = kPwrMsgDevTypeCtrl,
      .cmd = kPwrMsgOutCmdReset,
   };
   
   if(!can_send(msg.id, msg.data, 8))
   {
      pctrl.errors |= kPwrErrTransmit;
   }
}

bool pctrl_set(size_t port, size_t pin)
{
   if(port > pctrl.setup.pctrl_count  || port == 0)
   {
      pctrl.errors |= kPwrErrPortRange;
      return false;
   }
   
   if(pin > 12 || pin == 0)
   {
      pctrl.errors |= kPwrErrPortPin;
      return false;
   }
   
   pin--;
   port--;
   
   uint32_t mask = 1UL << pin;
   
   pctrl.board[port].signal |= mask;
   
   if(pctrl.board[port].burnt & mask)
   {
      return false;
   }
   
   return true;
}

bool pctrl_is_board_present(size_t port)
{
   if(port > pctrl.setup.pctrl_count || port == 0)
      return false;
   
   port--;
   
   uint32_t mask = 1UL << port;
      
   return (pctrl.disconnected & mask) == 0;
}

bool pctrl_is_board_powered(size_t port)
{
   if(port > pctrl.setup.pctrl_count || port == 0)
      return false;
   
   port--;
   
   uint32_t mask = 1UL << port;
   
   return (pctrl.unpowered & mask) == 0;
}

bool pctrl_is_bulb_burnt(size_t port, size_t pin)
{
   if(port > pctrl.setup.pctrl_count || port == 0)
      return false;
   
   port--;
   
   uint32_t mask = 1UL << pin;
   
   return (pctrl.board[port].burnt & mask) > 0;
}

uint32_t pctrl_get_unpowered(void)
{
   return pctrl.unpowered;
}

uint32_t pctrl_get_disconnected(void)
{
   return pctrl.disconnected;
}

uint32_t pctrl_get_failed(void)
{
   return pctrl.failed;
}

uint32_t pctrl_get_burnt(size_t port)
{
   if(port > pctrl.setup.pctrl_count || port == 0)
      return false;
   
   return pctrl.board[port - 1].burnt;
}

void pctrl_commit(bool led_sync)
{
   for(size_t i = 0; i < pctrl.setup.pctrl_count; i++)
   {
      send_signal(i, led_sync);
   }
   
   pctrl.req_print_metrics = true;
}

void pctrl_compile_metrics(void)
{
   for(size_t i = 0; i < pctrl.setup.pctrl_count; i++)
   {
      uint32_t mask = 1UL << i;

      PowerBoard * board = &pctrl.board[0];
      if(board->time_stamp == board->last_time_stamp)
      {
         if(board->missing_responses < 3)
            board->missing_responses++;
         
         if(board->missing_responses >= 3)
         {
            pctrl.disconnected |= mask;
         }
      }
      else
      {
         board->last_time_stamp = board->time_stamp;
         board->missing_responses = 0;
      }
   }
}

void pctrl_service(void)
{
   can_service();
   
   if(pctrl.errors)
   {
      uint32_t errors = pctrl.errors;
      pctrl.errors = 0;
   
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
   
   if(pctrl.req_print_metrics)
   {
      pctrl.req_print_metrics = false;
      print_metrics();
   }
}