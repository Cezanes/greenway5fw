/*
 * File:   timer.h
 * Author: cezane
 *
 * Software timer implementation. Supports unlimited timers with 
 * millisecond resolution. 
 */

#ifndef TIMER_H
#define TIMER_H

#include "types.h"


#define TM_MLS_T0_TICK(mili)                    (((uint32_t)mili))
#define TM_SEC_T0_TICK(sec)               (((uint32_t)sec) * 1000)
#define TM_MIN_T0_TICK(min)          (((uint32_t)min) * 60 * 1000)
#define TM_HRS_T0_TICK(hrs)     (((uint32_t)hrs) * 60 * 60 * 1000)
#define TM_TICK_TO_MLS(tics)                    (((uint32_t)tics))

typedef void (*TimerCb)(void);

void timer_init();
void timer_set_epoch(uint32_t epoch);
void timer_delay_ms(uint32_t ms);
void timer_delay_us(uint32_t us);

void timer_reset(size_t handle);
void timer_disable(size_t handle);
uint32_t timer_get_period(size_t handle);
void timer_set_period(size_t handle, uint32_t period);

void timer_service();

uint32_t timer_tick();
uint32_t timer_epoch();
void timer_get_sync_time(uint32_t *epoch, uint32_t *tick);

size_t timer_add(TimerCb cb, uint32_t period, bool enabled, bool repeat);

#endif

