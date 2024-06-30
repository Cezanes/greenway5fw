#ifndef PCF2129T
#define PCF2129T

#include "types.h"
#include "lib/datetime.h"

typedef struct
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   uint32_t ss_mask;
   uint8_t (* spi_xfer)(uint8_t);
} Pcf2129tConfig;

void pcf2129t_init(const Pcf2129tConfig * const cfg);
bool pcf2129t_is_valid(void);
bool pcf2129t_get_datetime(DateTime * const time);
bool pcf2129t_set_datetime(const DateTime * const time);


#endif