#ifndef RTC_H
#define RTC_H

#include "types.h"
#include "drv/pcf2129t.h"

typedef struct
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   uint32_t ss_mask;
   uint8_t (* spi_xfer)(uint8_t);
} RtcConfig;

void rtc_init(const RtcConfig * const config);
bool rtc_start(void);
bool rtc_is_valid(void);
bool rtc_get_datetime(DateTime * const time);
bool rtc_set_datetime(const DateTime * const time);


#endif