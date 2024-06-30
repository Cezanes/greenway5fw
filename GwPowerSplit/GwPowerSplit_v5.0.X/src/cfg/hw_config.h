#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#include "types.h"
#include "sas/pulse.h"
#include "sas/debug.h"
#include "ssl/bulbctrl.h"
#include "app/hostctrl.h"


enum
{
   kPulseMainsPowerError = 0,
   kPulseHostSync,
};

typedef struct 
{
   PinList hwaddr;
} DeviceConfig;


typedef struct
{
   DeviceConfig device;
   DebugConfig debug;
   PulseConfig pulse;
   HCtrlConfig hctrl;
   BulbConfig bulb_ctrl;
} HwConfig;

extern const HwConfig hw_config;

void hw_config_init(void);

#endif

