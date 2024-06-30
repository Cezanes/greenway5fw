#include "chronos.h"
#include "semaphore.h"

#include "sas/rtc.h"
#include "sas/gps.h"

#include "sal/debug.h"
#include "sal/timer.h"
#include "sal/pulse.h"

#include "cfg/app_config.h"
#include "cfg/hw_config.h"

#include "mcc_generated_files/tmr1.h"


#define CHRONO_ISR_PERIOD      125

static struct
{
   bool rtc_synced;
   bool have_time;

   bool have_gps;
   bool have_rtc;
   bool valid_gps;
   
   size_t gps_upd_skip_count;
   
   uint32_t last_tick;
   uint32_t sem_isr_duration;
   
   uint64_t epochms;
   uint64_t epochms_sem;
}chr;

#define chr_enable_tmr_isr()   IEC0SET = _IEC0_T1IE_MASK
#define chr_disable_tmr_isr()  IEC0CLR = _IEC0_T1IE_MASK
#define chr_clear_tmr_isr()    IFS0CLR = _IFS0_T1IF_MASK

static void on_rtc_tick(void);
static void (*rtc_tick_handler)(void);

////////////////////////////////////////////////////////////////////////////////////////

void __attribute__ ((weak)) TMR1_CallBack(void)
{
    if(rtc_tick_handler)
       rtc_tick_handler();
}

////////////////////////////////////////////////////////////////////////////////////////

void chronos_init(void)
{
   
}

static bool have_clock(void)
{
   TMR1_Counter16BitSet(0);
   uint16_t start = TMR1_Counter16BitGet();
   timer_delay_ms(10);
   uint16_t stop = TMR1_Counter16BitGet();
   
   uint32_t diff = stop - start;
   
   if(diff >= 300 && diff <= 350)
   {
      return true;
   }
   
   return false;
}


void chronos_start(void)
{
   bool forced = false;
   
   DateTime dt;
   chr.have_rtc = have_clock();
   
   if(forced || chr.have_rtc)
   {
      DBG(kLvlVerb, "chrono, have RTC clock");
      
      chr.have_time = rtc_is_valid() && rtc_get_datetime(&dt);
      if(!forced && !chr.have_time)
      {
         DBG(kLvlWarn, "chrono, invalid RTC values");
         pulse_start(kPulseNoTime);
      }
      else
      {
         uint8_t seconds = dt.seconds;
         
         /* Sync to second */
         uint32_t timeout = 2000;
         while(timeout > 0)
         {
            rtc_get_datetime(&dt);
            
            if(seconds != dt.seconds)
               break;
            
            timeout -= 50;
         }
         
         uint32_t utc = dte_get_epoch(&dt) - 1;
         chr.epochms = utc;
         chr.epochms *= 1000;
         chr.epochms_sem = chr.epochms;
         chr.have_time = true;
         
         utc += app_config.timezone;
         
         if(dte_is_daylight_saving(utc))
            utc += CA_SECONDS_PER_HOUR;
         
         dte_get_datetime(utc, &dt);
         
         DBG(kLvlInfo, "chrono, rtc %02u:%02u:%02u %02u.%02u.%02u %llu", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years, chr.epochms);
      }

      TMR1_Counter16BitSet(0);
      chr_clear_tmr_isr();
      rtc_tick_handler = &on_rtc_tick;
   }
   else
   {
      DBG(kLvlError, "chrono, no RTC clock available");
   }
}

static void on_rtc_tick(void)
{
   if (!chr.have_time)
   {
      return;
   }
   
   bool sem_update = false;
   uint32_t time_start = timer_tick();
  
   chr.epochms += CHRONO_ISR_PERIOD;
   chr.epochms_sem += CHRONO_ISR_PERIOD;

   if(chr.epochms > chr.epochms_sem)
   {
      uint64_t dif = chr.epochms - chr.epochms_sem;
      
      if(dif > 20)
         dif = 20;
            
      chr.epochms_sem += dif;
   }
   else if (chr.epochms_sem > chr.epochms)
   {
      uint64_t dif = chr.epochms_sem - chr.epochms;
      
      if(dif > 20)
         dif = 20;
            
      chr.epochms_sem -= dif;
   }
   
   uint32_t tick = (uint32_t)(chr.epochms_sem / 1000);
   tick += app_config.timezone;
   
   if(dte_is_daylight_saving(tick))
      tick += CA_SECONDS_PER_HOUR;
   
   static uint32_t last_milli = 0;
   uint32_t milli = (uint32_t)(chr.epochms_sem % 1000);
   
   if (chr.last_tick != tick || 
      (last_milli < 500 && milli >= 500) ||
      (last_milli >= 500 && milli < 500))
   {
      //if (chr.last_tick != tick)
      //   DBG(kLvlVerb, "chrono, tick %u %u %u", chr.last_tick, tick, milli);
      
      /*DateTime dt;
      dte_get_datetime(tick, &dt);
      DBG(kLvlInfo, "chrono, rtc %02u:%02u:%02u %02u.%02u.%02u %d", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years, (uint32_t)(chr.epochms - chr.epochms_sem));*/
      
      sem_tick(tick, milli);
      
      chr.last_tick = tick;
      last_milli = milli;
      
      //if (milli < 500)
      //   LATASET = 1 << 6;
      //else LATACLR = 1 << 6;
      
      sem_update = true;
   }
   
   if (sem_update)
      chr.sem_isr_duration = timer_tick() - time_start;
}

static void sync_time(const uint32_t value, const uint32_t milli)
{
   bool correction = false;
   
   chr_disable_tmr_isr();
   
   uint64_t now = (uint64_t)value * 1000;
   now += milli;
   
   if(chr.epochms > now && chr.epochms - now > CHRONO_ISR_PERIOD)
      correction = true;
   else if(now > chr.epochms && now - chr.epochms > CHRONO_ISR_PERIOD)
      correction = true;

   if (!correction)
   {
      chr.have_time = true;      
      
      uint32_t ticks = milli / CHRONO_ISR_PERIOD;
      chr.epochms = (uint64_t)value * 1000;
      chr.epochms += ticks * CHRONO_ISR_PERIOD;
      
      uint32_t counter = (milli % CHRONO_ISR_PERIOD) * TMR1_Period16BitGet() / CHRONO_ISR_PERIOD;
      
      TMR1_Counter16BitSet(counter);
      chr_clear_tmr_isr();
      chr_enable_tmr_isr();
      
      return;
   }
   
   DateTime dt;
   dte_get_datetime(value, &dt);
   DBG(kLvlVerb, "chrono, gps %02u:%02u:%02u %02u.%02u.%02u %llu", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years, now);
   
   dte_get_datetime((uint32_t)(chr.epochms / 1000), &dt);
   DBG(kLvlVerb, "chrono, sem %02u:%02u:%02u %02u.%02u.%02u %llu", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years, chr.epochms);
   
   chr.epochms = now;
   TMR1_Counter16BitSet(0);
   chr_clear_tmr_isr();

   uint32_t sem_period = sem_get_period(value);
   sem_period *= 1000;
   
   if(sem_period == 0 || !chr.have_time)
   {
      chr.epochms_sem = now;
      chr.have_time = true;
      chr_enable_tmr_isr();
      DBG(kLvlVerb, "chrono, time available");
      return;
   }
   
   if(now > chr.epochms_sem)
   {
      uint64_t epoch_shift;
      uint64_t loops;
      
      epoch_shift = now - chr.epochms_sem;
      loops = epoch_shift / sem_period;
      
      if(loops > 0)
      {
         chr.epochms_sem += loops * sem_period;
      }
   }
   else
   {
      uint64_t epoch_shift = chr.epochms_sem - now;
      uint64_t loops = epoch_shift / sem_period;
      
      if(loops > 0)
      {
         chr.epochms_sem -= loops * sem_period;
      }
   }
   
   chr_enable_tmr_isr();
      
   DBG(kLvlVerb, "chrono, GPS time shift of %lld ms", (int64_t)(chr.epochms - chr.epochms_sem));

   if(chr.have_rtc)
   {
      DateTime dt;
      dte_get_datetime(value, &dt);
      DBG(kLvlVerb, "chrono, RTC updated %02u:%02u:%02u %02u.%02u.%02u", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years);
      rtc_set_datetime(&dt);
   }
}


uint32_t chronos_get_time(void)
{
   return chr.epochms / 1000;
}

uint64_t chronos_get_full_time(void)
{
   return chr.epochms;
}

void chronos_test_next(void)
{
   static bool first = true;
   
   if(first)
   {
      first = false;
      chr.epochms_sem = 0;
      chr.epochms = 0;
   }
   else
   {
      chr.epochms_sem += 1000;
      chr.epochms += 1000;
   }
   
   //uint32_t milli = (uint32_t)(chr.epochms_sem / 1000);
   //DBG(kLvlInfo, "chrono, milli %u", (milli % 12) + 1);
}

void chronos_set_rtc(uint32_t time)
{
   DateTime dt;
   dte_get_datetime(time, &dt);
   DBG(kLvlInfo, "chrono, RTC updated %02u:%02u:%02u %02u.%02u.%02u", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years);
   rtc_set_datetime(&dt);
   chr.have_time = true;
}

void chronos_set_time(uint32_t value, uint32_t milli)
{
   chr_disable_tmr_isr();
   chr.epochms = (uint64_t)value * 1000;
   chr.epochms += milli;
   chr.epochms_sem = chr.epochms;
   chr.last_tick = 0;
   TMR1_Counter16BitSet(0);
   chr_clear_tmr_isr();
   chr_enable_tmr_isr();
   
   DBG(kLvlInfo, "chrono, new time %u", value);
   
   chronos_set_rtc(value);
}

void chronos_update_time(uint32_t value, uint32_t milli)
{
   if (!chr.have_time)
   {
      chronos_set_time(value, milli);
      pulse_stop(kPulseNoTime);
   }
   else
   {
      sync_time(value, milli);
   }
}

void chronos_rad_time_upd(const uint32_t value, const uint32_t milli)
{
   if (gps_have_time())
      return;
   
   //uint64_t epoch = chr.epochms;
   //uint32_t counter = TMR1_Counter16BitGet();
   
   //TMR1_Counter16BitSet(0);
   //chr_clear_tmr_isr();
   chronos_update_time(value, 0);
   
   DBG(kLvlInfo, "chrono, timer updated trough radio %u %u", value, milli);
}

void chronos_gps_time_upd(const uint32_t value)
{
   if(chr.gps_upd_skip_count > 0 && chr.valid_gps)
   {
      chr.gps_upd_skip_count--;
      return;
   }
   
   /*static uint32_t last = 0;
   uint32_t now = timer_tick();
   uint32_t dur = now - last;
   last = now;
   DBG(kLvlVerb, "gps, %u", dur);*/
   
   chr.gps_upd_skip_count = 9;
   chr.valid_gps = true;
   
   chronos_update_time(value, 0);
}


void chronos_service(void)
{
   static uint32_t last_sem_duration = 123;
   if (last_sem_duration != chr.sem_isr_duration)
   {
      // DBG(kLvlVerb, "chrono, isr duration %u", chr.sem_isr_duration);
      last_sem_duration = chr.sem_isr_duration;
   }
}
