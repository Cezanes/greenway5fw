#ifndef UART32MX_H
#define UART32MX_H

#include "types.h"


typedef struct
{
   void * lcb;
   void (*init)(void * lcb, uint32_t clock_src, uint32_t baud);
   uint8_t (*read)(void * lcb);
   void (*write)(void * lcb, uint8_t b);
   bool (*available)(void * lcb);
   void (*enable_isr)(void * lcb, bool on);
   void (*set_isr)(void * lcb, void(*on_rx)(uint8_t b));
   void (*close)(void * lcb);
} UartDev;


extern UartDev Uart[4];



#endif