
#include "pcal6524.h"
#include "hal/i2c_soft.h"
#include "hal/i2c.h"

enum 
{
   kCmdTris  = 0x0C,
   kCmdValue = 0x04,
};

void pcal6524_init()
{
   
}

bool pcal6524_set_tris(const uint8_t addr, const uint8_t * tris, const size_t count)
{
   /*i2c_write_byte(true, false, addr);
   i2c_write_byte(false, false, kCmdTris);
   
   for(size_t i = 0; i < count; i++)
   {
      if(i2c_write_byte(false, (i == count - 1), tris[i]))
         break;
   }
   
   return true;*/
   
   for(;;)
   {
      if(!i2c_start())
         break;
      
      if(!i2c_write(addr, true))
         break;
      
      if(!i2c_write(kCmdTris, true))
         break;
      
      for(size_t i = 0; i < count; i++)
      {
         if(!i2c_write(tris[i], true))
            break;
      }
      
      if(!i2c_stop())
         break;
      
      i2c_cleanup();
      
      return true;
   }
   
   i2c_cleanup();
   
   return false;
}

bool pcal6524_set_value(const uint8_t addr, const uint8_t * value, const size_t count)
{
   
   /*i2c_write_byte(true, false, addr);
   i2c_write_byte(false, false, kCmdValue);
   
   for(size_t i = 0; i < count; i++)
   {
      if(i2c_write_byte(false, (i == count - 1), value[i]))
         break;
   }
   
   return true;*/
   
   for(;;)
   {
      if(!i2c_start())
         break;
      
      if(!i2c_write(addr, true))
         break;
      
      if(!i2c_write(kCmdValue, true))
         break;
      
      for(size_t i = 0; i < count; i++)
      {
         if(!i2c_write(value[i], true))
            break;
      }
      
      if(!i2c_stop())
         break;
      
      i2c_cleanup();
      
      return true;
   }
   
   i2c_cleanup();
   
   return false;
}

size_t pcal6524_compile_tris(const uint8_t * val, size_t val_count, uint8_t * dest, size_t available)
{
   if(available < 4)
      return 0;
   
   *dest++ = kCmdTris;
   *dest++ = *val++;
   *dest++ = *val++;
   *dest++ = *val++;
   
   return 4;
}

size_t pcal6524_compile_val(const uint8_t * val, size_t val_count, uint8_t * dest, size_t available)
{
   if(available < 4)
      return 0;
   
   *dest++ = kCmdValue;
   *dest++ = *val++;
   *dest++ = *val++;
   *dest++ = *val++;
   
   return 4;
}