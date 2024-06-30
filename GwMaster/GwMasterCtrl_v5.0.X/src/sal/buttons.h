#ifndef BUTTONS_H
#define BUTTONS_H

#include "types.h"

#define BTN_LONG_PERIOD_MS      1500

#ifndef BTN_MAX_COUNT 
   #define BTN_MAX_COUNT           5
#endif

enum
{
   kBtnIndex0 = 0,
   kBtnIndex1,
   kBtnIndex2,
   kBtnIndex3,
   kBtnIndex4,
};

typedef enum
{
   kBtnEventUnknown = 0,
   kBtnEventDown,
   kBtnEventPressed,
   kBtnEventLongPressed,
   kBtnEventUp,
} BtnEventType;


typedef void (*BtnHandler)(const BtnEventType);


typedef struct
{
   const volatile uint32_t * volatile port;
   const uint32_t port_mask;
} BtnEntry;

typedef struct
{
   const BtnEntry * entries;
   const size_t count;
} ButtonConfig;


void btn_init(const ButtonConfig * config);
void btn_add_handler(const size_t index, const BtnHandler handler);
void btn_service();

bool btn_is_status(const size_t index, const BtnEventType event);



#endif