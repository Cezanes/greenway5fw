#include "app_config.h"
#include "lib/utils.h"
#include "sas/storage.h"
#include "sal/debug.h"

#include "mcc_generated_files/mcc.h"
#include "hw_config.h"


#define RH_RF95_FXOSC  (32000000.0) 
#define RH_RF95_FSTEP  (RH_RF95_FXOSC / 524288)

#define APP_CONFIG_VERSION       1

const AppConfig app_def_config = 
{
   .crc = 0,
   .version = APP_CONFIG_VERSION,
   .timestamp = 0,
   
   .timezone = (int32_t) 2 * 60 * 60,
   
   .net = 
   {
      .addr_network = 1,
      .addr_local = 1,
   },
   
   .radio = 
   {
      .bandwidth_index = 0,
      .tx_power = 23,
      .preamble_len = 8,
      .freq = (868 * 1000000.0) / RH_RF95_FSTEP,
      .blob_burst_count = 20,
      .msg_process_period = 100,
   },

   .com = {
      .cell = {
         .user_count = 1,
         .users = {
            {kCellUserRoleOfficer, "0745098213", "Cezane"}, 
            //{kCellUserRoleOfficer, "0101", "Debug"}, 
            //{kCellUserRoleOfficer, "0751078989", "Marty"}, 
         },
      },
   },
};

/////////////////////////////////////////////////////////////////////////////////////

AppConfig app_config;

static const uint32_t config_flash_size = (sizeof(AppConfig) + 0x07) & ((uint32_t)~0x07);
static uint32_t inst_index = 0;

/////////////////////////////////////////////////////////////////////////////////////

static void app_get_hw_addr(void)
{
   app_config.net.addr_local = 0;
      
   for(size_t i = 0; i < hw_config.boot.addr.count; i++)
   {
      pin_input(&hw_config.boot.addr.list[i]);
      
      app_config.net.addr_local <<= 1;
      if(pin_read(&hw_config.boot.addr.list[i]) == 0)
         app_config.net.addr_local += 1;
   }

   app_config.net.addr_network = 0;
   for(size_t i = 0; i < hw_config.boot.net.count; i++)
   {
      pin_input(&hw_config.boot.net.list[i]);
      
      app_config.net.addr_network <<= 1;
      if(pin_read(&hw_config.boot.net.list[i]) == 0)
         app_config.net.addr_network += 1;
   }
   
   if(app_config.net.addr_network == 0)
      app_config.net.addr_network = 1;
   
   pin_input(&hw_config.boot.modem_present);
   app_config.have_gsm = false; //pin_read(&hw_config.boot.modem_present) == 0;
}

void app_config_read(void)
{
   const uint8_t * addr = storage_get_ptr(kStorageSectorAppCfg);
   const uint32_t flash_size = storage_get_size(kStorageSectorAppCfg);
   
   app_config = app_def_config;
   
   if(addr == NULL || flash_size == 0)
   {
      DBG(kLvlError, "cfg, invalid storage configuration");
      app_get_hw_addr();
      return;
   }

   uint32_t inst_count = flash_size / config_flash_size;
   
   inst_index = 0;
   
   for(uint32_t i = 0; i < inst_count; i++)
   {
      const AppConfig * flash_cfg = (const AppConfig *) addr;
      
      uint16_t crc = utils_crc16t(flash_cfg, sizeof(AppConfig) - sizeof(app_config.crc), CRC_START_CCITT_1D0F);
      
      //DBGHEX(kLvlDbg, "read ", flash_cfg, sizeof(AppConfig));
      
      if(flash_cfg->crc == crc)
      {
         if(flash_cfg->timestamp > app_config.timestamp)
         {
            app_config = *flash_cfg;
         }
         
         inst_index = i;
      }
      
      addr += config_flash_size;
   }

   if (app_config.timestamp == 0)
   {
      DBG(kLvlWarn, "cfg, no flash config found");
   }
   else
   {
      DBG(kLvlVerb, "cfg, found flash config at %u", inst_index);
   }
   
   app_get_hw_addr();
}

size_t app_config_write(void)
{
   const uint8_t * addr = storage_get_ptr(kStorageSectorAppCfg);
   const uint32_t flash_size = storage_get_size(kStorageSectorAppCfg);
   const uint32_t inst_count = flash_size / config_flash_size;
   
   inst_index++;
   
   if (inst_index >= inst_count || app_config.timestamp == app_def_config.timestamp)
   {
      bool req_erase = false;
      const uint8_t *ptr = addr;
      
      for(uint32_t i = 0; i < flash_size; i++, ptr++)
      {
         if (*ptr != 0xFF)
         {
            req_erase = true;
            break;
         }
      }
      
      if (req_erase)
      {
         storage_erase(kStorageSectorAppCfg);
      }
      
      inst_index = 0;
   }
   
   app_config.timestamp++;
   app_config.crc = utils_crc16t(&app_config, sizeof(AppConfig) - sizeof(app_config.crc), CRC_START_CCITT_1D0F);
   
   addr += inst_index * config_flash_size;
   
   if(!storage_write_words(kStorageSectorAppCfg, addr, &app_config, sizeof(AppConfig)))
   {
      DBG(kLvlError, "cfg, could not write config into flash");
      return kErrorFlash;
   }
   
   DBG(kLvlVerb, "cfg, config saved %u", inst_index);
   
   return kOK;
}