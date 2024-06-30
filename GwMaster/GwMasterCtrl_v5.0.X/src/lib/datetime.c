#include "datetime.h"

#include "types.h"



#define LEAPYEAR(year)   (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)   (LEAPYEAR(year) ? 366 : 365)

const size_t ytab[2][12] = 
{
   {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
   {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

uint32_t dte_epoch_seconds_from_monday(uint32_t epoch)
{
   epoch += 4 * CA_SECONDS_PER_DAY;
   epoch %= CA_SECONDS_PER_WEEK;
   return epoch;
}

uint32_t dte_epoch_day_of_week_seconds(uint32_t epoch)
{
   epoch = epoch % CA_SECONDS_PER_WEEK;
   return epoch;
}

size_t dte_epoch_day_of_week(uint32_t epoch)
{
   epoch = epoch % CA_SECONDS_PER_WEEK;
   
   size_t day = epoch / CA_SECONDS_PER_DAY;
   day = (day + 3) % CA_DAYS_PER_WEEK;
   
   return day;
}

DateTime * dte_get_datetime(uint32_t epoch, DateTime * date)
{
   date->week_day = dte_epoch_day_of_week(epoch);
   
   uint32_t dayno = epoch / CA_SECONDS_PER_DAY;
   size_t year = CA_EOPOCH_YEAR;
   
   size_t year_size = YEARSIZE(year);
   while(dayno >= year_size)
   {
      dayno -= year_size;
      year++;
      year_size = YEARSIZE(year);
   }
   
   size_t leap_year = LEAPYEAR(year);
   size_t mth = 0;
   
   size_t mdays = ytab[leap_year][mth];
   while (dayno >= mdays)
   {
      dayno -= mdays;
      mth++;
      mdays = ytab[leap_year][mth];
   }
   
   date->days = dayno + 1;
   date->months = mth + 1;
   date->years = year;
   
   // Extract only seconds relative to a day.
   epoch %= CA_SECONDS_PER_DAY;
      
   // Get the hour.
   date->hours = 0;
   while(epoch >= CA_SECONDS_PER_HOUR)
   {
      epoch -= CA_SECONDS_PER_HOUR;
      (date->hours)++;
   }
   
   // Get the minute & second
   date->minutes = epoch / CA_SECONDS_PER_MINUTE;
   date->seconds = epoch % CA_SECONDS_PER_MINUTE;
   
   return date;
}

uint32_t dte_get_epoch(const DateTime * dt)
{
   uint32_t epoch = dt->seconds;
   
   epoch += (uint32_t)dt->minutes * CA_SECONDS_PER_MINUTE;
   epoch += (uint32_t)dt->hours * CA_SECONDS_PER_HOUR;
   epoch += ((uint32_t)dt->days - 1) * CA_SECONDS_PER_DAY;
   
   size_t leap_year = LEAPYEAR(dt->years);
   uint32_t ydays = 0;
   
   for(size_t i = 0; i < dt->months - 1; i++)
   {
      ydays += ytab[leap_year][i];
   }
   
   epoch += ydays * CA_SECONDS_PER_DAY;
   
   uint32_t year = ((uint32_t)dt->years - CA_EOPOCH_YEAR) * CA_SECONDS_PER_YEAR;
   epoch += year;
   
   year = ((uint32_t)dt->years - CA_EOPOCH_YEAR + 1) / 4 * CA_SECONDS_PER_DAY;
   year -= (((uint32_t)dt->years - 1900) - 1) / 100 * CA_SECONDS_PER_DAY;
   epoch += year;
   
   year = (((uint32_t)dt->years - 1900) + 299) / 400 * CA_SECONDS_PER_DAY;
   epoch += year;
   
   return epoch;
}

static uint8_t dte_dec_to_uint8(const uint8_t *dec)
{
   uint8_t res = (dec[0] - '0') * 10;
   return res + (dec[1] - '0');
}

void dte_get_gps_datetime(const uint8_t * time, const uint8_t * date, DateTime * dt)
{
   dt->hours = dte_dec_to_uint8(&time[0]);
   dt->minutes = dte_dec_to_uint8(&time[2]);
   dt->seconds = dte_dec_to_uint8(&time[4]);
   
   dt->days = dte_dec_to_uint8(&date[0]);
   dt->months = dte_dec_to_uint8(&date[2]);
   dt->years = dte_dec_to_uint8(&date[4]) + 2000;
   
   dt->week_day = 0;
}

bool dte_is_valid(const DateTime * dt)
{
   if(dt->seconds > 60 || dt->minutes > 60 || dt->hours > 24)
   {
      return false;
   }
   
   if(dt->days > 31 || dt->days == 0 || dt->months > 12 || dt->months == 0)
   {
      return false;
   }
   
   if(dt->years < 1970 || dt->years > 2100)
   {
      return false;
   }
   
   return true;
}

bool dte_is_daylight_saving(uint32_t epoch)
{
   // aplicabil? din ultima duminic? a lunii martie, ora 3.00, care devine ora 4.00, pân? la ultima duminic? a lunii octombrie, 
   // ora 4.00, care devine ora 3.00
   
   DateTime dt;
   dte_get_datetime(epoch, &dt);
   
   DateTime ref = {
      .days = 1,
      .hours = 3,
      .months = 4,
      .years = dt.years,
   };
   
   uint32_t dls_begin = dte_get_epoch(&ref) - CA_SECONDS_PER_DAY;
   
   for(;;)
   {
      if(dte_epoch_day_of_week(dls_begin) == 6)
         break;
      dls_begin -= CA_SECONDS_PER_DAY;
   }
       
   ref = (DateTime) {
      .days = 1,
      .hours = 4,
      .months = 11,
      .years = dt.years,
   };
   
   uint32_t dls_end = dte_get_epoch(&ref) - CA_SECONDS_PER_DAY;
   
   for(;;)
   {
      if(dte_epoch_day_of_week(dls_end) == 6)
         break;
      dls_end -= CA_SECONDS_PER_DAY;
   }
   
   if(epoch > dls_begin && epoch <= dls_end)
      return true;
      
   return false;
}
