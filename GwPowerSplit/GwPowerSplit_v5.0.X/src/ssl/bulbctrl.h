#ifndef BULB_CTRL_H
#define BULB_CTRL_H

#include "hal/pin32.h"
#include "types.h"

typedef struct
{
   Pin pin_sig_sense;
   volatile uint32_t * sig_port;
   size_t sig_port_mask;
   
   Pin pin_power_hot;
   Pin pin_power_neutral;
   
   uint32_t main_power_timeout;
   
} BulbConfig;



void bulb_ctrl_init(const BulbConfig * config);
void bulb_ctrl_start(void);
void bulb_ctrl_set_cfg(uint32_t burnt_timeout, uint32_t main_power_timeout);
void bulb_ctrl_set_power(bool en);
bool bulb_ctrl_have_power(void);
void bulb_ctrl_monitor(bool en);

void bulb_ctrl_service(void);

#endif