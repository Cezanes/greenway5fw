#ifndef PIN32_H
#define PIN32_H

#include "types.h"

#define PIN_DEF(rp, index)         \
   {                               \
      .mask     = 1 << index,      \
      .port     = &PORT##rp,       \
      .port_set = &PORT##rp##SET,  \
      .port_clr = &PORT##rp##CLR,  \
      .lat      = &LAT##rp,        \
      .lat_set  = &LAT##rp##SET,   \
      .lat_clr  = &LAT##rp##CLR,   \
      .tris     = &TRIS##rp,       \
      .tris_set = &TRIS##rp##SET,  \
      .tris_clr = &TRIS##rp##CLR,  \
   }


typedef struct
{
   volatile uint32_t * port;
   volatile uint32_t * port_set;
   volatile uint32_t * port_clr;
   volatile uint32_t * lat;
   volatile uint32_t * lat_set;
   volatile uint32_t * lat_clr;
   volatile uint32_t * tris;
   volatile uint32_t * tris_set;
   volatile uint32_t * tris_clr;
   uint32_t mask;
} Pin;


typedef struct
{
   const Pin * list;
   size_t count;
} PinList;


void pin_input(const Pin * pin);
void pin_output(const Pin * pin);
uint32_t pin_read(const Pin * pin);
void pin_write(const Pin * pin, bool value);





#endif