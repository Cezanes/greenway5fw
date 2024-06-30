#include "i2c_soft.h"
#include "types.h"
#include "sas/debug.h"

#ifndef I2C_TIMEOUT
   #define I2C_TIMEOUT                        1000
#endif

#define  i2c_delay()                    delay_us(25)


typedef struct
{
   const I2cSoftConfig * config;
   
} I2cSoftInternal;


static I2cSoftInternal i2cs;


void i2c_soft_init(const I2cSoftConfig * config)
{
   i2cs.config = config;
}

static void delay_us(const uint32_t us)
{
   uint32_t start = _CP0_GET_COUNT();
   uint32_t duration = us * 12;
   while(_CP0_GET_COUNT() - start < duration);
}

 // Set SCL as input and return current level of line, 0 or 1
static bool i2c_read_scl(void)
{
   *i2cs.config->scl_tris_set = i2cs.config->scl_reg_mask;
   delay_us(1);
   return (*i2cs.config->scl_input & i2cs.config->scl_reg_mask) > 0;
   
   /*output_float(I2C_PIN_SCL);
   delay_cycles(1);
   return input(I2C_PIN_SCL);*/
}

// Set SDA as input and return current level of line, 0 or 1
static bool i2c_read_sda(void)
{
   *i2cs.config->sda_tris_set = i2cs.config->sda_reg_mask;
   delay_us(1);
   return (*i2cs.config->sda_input & i2cs.config->sda_reg_mask) > 0;
   
   /*output_float(I2C_PIN_SDA);
   delay_cycles(1);
   return input(I2C_PIN_SDA);*/
}

 // Actively drive SCL signal low
static void i2c_clear_scl(void)
{
   *i2cs.config->scl_tris_clear = i2cs.config->scl_reg_mask;
   delay_us(1);
   *i2cs.config->scl_val_clear = i2cs.config->scl_reg_mask;
   
   /*output_drive(I2C_PIN_SCL);
   delay_cycles(1);
   output_low(I2C_PIN_SCL);*/
}

 // Actively drive SDA signal low
static void i2c_clear_sda(void)
{
   *i2cs.config->sda_tris_clear = i2cs.config->sda_reg_mask;
   delay_us(1);
   *i2cs.config->sda_val_clear = i2cs.config->sda_reg_mask;
   
   /*output_drive(I2C_PIN_SDA);
   delay_cycles(1);
   output_low(I2C_PIN_SDA);*/
}

void i2c_arbitration_lost()
{
   // fprintf(dbg, "lost arb\r\n");
}
 
// global data
bool i2c_started = false;

void i2c_start_cond() 
{
   if(i2c_started) 
   { 
      // if started, do a restart cond
      // set SDA to 1
      i2c_read_sda();
      i2c_delay();
      
      uint32_t timeout = I2C_TIMEOUT;
      while(i2c_read_scl() == 0 && timeout)
      {
         // Clock stretching
         timeout--;
         delay_us(1);
      }
      
      //fprintf(dbg, "%lu \r\n", timeout);
      // Repeated start setup time, minimum 4.7us
      i2c_delay();
   }
   
   if(i2c_read_sda() == 0) 
   {
      i2c_arbitration_lost();
   }
  
   // SCL is high, set SDA from 1 to 0.
   i2c_clear_sda();
   i2c_delay();
   i2c_clear_scl();
   i2c_started = true;
}
 
void i2c_stop_cond()
{
   // set SDA to 0
   i2c_clear_sda();
   i2c_delay();
   
   // Clock stretching
   uint32_t timeout = I2C_TIMEOUT;
   while(i2c_read_scl() == 0 && timeout)
   {
      // Clock stretching
      timeout--;
      delay_us(1);
   }
   
   //fprintf(dbg, "%lu \r\n", timeout);
   
   // Stop bit setup time, minimum 4us
   i2c_delay();
   
   // SCL is high, set SDA from 0 to 1
   if(i2c_read_sda() == 0) 
   {
      i2c_arbitration_lost();
   }
   i2c_delay();
   i2c_started = false;
}
 
// Write a bit to I2C bus
void i2c_write_bit(bool bit) 
{
   if(bit) 
   {
      i2c_read_sda();
   } else 
   {
      i2c_clear_sda();
   }
   
   i2c_delay();
   
   uint32_t timeout = I2C_TIMEOUT;
   while(i2c_read_scl() == 0 && timeout)
   {
      // Clock stretching
      timeout--;
      delay_us(1);
   }
   
   // DBG(kLvlVerb, "write %u", timeout);
   
   //fprintf(dbg, "%lu \r\n", timeout);
   
   // SCL is high, now data is valid
   // If SDA is high, check that nobody else is driving SDA
   if (bit && i2c_read_sda() == 0) 
   {
      i2c_arbitration_lost();
   }
   i2c_delay();
   i2c_clear_scl();
}
 
// Read a bit from I2C bus
bool i2c_read_bit(void) 
{
   bool bit;
   
   // Let the slave drive data
   i2c_read_sda();
   i2c_delay();
   
   uint32_t timeout = I2C_TIMEOUT;
   while(i2c_read_scl() == 0 && timeout)
   {
      // Clock stretching
      timeout--;
      delay_us(1);
   }
   
   //fprintf(dbg, "%lu \r\n", timeout);
   
   // SCL is high, now data is valid
   bit = i2c_read_sda();
   i2c_delay();
   i2c_clear_scl();
   return bit;
}
 
// Write a byte to I2C bus. Return 0 if ack by the slave.
bool i2c_write_byte(bool send_start, bool send_stop, uint8_t byte) 
{
   uint8_t bit;
   bool nack;
   if(send_start) 
   {
      i2c_start_cond();
   }
   
   for(bit = 0; bit < 8; bit++) 
   {
      i2c_write_bit((byte & 0x80) != 0);
      byte <<= 1;
   }
   
   nack = i2c_read_bit();
   if(send_stop) 
   {
      i2c_stop_cond();
   }
   
   return nack;
}
 
// Read a byte from I2C bus
uint8_t i2c_read_byte(bool nack, bool send_stop)
{
   uint8_t byte = 0;
   uint8_t bit;
   for (bit = 0; bit < 8; bit++) 
   {
      byte = (byte << 1) | i2c_read_bit();
   }
   
   i2c_write_bit(nack);
   if(send_stop) 
   {
      i2c_stop_cond();
   }
   
   return byte;
}


