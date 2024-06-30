#ifndef HOST_CTRL_H
#define HOST_CTRL_H

#include "hal/pin32.h"
#include "ssl/canbus.h"


typedef struct
{
   CanBusConfig can;
   size_t bulb_count;
   Pin pin_led_error;
   Pin pin_led_warning;
} HCtrlConfig;

void hctrl_reset(void);
void hctrl_flag(bool set, uint32_t flag);

void hctrl_init(const HCtrlConfig * config);
void hctrl_start(void);
void hctrl_service(void);

#endif