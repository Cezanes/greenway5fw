#include "bulbctrl.h"

#include "sas/timer.h"
#include "sas/debug.h"
#include "sas/pulse.h"

#include "cfg/hw_config.h"

#include <stdio.h>


typedef struct
{
   BulbConfig config;

   uint32_t last_port;
   size_t monitoring;
   
   bool isr_phase;
   bool have_phase;
   uint32_t time_last_phase;

   uint32_t main_power_timeout;

   uint32_t errors;
   
   uint32_t time_phase;
   uint32_t time_timer;
      
} BulbCtrlInt;


////////////////////////////////////////////////////////////////////////////////////////////////////


static BulbCtrlInt bc;
static void on_phase_start(void);


////////////////////////////////////////////////////////////////////////////////////////////////////


void __ISR (_CHANGE_NOTICE_VECTOR, IPL4AUTO) _CHANGE_NOTICE ( void )
{
   if(IFS1bits.CNBIF)
   {
      uint32_t port = *bc.config.sig_port;
      uint32_t mod = bc.last_port ^ port;
      
      if(mod & bc.config.sig_port_mask && (port & bc.config.sig_port_mask))
      {
         on_phase_start();
      }     
     
      bc.last_port = port;
      IFS1CLR = 1 << _IFS1_CNBIF_POSITION;
   }
}

static void on_phase_start(void)
{
   if(!bc.monitoring)
      return;

   bc.isr_phase = true;
}

static void on_main_power_changed(bool on)
{
   if(on)
   {
      if(!bc.have_phase)
      {
         DBG(kLvlWarn, "main power ON");
      }
      
      bc.have_phase = true;
      bc.time_last_phase = timer_tick();
      pulse_enable(kPulseMainsPowerError, false);
   }
   else
   {
      bc.have_phase = false;
      DBG(kLvlWarn, "main power OFF");
      pulse_enable(kPulseMainsPowerError, true);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void bulb_ctrl_init(const BulbConfig * config)
{
   bc = (BulbCtrlInt){
      .config = *config,
   };
   
   bc.have_phase = true;
   bc.main_power_timeout = bc.config.main_power_timeout;
   
   pin_input(&bc.config.pin_sig_sense);
   
   pin_write(&bc.config.pin_power_hot, 0);
   pin_write(&bc.config.pin_power_neutral, 0);
   
   pin_output(&bc.config.pin_power_hot);
   pin_output(&bc.config.pin_power_neutral);

	CNCONBbits.ON = 1;
	CNENBbits.CNIEB2 = 1; // Pin : RB2
}

void bulb_ctrl_start(void)
{
   IFS1bits.CNBIF = 0;
   IEC1bits.CNBIE = 1;
   bulb_ctrl_monitor(true);
}


void bulb_ctrl_set_cfg(uint32_t burnt_timeout, uint32_t main_power_timeout)
{
   bc.main_power_timeout = main_power_timeout;
}

void bulb_ctrl_set_power(bool en)
{
   pin_write(&bc.config.pin_power_hot, en);
   pin_write(&bc.config.pin_power_neutral, en);
}

void bulb_ctrl_monitor(bool en)
{   
   bc.monitoring = en;
}

bool bulb_ctrl_have_power(void)
{
   return bc.have_phase;
}

void bulb_ctrl_service(void)
{
   if(bc.isr_phase)
   {
      bc.isr_phase = false;
      on_main_power_changed(true);
   }
   
   if(bc.have_phase)
   {
      if(timer_tick() - bc.time_last_phase >= bc.main_power_timeout)
      {
         bc.have_phase = false;
         on_main_power_changed(false);
      }
   }
}