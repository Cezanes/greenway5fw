#include <stdarg.h>
#include <stdio.h>

#include "types.h"
#include "debug.h"
#include "timer.h"
#include "mcc_generated_files/uart1.h"

const char * lvl_str[] = {"debg", "verb", "info", "warn", "erro"};
const char * lvl_color[] = {"\033[0;37m", "\033[0;37m", "\033[1;32m", "\033[1;33m", "\033[1;31m"};
const char * def_color = "\033[0m";


static struct
{
   size_t lvl;
   DebugConfig config;
} dbg;


//////////////////////////////////////////////////////////////////////////////////////////////////////


void dbg_init(const DebugConfig * config)
{
   dbg.config = *config;
   dbg.lvl = config->level;
   
   dbg.config.uart->init(dbg.config.uart->lcb, NULL, dbg.config.clock_src, dbg.config.baud);
   
   setbuf(stdout, NULL);
}

void _mon_putc(char c)
{
   //dbg.config.uart->write(dbg.config.uart->lcb, c);
   UART1_Write(c);
}

/* 
 * Returns the configured debug level.
 */
size_t dbg_get_level(void)
{  
   return dbg.lvl;
}

/* 
 * Sets the debug level.
 */
void dbg_set_level(size_t lvl)
{
   dbg.lvl = lvl;
}

static void dbg_uart_write(const void * data, size_t count)
{
   while (count > 0)
   {
      //dbg.config.uart->write(dbg.config.uart->lcb, *(const uint8_t *)data);
      UART1_Write(*(const char *)data);
      data++;
      count--;
   }
}

/* 
 * Prints a new line
 */
void dbg_println(int lvl)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
   dbg_uart_write("\r\n", 2);
}

static void dbg_timestamp(void)
{  
#if DBG_USE_TIMESTAMP == 1

   /*uint32_t epoch, tick;  
   timer_get_sync_time(&epoch, &tick);
   
   uint8_t day, month;
   uint16_t year;
   CaGetCurrentDate(epoch, &day, &month, &year);
   
   sprintf(dbg.buff, "%02u.%02u.%02u ", year, month, day);
   dbg_uart_write(dbg.buff, strlen(dbg.buff));
   
   uint8_t hour, min, second;
   CaGetTime(epoch, &hour, &min, &second);
   uint16_t mili = tick % 1000;
   
   sprintf(dbg.buff, "%02u:%02u:%02u.%04u ", hour, min, second, mili);
   dbg_uart_write(dbg.buff, strlen(dbg.buff));*/
   
   printf("[%6u] ", timer_tick());
   
#endif
}

/* 
 * Prints a formated string
 */
void dbg_print(int lvl, const char *fmt, ...)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(lvl_color[lvl], 7);
#endif
   
   dbg_timestamp();
   
   dbg_uart_write(lvl_str[lvl], 4);
   dbg_uart_write(": ", 2);
   
   va_list ap; 
   va_start(ap, fmt); 
   vprintf(fmt, ap);
   va_end(ap);
      
   dbg_println(lvl);
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(def_color, 4);
#endif
}

void dbg_print_hdr(int lvl, const char *fmt, ...)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(lvl_color[lvl], 7);
#endif
   
   dbg_timestamp();
   
   dbg_uart_write(lvl_str[lvl], 4);
   dbg_uart_write(": ", 2);
   
   va_list ap; 
   va_start(ap, fmt); 
   vprintf(fmt, ap);
   va_end(ap);
}

/* 
 * Prints data in a hex format.
 */
void dbg_hex(int lvl, const char *text, const void *ptr, size_t size)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
   const uint8_t *data = (const uint8_t *) ptr;

#if DBG_USE_COLORS == 1
   dbg_uart_write(lvl_color[lvl], 7);
#endif
   
   dbg_timestamp();
   
   dbg_uart_write(lvl_str[lvl], 4);
   dbg_uart_write(": ", 2);
   
   while(*text)
      dbg_uart_write(text++, 1);
    
   for(size_t i = 0; i < size; i++)
   {
      printf("%02X ", data[i]);
   }
   
   dbg_println(lvl);
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(def_color, 4);
#endif
}

/* 
 * Prints data without any processing.
 */
void dbg_print_raw(int lvl, const char *fmt, ...)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
   va_list ap; 
   va_start(ap, fmt); 
   vprintf(fmt, ap);
   va_end(ap);
}