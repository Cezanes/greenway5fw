#include "mcc_generated_files/mcc.h"

#include "sal/debug.h"
#include "sal/timer.h"
#include "sal/buttons.h"
#include "sal/pulse.h"

#include "sas/rtc.h"
#include "sas/gps.h"

#include "cfg/app_config.h"
#include "cfg/hw_config.h"

#include "app/out/power_ctrl.h"
#include "app/sem/semaphore.h"
#include "app/sem/chronos.h"
#include "app/net/cellular.h"
#include "app/net/serial.h"
#include "app/logic/state.h"
#include "app/logic/logic.h"
#include "app/net/radio.h"

int main(void)
{ 
   SYSTEM_Initialize();

   timer_delay_ms(100);
   
   hw_config_init();
   dbg_init(&hw_config.debug);

   DBGLN(kLvlInfo); DBGLN(kLvlInfo);
   DBG(kLvlInfo, "application init %X", RCON);
   RCONCLR = 0xFF;
   
   pulse_init(&hw_config.pulse);
   pulse_start(kPulseBooting);
   
   timer_init();
   shared_buff_init(&hw_config.shabuff);
   storage_init(&hw_config.storage);
   app_config_read();

   rtc_init(&hw_config.rtc);
   gps_init(&hw_config.gps);
   
   radio_init(&app_config.net, &app_config.radio, &hw_config.radio);
   btn_init(&hw_config.buttons);
   sem_init(&hw_config.sem);
   pctrl_init(&hw_config.pctrl);
   
   serial_init(&hw_config.srv);
   chronos_init();
   state_init(&app_config.com, &hw_config.com);
   logic_init();
   
   timer_delay_ms(100);
   
   DBG(kLvlInfo, "application start, addr %u, net %u, modem %u", app_config.net.addr_local, app_config.net.addr_network, app_config.have_gsm);

   gps_start();
   radio_start();
   serial_start();
   sem_start();
   chronos_start();
   state_start();
   logic_start();
   
   pulse_stop(kPulseBooting);

   for(;;)
   {
      timer_service();
      chronos_service();
      gps_service();
      radio_service();
      serial_service();
      btn_service();
      logic_service();
      pctrl_service();
      sem_service();
      state_service();
      
      WDTCONSET = 1;
   }

   return 0; 
}
