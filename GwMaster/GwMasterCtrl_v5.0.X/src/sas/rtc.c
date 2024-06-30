
#include "rtc.h"
#include "sal/debug.h"

#include "mcc_generated_files/spi3.h"

void rtc_init(const RtcConfig * const config)
{
   const Pcf2129tConfig cfg = {
      .ss_reg_set = config->ss_reg_set,
      .ss_reg_clear = config->ss_reg_clear,
      .ss_mask = config->ss_mask,
      .spi_xfer = config->spi_xfer,
   };
   
   pcf2129t_init(&cfg);
}

bool rtc_start()
{
   if(!pcf2129t_is_valid())
   {
      DBG(kLvlError, "rtc, IC is not responding");
      return false;
   }
   
   DateTime time;
   
   if(!rtc_get_datetime(&time))
   {
      DBG(kLvlError, "rtc, failed to read datetime");
      return false;
   }
   
   DBG(kLvlInfo, "rtc, %02u:%02u:%02u %02u.%02u.%02u", time.hours, time.minutes, time.seconds, time.days, time.months, time.years);
   
   return true;
}

bool rtc_is_valid(void)
{
   return pcf2129t_is_valid();
}

bool rtc_get_datetime(DateTime * const time)
{  
   if(!pcf2129t_get_datetime(time))
   {
      DBG(kLvlError, "rtc, fail to read date/time");
      return false;
   }
   
   if(time->seconds > 60 || time->minutes > 60 || time->hours > 24)
   {
      DBG(kLvlError, "rtc, invalid time format %02u:%02u:%02u", time->hours, time->minutes, time->seconds);
      return false;
   }
   
   if(time->days > 31 || time->days == 0 || time->months > 12 || time->months == 0)
   {
      DBG(kLvlError, "rtc, invalid date format %02u.%02u.%04u", time->days, time->months, time->years);
      return false;
   }
   
   return true;
}

bool rtc_set_datetime(const DateTime * const time)
{
   return pcf2129t_set_datetime(time);
}
