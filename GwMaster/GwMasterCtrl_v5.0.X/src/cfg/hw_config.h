#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#include "types.h"

#include "lib/shared_buff.h"

#include "sal/debug.h"
#include "sal/buttons.h"
#include "sal/pulse.h"

#include "sas/lora.h"
#include "sas/rtc.h"
#include "sas/storage.h"
#include "sas/sim800c.h"
#include "sas/gps.h"
#include "sas/server.h"

#include "app/sem/semaphore.h"
#include "app/logic/state.h"
#include "app/out/power_ctrl.h"


enum
{
   kPulseSem = 0,
   kPulseRadio,
   kPulseGps,
   kPulseError,
   kPulseBooting,
   kPulseNoTime,
};

typedef struct
{
   PinList addr;
   PinList net;
   Pin modem_present;
} BootStrap;


typedef struct
{
   BootStrap boot;
   DebugConfig debug;
   SharedBuff shabuff;
   StorageConfig storage;
   ButtonConfig buttons;
   HwRadioConfig radio;
   RtcConfig rtc;
   SemConfig sem;
   PulseConfig pulse;
   ComConfig com;
   GpsConfig gps;
   ServerConfig srv;
   PCtrlConfig pctrl;
} HwConfig;

extern const HwConfig hw_config;

void hw_config_init(void);

#endif

