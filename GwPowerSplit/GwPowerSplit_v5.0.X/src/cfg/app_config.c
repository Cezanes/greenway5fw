#include "app_config.h"
#include "sas/debug.h"
#include "lib/utils.h"

#include "../mcc_generated_files/mcc.h"
#include "hw_config.h"

#define APP_CONFIG_VERSION       1

const AppConfig app_def_config = 
{
   .crc = 0,
   .version = APP_CONFIG_VERSION,
   .timestamp = 0,
   .addr_local = 1,
};

/////////////////////////////////////////////////////////////////////////////////////

AppConfig app_config;

/////////////////////////////////////////////////////////////////////////////////////

static size_t app_get_hw_addr(const PinList * pins)
{
   size_t addr = 0;
   
   for(size_t i = 0; i < pins->count; i++)
   {
      pin_input(&pins->list[i]);
   }
   
   for(size_t i = 0; i < pins->count; i++)
   {
      addr <<= 1;
      if(!pin_read(&pins->list[i]))
         addr |= 1;
   }
   
   return addr;
}

void app_config_init(const DeviceConfig * device)
{   
   app_config.addr_local = app_get_hw_addr(&device->hwaddr);
}

size_t app_config_write(void)
{
   return kOK;
}