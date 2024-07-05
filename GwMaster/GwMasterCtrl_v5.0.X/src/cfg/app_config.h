#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "types.h"
#include "sas/lora.h"

#include "app/sem/semaphore.h"
#include "app/logic/state.h"

enum
{
   kStorageSectorAppCfg = 0,
   kStorageSemProg,
   kStorageSemDesc,
};

typedef struct __attribute__ ((packed))
{
   uint8_t version;
   uint16_t size;
   uint32_t timestamp;
   int32_t timezone;
   bool have_gsm;
   NetworkConfig net;
   RadioConfig radio;
   ComData com;
   uint16_t crc;
} AppConfig;

extern AppConfig app_config;

void app_config_read(void);
size_t app_config_write(void);


#endif