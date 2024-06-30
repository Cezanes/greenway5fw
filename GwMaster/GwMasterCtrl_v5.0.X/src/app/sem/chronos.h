#ifndef CHRONOS_H
#define CHRONOS_H

#include "types.h"

void chronos_init(void);
void chronos_start(void);
void chronos_service(void);

void chronos_gps_time_upd(const uint32_t value);
void chronos_rtc_time_upd(const uint32_t value);
void chronos_rad_time_upd(const uint32_t value, const uint32_t milli);

uint32_t chronos_get_time(void);
uint64_t chronos_get_full_time(void);
void chronos_set_time(uint32_t value, uint32_t milli);

void chronos_test_next(void);


#endif