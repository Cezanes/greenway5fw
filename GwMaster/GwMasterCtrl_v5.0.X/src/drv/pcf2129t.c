
#include "pcf2129t.h"
#include "sal/debug.h"
#include "sal/timer.h"
#include "lib/utils.h"

#include "mcc_generated_files/spi3.h"

enum 
{
   kAddrControl = 0x00,
   kAddrSeconds = 0x03,
   kAddrClockout = 0x0F,
   kAddrAgingOffs = 0x19,
};

enum 
{
   kSubAddr = 0x20,
};

enum
{
   kFlagRead  = 0x80,
   kFlagWrite = 0x00,
};


static struct 
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   uint32_t ss_mask;
   uint8_t (* spi_xfer)(uint8_t);
} pcf;

static void pcf2129t_xfer(uint8_t * const data, size_t count)
{
   *pcf.ss_reg_clear = pcf.ss_mask;
   
   for(size_t i = 0; i < count; i++)
   {
      data[i] = (*pcf.spi_xfer)(data[i]);
   }
   
   *pcf.ss_reg_set = pcf.ss_mask;
}

void pcf2129t_init(const Pcf2129tConfig * const cfg)
{
   pcf.ss_reg_set = cfg->ss_reg_set;
   pcf.ss_reg_clear = cfg->ss_reg_clear;
   pcf.ss_mask = cfg->ss_mask;
   pcf.spi_xfer = cfg->spi_xfer;
}

static uint8_t pcf2129t_get_seconds()
{
   uint8_t data[8] = {kFlagRead | kSubAddr | kAddrSeconds, 0};
   pcf2129t_xfer(data, COUNT(data));
   DBGHEX(kLvlDbg, "pcf2129t, read seq ", data, COUNT(data));
   return utils_bcd_to_hex(data[1] & 0x7F);
}


bool pcf2129t_wait_boot(void)
{
   uint32_t timeout = TM_SEC_T0_TICK(5);
   uint32_t start = timer_tick();
   
   while(timer_tick() - start < timeout)
   {
      uint8_t data[0x1A] = {kFlagRead | kSubAddr | kAddrSeconds, 0};

      pcf2129t_xfer(data, COUNT(data));

      DBGHEX(kLvlDbg, "pcf2129t, wait for boot ", data, COUNT(data));
      
      if((data[1] == 0xFF && data[2] == 0xFF && data[3] == 0xFF) ||
         (data[1] == 0x00 && data[2] == 0x00 && data[3] == 0x00) ||
         (data[1] == 0x80 && data[2] == 0x00 && data[3] == 0x00))
      {
         timer_delay_ms(250);
         continue;
      }
      
      return true;
   }
   
   return false;
}

bool pcf2129t_is_valid(void)
{
   if (!pcf2129t_wait_boot())
   {
      return false;
   }
   
   uint8_t ctrl[4] = {kFlagWrite | kSubAddr | kAddrControl, 0, 0, 0};
   pcf2129t_xfer(ctrl, COUNT(ctrl));
   
   uint8_t wdt[2] = {kFlagWrite | kSubAddr | kAddrClockout, 0};
   pcf2129t_xfer(wdt, COUNT(wdt));
   
   uint8_t aging[2] = {kFlagWrite | kSubAddr | kAddrAgingOffs, 0x08};
   pcf2129t_xfer(aging, COUNT(aging));
   
   size_t counter = 3;
   
   uint8_t read = pcf2129t_get_seconds();
   uint8_t seconds = read;
   
   uint32_t timeout = TM_SEC_T0_TICK(counter + 5);
   uint32_t start = timer_tick();
   
   DBG(kLvlVerb, "pcf2129t, testing time sequence...");
   
   while(timer_tick() - start < timeout)
   {
      uint8_t expected = seconds + 1;
      if(expected >= 60)
         expected = 0;
      
      if(read != seconds)
      {
         if(read == expected)
         {
            counter--;
            if(counter == 0)
            {
               DBG(kLvlDbg, "pcf2129t, good seq %u %u", expected, read);
               return true;
            }
         }
         else
         {
            DBG(kLvlError, "pcf2129t, bad seq %u %u", expected, read);
            return false;
         }
         
         seconds = read;
      }
      
      timer_delay_ms(500);
      
      read = pcf2129t_get_seconds();
      
      DBG(kLvlDbg, "pcf2129t, read sec %u", read);
   }
   
   DBG(kLvlError, "pcf2129t, timeout on second increment sequence");
  
   return false;
}


bool pcf2129t_get_datetime(DateTime * const time)
{
   uint8_t data[8] = {kFlagRead | kSubAddr | kAddrSeconds, 0};

   pcf2129t_xfer(data, COUNT(data));

   DBGHEX(kLvlDbg, "pcf2129t, read data: ", data, COUNT(data));
   
   if((data[1] == 0xFF && data[2] == 0xFF && data[3] == 0xFF && data[4] == 0xFF && data[5] == 0xFF && data[6] == 0xFF && data[7] == 0xFF) ||
      (data[1] == 0x00 && data[2] == 0x00 && data[3] == 0x00 && data[4] == 0x00 && data[5] == 0x00 && data[6] == 0x00 && data[7] == 0x00) || 
      (data[1] == 0x80 && data[2] == 0x00 && data[3] == 0x00 && data[4] == 0x00 && data[5] == 0x00 && data[6] == 0x00 && data[7] == 0x00))
   {
      DBGHEX(kLvlError, "pcf2129t, IC not responding: ", data, COUNT(data));
      return false;
   }

   time->seconds = utils_bcd_to_hex(data[1] & 0x7F);
   time->minutes = utils_bcd_to_hex(data[2] & 0x7F);
   time->hours = utils_bcd_to_hex(data[3] & 0x3F);
   time->days = utils_bcd_to_hex(data[4] & 0x3F);
   time->week_day = data[5] & 0x07;
   time->months = utils_bcd_to_hex(data[6] & 0x1F);
   time->years = utils_bcd_to_hex(data[7]);

   time->years += 2000;

   if(time->week_day == 0)
      time->week_day = 7;

   return true;
}

bool pcf2129t_set_datetime(const DateTime * const time)
{
   size_t week_day = time->week_day;
   
   if(week_day == 7)
      week_day = 0;
   
   uint8_t data[8] = 
   {
      kFlagWrite | kSubAddr | kAddrSeconds,
      utils_hex_to_bcd(time->seconds),
      utils_hex_to_bcd(time->minutes),
      utils_hex_to_bcd(time->hours),
      utils_hex_to_bcd(time->days),
      week_day,
      utils_hex_to_bcd(time->months),
      utils_hex_to_bcd(time->years - 2000),
   };
 
   pcf2129t_xfer(data, COUNT(data));

   return true;
}