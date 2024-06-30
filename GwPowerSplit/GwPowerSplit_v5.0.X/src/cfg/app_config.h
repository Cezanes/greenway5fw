#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "types.h"
#include "hw_config.h"

typedef struct __attribute__ ((packed))
{
   uint8_t version;
   uint16_t size;
   uint32_t timestamp;
   size_t addr_local;
   uint16_t crc;
} AppConfig;

extern AppConfig app_config;

void app_config_init(const DeviceConfig * device);
size_t app_config_write(void);


#endif