#ifndef CALENDAR_H
#define CALENDAR_H

#include "types.h"


#define CA_SECONDS_PER_YEAR    31536000
#define CA_SECONDS_PER_WEEK      604800
#define CA_SECONDS_PER_DAY        86400
#define CA_SECONDS_PER_HOUR        3600
#define CA_SECONDS_PER_MINUTE        60
#define CA_DAYS_PER_WEEK              7
#define CA_EOPOCH_YEAR             1970


typedef struct
{
   size_t seconds;
   size_t minutes;
   size_t hours;
   size_t days;
   size_t week_day;
   size_t months;
   size_t years;
} DateTime;

uint32_t dte_epoch_seconds_from_monday(uint32_t epoch);
uint32_t dte_epoch_week_seconds(uint32_t epoch);
size_t dte_epoch_day_of_week(uint32_t epoch);
DateTime * dte_get_datetime(uint32_t epoch, DateTime * dt);
uint32_t dte_get_epoch(const DateTime * dt);

void dte_get_gps_datetime(const uint8_t * time, const uint8_t * date, DateTime * dt);
bool dte_is_valid(const DateTime * dt);
bool dte_is_daylight_saving(uint32_t epoch);

char * dte_to_str(const DateTime * dt);

#endif
