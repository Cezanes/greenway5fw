#include "hw_config.h"
#include "sas/pulse.h"
#include "hal/uart32mx.h"

#include "mcc_generated_files/mcc.h"


///////////////////////////////////////////////////////////////////////////////


// High first
static const Pin pin_hw_addr[] = 
{
   PIN_DEF(F, 1),
   PIN_DEF(E, 0), 
   PIN_DEF(E, 1), 
   PIN_DEF(E, 2), 
};

static const PulseInstance pu_inst[] = 
{
   {
      .period_on = 250,       // kPulseMainsPowerError
      .period_off = 250,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 3,
      .pin_port_set = &LATESET,
      .pin_port_clr = &LATECLR,
   },
   {
      .flags = kPulseStartActive,
      .period_on = 550,       // kPulseHostSync
      .period_off = 0,
      .total_pulses = 2,
      .pin_mask = 1 << 4,
      .pin_port_set = &LATESET,
      .pin_port_clr = &LATECLR,
   },
};

const HwConfig hw_config = 
{
   .device = {
      .hwaddr = {
         .list = pin_hw_addr,
         .count = COUNT(pin_hw_addr),
      },
   },
   
   .debug = {
      .buff = (uint8_t[1024]){},
      .buff_size = 1024,
      .baud = 460800,
      .clock_src = _XTAL_FREQ,
      .uart = &Uart[0],
   },
   
   .pulse = {
      .inst = pu_inst,
      .count = COUNT(pu_inst),
   },
   
   .hctrl = 
   {
      .can = 
      {
         .clock = {
            .phaseSeg1Tq = 3,
            .phaseSeg2Tq = 3,
            .propagationSegTq = 3,
            .phaseSeg2TimeSelect = true,
            .sample3Time = true,
            .syncJumpWidth = 2,
            .can_baud = 125000,
            .sys_clock = _XTAL_FREQ,
         },
         .mode_timeout = 1000,
      },

      .pin_led_error = PIN_DEF(E, 3),
      .pin_led_warning = PIN_DEF(E, 4),      
   },
   
   .bulb_ctrl = 
   {
      .pin_sig_sense = PIN_DEF(B, 4),
      .sig_port = &PORTB,
      .sig_port_mask = 1 << 2,
      .main_power_timeout = 6 * 1000,
      
      .pin_power_hot = PIN_DEF(B, 14),
      .pin_power_neutral = PIN_DEF(B, 15),
   },
};



void hw_config_init(void)
{
   SYSTEM_RegUnlock(); // unlock PPS
   CFGCONbits.IOLOCK = 0;

   C1RXRbits.C1RXR = 0x0003;
   RPD10Rbits.RPD10R = 0x000C;

   CFGCONbits.IOLOCK = 1; // lock   PPS
   SYSTEM_RegLock(); 
}