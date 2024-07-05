#pragma once

#include <stdint.h>

typedef struct
{
   char what[32];
} DataCtrlReq;


typedef struct 
{
   int fwv;
   int hwv;
   char devid[16];
   
} DataCtrlId;

typedef struct 
{
   char name[16];
   char description[64];
   
} DataCtrlTitle;

typedef struct 
{
   char state[16];
   char error[16];
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




////////////////////////////////////////////////////////////////////////////


typedef struct 
{
   const char * nr;
   const char * text;
   
} DataMonSms;
