#ifndef I2CDRV_H
#define I2CDRV_H

#include "types.h"

typedef struct 
{
   volatile uint32_t * volatile scl_val_set;
   volatile uint32_t * volatile scl_val_clear;
   volatile uint32_t * volatile scl_tris_set;
   volatile uint32_t * volatile scl_tris_clear;
   volatile uint32_t * volatile scl_input;
   uint32_t scl_reg_mask;
   
   volatile uint32_t * volatile sda_val_set;
   volatile uint32_t * volatile sda_val_clear;
   volatile uint32_t * volatile sda_tris_set;
   volatile uint32_t * volatile sda_tris_clear;
   volatile uint32_t * volatile sda_input;
   uint32_t sda_reg_mask;
   
} I2cSoftConfig;


void i2c_soft_init(const I2cSoftConfig * config);
bool i2c_write_byte(bool send_start, bool send_stop, uint8_t byte);
uint8_t i2c_read_byte(bool nack, bool send_stop);

#endif