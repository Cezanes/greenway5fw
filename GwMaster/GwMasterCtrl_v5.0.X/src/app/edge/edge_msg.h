#pragma once

#include <stdint.h>

typedef struct
{
   const char * what;
} DataCtrlReq;

typedef struct 
{
   int fwv;
   int hwv;
   uint32_t ctrl_id;
   
} DataCtrlId;

typedef struct 
{
   char name[32];
   char description[64];
   
} DataCtrlTitle;

typedef struct 
{
   const char * state;
   const char * error;
   uint32_t program_active_id;
   uint32_t schedule_active_id;
   uint32_t pinout_active_id;
   
} DataCtrlStatus;

typedef struct 
{
   DataCtrlId id;
   DataCtrlTitle title;
   DataCtrlStatus status;
   
} DataCtrlInfo;

typedef struct 
{
   uint32_t ctrl_id;

} DataCtrlConfig;


////////////////////////////////////////////////////////////////////////////


typedef struct 
{
   const char * nr;
   const char * text;
   
} DataMonSms;


////////////////////////////////////////////////////////////////////////////

typedef struct
{
   DataCtrlConfig config;
   DataCtrlTitle title;
   
} DataCtrlGlobal;
