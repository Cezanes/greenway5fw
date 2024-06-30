/*
 * File:   pulse.h
 * Author: cezane
 *
 * Pulse IO driver that 'blinks' IO pins in a specific pattern.
 * Supports multiple pins and multiple patterns.
 */


#ifndef PULSE_H
#define PULSE_H

#include "types.h"

enum
{
   kPulseEnable      = 1,
   kPulseActive      = 2,
   kPulseRevPolarity = 4,
   kPulseStartActive = 8,
   kPulseCloseActive = 16,
   kPulseInfinite    = 0xFF,
};

/* Defines the pin and the pattern for a specific IO*/
typedef struct
{
   volatile uint32_t * volatile pin_port_set;
   volatile uint32_t * volatile pin_port_clr;
   const uint32_t pin_mask;
   const uint32_t period_on;
   const uint32_t period_off;
   const size_t total_pulses;
   const size_t flags;
} PulseInstance;

typedef struct
{
   const PulseInstance * inst;
   size_t count;
} PulseConfig;


void pulse_init(const PulseConfig * config);
void pulse_set_isr(const size_t index, const bool en);
void pulse_start(const size_t index);
void pulse_reset(const size_t index);
void pulse_start_count(const size_t index, const size_t count);
void pulse_stop(const size_t index);
void pulse_service(const uint32_t mili);

#endif