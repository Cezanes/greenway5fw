#include "buttons.h"
#include "debug.h"
#include "timer.h"

enum
{
   kBtnFlagDown     = 1,
   kBtnFlagLongDown = 2,
};

typedef struct 
{
   size_t flags;
   uint32_t timestamp;
   const volatile uint32_t * volatile port;
   uint32_t port_mask;
   BtnHandler handler;
} BtnInst;

typedef struct
{
   BtnInst inst[BTN_MAX_COUNT];
   size_t inst_count;
} BtnInternal;


/////////////////////////////////////////////////////////////////////////////////////////


static BtnInternal btn;


/////////////////////////////////////////////////////////////////////////////////////////


void btn_init(const ButtonConfig * config)
{
   size_t count = config->count;
   
   if(config->count > BTN_MAX_COUNT)
   {
      DBG(kLvlError, "buttons, not enough space for all buttons %u vs %u", config->count, BTN_MAX_COUNT);
      count = BTN_MAX_COUNT;
   }
   
   btn = (BtnInternal) {
      .inst_count = count,
   };
   
   for(size_t i = 0; i < count; i++)
   {
      btn.inst[i] = (BtnInst) {
        .port = config->entries[i].port,
        .port_mask = config->entries[i].port_mask,
      };
   }
}

void btn_add_handler(const size_t index, const BtnHandler handler)
{
   if(index >= btn.inst_count)
   {
      DBG(kLvlError, "buttons, invalid handler index %u, total %u", index, btn.inst_count);
      return;
   }
   
   btn.inst[index].handler = handler;
}

static void btn_check_button(BtnInst * inst)
{
   bool down = (*inst->port & inst->port_mask) == 0;
   
   if(down)
   {
      timer_delay_ms(10);
      down = (*inst->port & inst->port_mask) == 0;
   }
   
   if(down)
   {
      if(!(inst->flags & kBtnFlagDown))
      {
         if(inst->handler)
            (*inst->handler)(kBtnEventDown);
         
         inst->flags |= kBtnFlagDown;
         inst->timestamp = timer_tick();
      }
      else
      {
         if(!(inst->flags & kBtnFlagLongDown))
         {
            if(timer_tick() - inst->timestamp >= TM_MLS_T0_TICK(BTN_LONG_PERIOD_MS))
            {
               inst->flags |= kBtnFlagLongDown;
               if(inst->handler)
                  (*inst->handler)(kBtnEventLongPressed);
            }
         }
      }
   }
   else
   {
      if(inst->flags & kBtnFlagDown)
      {
         if(!(inst->flags & kBtnFlagLongDown))
         {
            if(inst->handler)
               (*inst->handler)(kBtnEventPressed);
         }
         
         inst->flags &= ~((size_t)kBtnFlagDown | kBtnFlagLongDown);
      
         if(inst->handler)
            (*inst->handler)(kBtnEventUp);
      }
   }
}

bool btn_is_status(const size_t index, const BtnEventType event)
{
   if(index >= btn.inst_count)
      return false;
   
   switch(event)
   {
      case kBtnEventDown: 
         return (btn.inst[index].flags & kBtnFlagDown) > 0;
         
      case kBtnEventLongPressed: 
         return (btn.inst[index].flags & kBtnFlagLongDown) > 0;
   }
   
   return false;
}

void btn_service()
{
   for(size_t i = 0; i < btn.inst_count; i++)
   {
      btn_check_button(&btn.inst[i]);
   }
}