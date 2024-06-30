#ifndef GPS_H
#define GPS_H

#include "types.h"
#include "hal/uart32mx.h"


typedef struct
{
   uint8_t * rx_buff;
   size_t rx_buff_size;
   UartDev * uart;
   uint32_t clock_src;
   uint32_t baud;
   size_t pulse_led_id;
} GpsConfig;



void gps_init(const GpsConfig * config);
void gps_start(void);
bool gps_have_time(void);
void gps_service(void);
void gps_tick(void);



#endif