
#include <stdio.h>

#include "types.h"
#include "timer.h"
#include "pulse.h"

#include "sas/debug.h"

#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/tmr2.h"

#define TM_TIMER_ENTRIES                           5

/* Memory footprint for each timer entry */
typedef struct
{
   bool repeat;
   bool enabled;
   uint32_t period;
   uint32_t started;
   TimerCb cb;
} TimerEntry;

static struct
{
   bool isr;
   uint32_t ticker;
   uint32_t epoch;
   uint32_t second_accum;
   uint32_t ms_accum;
   
   size_t timer_count;
   TimerEntry timers[TM_TIMER_ENTRIES];
} tm;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timer_init(void)
{
   TMR2 = 0x0;
   PR2 = 0x3E8;
   T2CON = 0x8050;
   
   IPC2bits.T2IP = 1;
   IPC2bits.T2IS = 0;
   
   IFS0CLR = 1 << _IFS0_T2IF_POSITION;
   IEC0SET = 1 << _IEC0_T2IE_POSITION;
}


void timer_delay_ms(uint32_t ms)
{
   uint32_t start = _CP0_GET_COUNT();
   uint32_t duration = ms * (_XTAL_FREQ / 2000);
   while(_CP0_GET_COUNT() - start < duration);
}

void timer_delay_us(uint32_t us)
{
   uint32_t start = _CP0_GET_COUNT();
   uint32_t duration = us * (_XTAL_FREQ / 2000000);
   
   while(_CP0_GET_COUNT() - start < duration);
}

void __ISR(_TIMER_2_VECTOR, IPL1AUTO) _T2Interrupt (void)
{
   IFS0CLR = 1 << _IFS0_T2IF_POSITION;
   
   tm.ticker++;
   tm.ms_accum++;
      
   if (tm.ms_accum == 50)
   {
      tm.ms_accum = 0;
      pulse_service(50);
   }
}

/* 
 * Gets ticker in milliseconds. Overlaps in 49.7 days. 
 */
inline uint32_t timer_tick(void)
{
   return tm.ticker;
}
   
/* 
 * Gets epoch timer in seconds 
 */
uint32_t timer_epoch(void)
{
   return tm.epoch;
}

void timer_get_sync_time(uint32_t *epoch, uint32_t *tick)
{
   for(;;)
   {
      tm.isr = 0;
      *epoch = tm.epoch;
      *tick = tm.ticker;
      if(tm.isr) continue;
      break;
   }
}

/* 
 * Sets epoch timer in seconds 
 */
void timer_set_epoch(uint32_t epoch)
{
   for(;;)
   {
      tm.isr = 0;
      tm.epoch = epoch;
      if(tm.isr) continue;
      break;
   }
}

/* 
 * Adds a new software timer 
 */
size_t timer_add(TimerCb cb, uint32_t period, bool enabled, bool repeat)
{
   if(tm.timer_count >= COUNT(tm.timers))
   {
      DBG(kLvlError, "not enough timer slots (%u)", COUNT(tm.timers));
      return -1;
   }
   
   TimerEntry *timer = &tm.timers[tm.timer_count];
   
   timer->cb = cb;
   timer->period = period;
   timer->repeat = repeat;
   timer->enabled = enabled;
      
   if (enabled)
   {
      timer->started = timer_tick();
   }
   
   size_t handle = tm.timer_count++;
   
   return handle;
}

/* 
 * Timer service routine. This routine has to be called from the main loop
 * as often as possible. 
 */
void timer_service(void)
{
   TimerEntry *timer = &tm.timers[0];
   
   for(size_t i = 0; i < tm.timer_count; i++, timer++)
   {
      if(timer->enabled)
      {
         uint32_t tick = timer_tick();
         
         if((tick - timer->started) >= timer->period)
         {
            timer->enabled = timer->repeat;
            timer->started += timer->period;
            
            (*timer->cb)();
         }
      }
   }
}

/* 
 * Resets the counter and stars the timer.
 */
void timer_reset(size_t handle)
{
   if(handle >= tm.timer_count)
   {
      DBG(kLvlError, "invalid timer handle (%d)", handle);
      return;
   }
     
   TimerEntry *timer = &tm.timers[handle];
   timer->started = timer_tick();
   timer->enabled = true;  
}

/* 
 * Disables the timer.
 */
void timer_disable(size_t handle)
{
   if(handle >= tm.timer_count)
   {
      DBG(kLvlError, "invalid timer handle (%d)", handle);
      return;
   }
   
   tm.timers[handle].enabled = false;
}

/* 
 * Changes the period of a timer.
 */
void timer_set_period(size_t handle, uint32_t period)
{
   if(handle >= tm.timer_count)
   {
      DBG(kLvlError, "invalid timer handle (%d)", handle);
      return;
   }
   
   tm.timers[handle].period = period;
}
