#include "pin32.h"

void pin_input(const Pin * pin)
{
   *pin->tris_set = pin->mask;
}

void pin_output(const Pin * pin)
{
   *pin->tris_clr = pin->mask;
}

uint32_t pin_read(const Pin * pin)
{
   return ((*pin->port & pin->mask) > 0);
}

void pin_write(const Pin * pin, bool value)
{
   if(value)
   {
      *pin->lat_set = pin->mask;
   }
   else
   {
      *pin->lat_clr = pin->mask;
   }
}