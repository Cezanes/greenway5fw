#ifndef BULB_CTRL_H
#define BULB_CTRL_H

#include "hal/pin32.h"
#include "types.h"

typedef struct
{
   Pin pin_sig_sense;
   volatile uint32_t * sig_port;
   size_t sig_port_mask;
   
   const Pin * pin_out;
   size_t pin_out_count;
   bool out_pol_invert;
   
   const Pin * pin_mux;
   size_t pin_mux_count;
   
   const Pin * pin_led;
   size_t pin_led_count;
   bool led_pol_invert;
   
   const uint32_t * map_triac_sense;
   size_t map_triac_sense_count;
   
   uint32_t main_power_timeout;
   uint32_t power_noise_floor;
   uint32_t power_on_burnt_thresh;
   uint32_t power_off_burnt_thresh;
   uint32_t switch_on_fail_thresh;
   uint32_t switch_off_fail_thresh;
   
   size_t skip_on_phases;
   size_t skip_off_phases;
   
} BulbConfig;



void bulb_ctrl_init(const BulbConfig * config);
void bulb_ctrl_start(void);
void bulb_ctrl_clear(void);
void bulb_ctrl_set(size_t index, bool en);
void bulb_ctrl_set_map(uint32_t map);
void bulb_ctrl_set_cfg(uint32_t burnt_timeout, uint32_t main_power_timeout);
void bulb_ctrl_monitor(bool en);
void bulb_ctrl_mux(size_t index);
size_t bulb_ctrl_get_index();
uint32_t bulb_ctrl_burnt_bulb_map(void);
uint32_t bulb_ctrl_burnt_triac_map(void);
bool bulb_ctrl_have_power(void);
void bulb_ctrl_print(void);

void bulb_ctrl_service(void);

#endif