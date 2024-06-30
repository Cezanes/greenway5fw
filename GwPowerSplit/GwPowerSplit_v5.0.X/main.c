#include "mcc_generated_files/mcc.h"

#include "cfg/hw_config.h"
#include "cfg/app_config.h"
#include "sas/debug.h"
#include "sas/timer.h"
#include "ssl/bulbctrl.h"
#include "app/hostctrl.h"

int main(void)
{
   SYSTEM_Initialize();

   hw_config_init();
   timer_delay_ms(100);
   
   app_config_init(&hw_config.device);
   
   dbg_init(&hw_config.debug);
   timer_init();
   
   DBGLN(kLvlInfo); DBGLN(kLvlInfo);
   DBG(kLvlInfo, "application init addr %u reset %X", app_config.addr_local, RCON);
   RCONCLR = 0xFF;
   
   pulse_init(&hw_config.pulse);
   bulb_ctrl_init(&hw_config.bulb_ctrl);
   hctrl_init(&hw_config.hctrl);

   INTERRUPT_Initialize();
   
   bulb_ctrl_start();
   
   while (1)
   {
      timer_service();
      bulb_ctrl_service();
      hctrl_service();
      WDTCONSET = 1;
   }

   return 0;
}
