#include "gps.h"

#include <sys/attribs.h>

#include "lib/utils.h"
#include "lib/datetime.h"

#include "sal/debug.h"
#include "sal/timer.h"
#include "sal/pulse.h"

#include "app/sem/chronos.h"
#include "app/logic/logic.h"

enum 
{
   kGpsErrInvalidBuff = 1 << 0,
   kGpsErrCrc         = 1 << 1,
   kGpsErrSignal      = 1 << 2,
};

static struct 
{
   GpsConfig config;
   size_t rx_index;
   
   uint8_t time_str[7];
   uint8_t date_str[7];
   
   bool have_signal;
   bool first_run;
   bool time_updated;
   uint32_t time_stamp;
   uint32_t last_epoch;
   uint32_t last_epoch_ts;
   
   bool use_tick_pulses;
   size_t tick_pulses;
   size_t last_tick_pulse;
   uint32_t last_pulse_ts;
   
   uint32_t skip_report_count;
   uint32_t errors;
   
} gps;

static void gps_recv_byte(void*, uint8_t b);


///////////////////////////////////////////////////////////////////////////////////////////////////


static bool gps_get_param(size_t index, const uint8_t * src, size_t size, uint8_t * dst, size_t count)
{
   const uint8_t * ptr = src;
   
   while(index > 0)
   {
      while(*ptr != ',')
      {
         ptr++;
         if(ptr >= &src[size])
            return false;
      }
      
      ptr++;
      if(ptr >= &src[size])
         return false;
      
      index--;
   }
   
   if(&ptr[count] > &src[size])
      return false;
   
   for(size_t i = 0; i < count; i++)
   {
      if(ptr[i] == ',')
         return false;
   }
   
   while(count)
   {
      *dst++ = *ptr++;
      count--;
   }
   
   return true;
}

static void gps_process_nmea(const uint8_t * data, size_t size)
{
   if(data[0] == 'G' && data[1] == 'N' && data[2] == 'R' && data[3] == 'M' && data[4] == 'C')
   {
      gps.time_str[sizeof(gps.time_str) - 1] = 0;
      if(!gps_get_param(1, data, size, gps.time_str, 6))
      {
         gps.errors |= kGpsErrSignal;
         return;
      }
      
      gps.date_str[sizeof(gps.date_str) - 1] = 0;
      if(!gps_get_param(9, data, size, gps.date_str, 6))
      {
         gps.errors |= kGpsErrSignal;
         return;
      }
      
      gps.time_updated = true;
      gps.time_stamp = timer_tick();
   }
}

static void gps_process_buff(const uint8_t * const data, size_t size)
{
   const uint8_t * start = data;
   
   while(*start == '\n' || *start == '$')
   {
      start++;
      if(start >= &data[size])
      {
         gps.errors |= kGpsErrInvalidBuff;
         return;
      }
   }
   
   const uint8_t * end = start;
   
   while(*end != '*')
   {
      end++;
      if(end >= &data[size])
      {
         gps.errors |= kGpsErrInvalidBuff;
         return;
      }
   }
   
   if (end - data > size - 2)
   {
      gps.errors |= kGpsErrInvalidBuff;
      return;
   }
   
   uint8_t found_crc = utils_hex_to_byte(end + 1);
   uint8_t calc_crc = 0;

   const uint8_t * ptr = start;
   
   while(ptr < end)
   {
      calc_crc ^= *ptr;
      ptr++;
   }
   
   if (calc_crc != found_crc)
   {
      gps.errors |= kGpsErrCrc;
      return;
   }
   
   gps_process_nmea(start, end - start);
}

static void gps_recv_byte(void* user, uint8_t b)
{
   if(b == '$')
   {
      gps.rx_index = 0;
   }
   else if(gps.rx_index == 0)
   {
      return;
   }
      
   //while(U1STAbits.UTXBF);
   //U1TXREG = b;
   
   if(b == '\n' && gps.rx_index > 0)
   {
      gps_process_buff(gps.config.rx_buff, gps.rx_index);
      gps.rx_index = 0;
      
      return;
   }   
   
   if(gps.rx_index < gps.config.rx_buff_size)
      gps.config.rx_buff[gps.rx_index++] = b;
   else gps.rx_index = 0;  
}

void gps_tick(void)
{
   gps.last_pulse_ts = timer_tick();
   gps.tick_pulses++;
   if(gps.tick_pulses >= 3)
      gps.use_tick_pulses = true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////


void gps_init(const GpsConfig * config)
{
   gps.config = *config;
   gps.skip_report_count = 5;
   gps.errors = kGpsErrSignal;
   
   gps.config.uart->init(gps.config.uart->lcb, NULL, gps.config.clock_src, gps.config.baud);
   gps.config.uart->set_isr(gps.config.uart->lcb, &gps_recv_byte);
   gps.config.uart->enable_isr(gps.config.uart->lcb, true);
}


void gps_start(void)
{
   gps.errors |= kGpsErrSignal;
   gps.first_run = true;
   
   const char * baud_cmd = "$PMTK251,115200*1F\r\n";
   
   timer_delay_ms(2000);
   
   size_t repeat = 3;
   while(repeat--)
   {
      const char *ptr = baud_cmd;
      for(; *ptr; ptr++)
      {
         gps.config.uart->write(gps.config.uart->lcb, *ptr);
      }
      timer_delay_ms(200);
   }
   
   gps.config.uart->init(gps.config.uart->lcb, NULL, gps.config.clock_src, 115200);
   
   const char * sync_cmd = "$PMTK255,1*2D\r\n";
   repeat = 3;
   while(repeat--)
   {
      const char *ptr = sync_cmd;
      for(; *ptr; ptr++)
      {
         gps.config.uart->write(gps.config.uart->lcb, *ptr);
      }
      timer_delay_ms(200);
   }
}

bool gps_have_time(void)
{
   return gps.have_signal;
}

void gps_service()
{
   if(gps.use_tick_pulses && gps.tick_pulses != gps.last_tick_pulse)
   {
      gps.last_tick_pulse = gps.tick_pulses;
      uint32_t now = timer_tick();
      
      if (now - gps.last_epoch_ts < TM_MLS_T0_TICK(900) &&
          now - gps.last_pulse_ts < TM_MLS_T0_TICK(5))
      {
         logic_on_gps_status(true, gps.last_epoch + 1);
      }
   }
   
   if(gps.errors & kGpsErrInvalidBuff)
   {
      gps.errors ^= kGpsErrInvalidBuff;
      DBG(kLvlWarn, "gps, received corrupted buffer");
   }
   
   if(gps.errors & kGpsErrCrc)
   {
      gps.errors ^= kGpsErrCrc;
      DBG(kLvlWarn, "gps, invalid crc received");
   }
   
   if(gps.errors & kGpsErrSignal)
   {
      gps.errors ^= kGpsErrSignal;
      
      if (gps.have_signal || gps.first_run)
      {
         pulse_stop(gps.config.pulse_led_id);
         logic_on_gps_status(false, 0);
         
         DBG(kLvlWarn, "gps, no signal");
         gps.have_signal = false;
         gps.first_run = false;
         
      }
   }
   
   if (gps.time_updated)
   {
      gps.time_updated = false;
      
      DateTime dt;
      dte_get_gps_datetime(gps.time_str, gps.date_str, &dt);
      gps.last_epoch = dte_get_epoch(&dt);
      gps.last_epoch_ts = gps.time_stamp;
         
      if (!gps.have_signal)
      {
         pulse_start(gps.config.pulse_led_id);
         gps.have_signal = true;
         DBG(kLvlInfo, "gps, signal %02u:%02u:%02u %02u.%02u.%02u", dt.hours, dt.minutes, dt.seconds, dt.days, dt.months, dt.years);
      }
      
      if (gps.skip_report_count > 0)
         gps.skip_report_count--;
      else 
      {
         if (!gps.use_tick_pulses)
         {
            uint32_t now = timer_tick();
            uint32_t delay = now - gps.time_stamp;

            if (delay < TM_MLS_T0_TICK(5))
            {
               logic_on_gps_status(true, gps.last_epoch);
            }
            else
            {
               DBG(kLvlInfo, "gps, update delay %u %u %u", delay, gps.time_stamp, now);
            }
         }
      }
   }
   else if (gps.have_signal && (timer_tick() - gps.time_stamp) > TM_SEC_T0_TICK(10))
   { 
      gps.errors |= kGpsErrSignal;
   }
}