#include <stdarg.h>

#include "debug.h"
#include "timer.h"


const char * lvl_str[] = {"debg", "verb", "info", "warn", "erro"};
const char * lvl_color[] = {"\033[0;37m", "\033[0;37m", "\033[1;32m", "\033[1;33m", "\033[1;31m"};
const char * def_color = "\033[0m";

static struct
{
   size_t lvl;
   DebugConfig config;
} dbg;


typedef struct
{
   char * ptr;
   size_t remaining;
} StrN;


typedef void (*tfp_putcf) (void*, char);
static void tfp_printf_putcp(void* p, char c);
static void tfp_snprintf_putc(void* p, char c);
static void tfp_format(void* putp, tfp_putcf putf, const char *fmt, va_list va);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void dbg_init(const DebugConfig * config)
{
   dbg.config = *config;
   dbg.lvl = config->level;
   
   dbg.config.uart->init(dbg.config.uart->lcb, NULL, dbg.config.clock_src, dbg.config.baud);
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
      dbg.config.uart->write(dbg.config.uart->lcb, *(const uint8_t *)data);
      data++;
      count--;
   }
}

/*int __attribute__((__section__(".libc.write"))) write(int handle, void *buffer, unsigned int len) 
{
    unsigned int i;

    for (i = len; i; --i)
    {
        dbg.config.uart->write(dbg.config.uart->lcb, *(const uint8_t *)data);
    }
    return(len);
}*/

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
   
   tfp_printf("[%6lu] ", timer_tick());
   
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
   tfp_format(NULL, tfp_printf_putcp, fmt, ap);
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
   tfp_format(NULL, tfp_printf_putcp, fmt, ap);
   va_end(ap);
}

void dbg_print_foot(int lvl, const char *fmt, ...)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
   va_list ap; 
   va_start(ap, fmt); 
   tfp_format(NULL, tfp_printf_putcp, fmt, ap);
   va_end(ap);
   
   dbg_println(lvl);
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(def_color, 4);
#endif
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
      tfp_printf("%02X ", data[i]);
   }
   
   dbg_println(lvl);
   
#if DBG_USE_COLORS == 1
   dbg_uart_write(def_color, 4);
#endif
}


void dbg_print_data(int lvl, const void *ptr, size_t size)
{
   if(lvl < dbg.lvl || lvl >= COUNT(lvl_str))
      return;
   
   const uint8_t *text = (const uint8_t *) ptr;
  
   while(size--)
      dbg_uart_write(text++, 1);      
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
   tfp_format(NULL, tfp_printf_putcp, fmt, ap);
   va_end(ap);
}




static void putcp(void* p,char c)
{
   *(*((char**)p))++ = c;
}

static void tfp_printf_putcp(void* p, char c)
{
	(void) p;
	dbg.config.uart->write(dbg.config.uart->lcb, c);
}

static void tfp_snprintf_putc(void* p, char c)
{
   StrN * strn = p;
   
   if(strn->remaining)
   {
      *strn->ptr = c;
      strn->ptr++;
      strn->remaining--;
   }
}


static void uli2a(uint32_t num, size_t base, bool uc, char * bf)
{
   size_t n = 0;
   uint32_t d = 1;
   
   while (num / d >= base)
        d *= base;         
    
   while (d != 0) 
   {
      size_t dgt = num / d;
      num %= d;
      d /= base;
      
      if (n || dgt > 0|| d == 0) 
      {
         *bf++ = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a')-10);
         ++n;
      }
   }
    
   *bf=0;
}

static void li2a(int32_t num, char * bf)
{
   if (num < 0) 
   {
      num = -num;
         *bf++ = '-';
   }   
   uli2a((uint32_t)num,10,0,bf);
}

static void ui2a(unsigned int num, size_t base, bool uc, char * bf)
{
   size_t n = 0;
   unsigned int d = 1;
   
   while (num/d >= base)
       d*=base;    
   
   while (d!=0) 
   {
      size_t dgt = num / d;
      num %= d;
      d /= base;
      if (n || dgt > 0 || d == 0) 
      {
         *bf++ = dgt+(dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
         ++n;
      }
   }
   
   *bf=0;
}

static void i2a (int num, char * bf)
{
   if (num<0) 
   {
      num=-num;
      *bf++ = '-';
   }
   
   ui2a(num,10,0,bf);
}

static int a2d(char ch)
{
   if (ch>='0' && ch<='9') 
       return ch-'0';
   else if (ch>='a' && ch<='f')
       return ch-'a'+10;
   else if (ch>='A' && ch<='F')
       return ch-'A'+10;
   else return -1;
}

static char a2i(char ch, const char ** src, size_t base, int * nump)
{
   const char * p= *src;
   int num = 0;
   int digit;
   while ((digit = a2d(ch))>=0) 
   {
       if (digit > base) break;
       num = num * base + digit;
       ch = *p++;
   }
   
   *src = p;
   *nump = num;
   return ch;
}

static void putchw(void* putp, tfp_putcf putf, int n, char z, char* bf)
{
    char fc=z? '0' : ' ';
    char ch;
    char* p=bf;
    while (*p++ && n > 0)
        n--;
    while (n-- > 0) 
        putf(putp, fc);
    while ((ch= *bf++))
        putf(putp, ch);
}

void tfp_format(void* putp, tfp_putcf putf, const char *fmt, va_list va)
{
    char bf[12];
    char ch;

    while ((ch=*(fmt++))) 
    {
        if (ch != '%') 
            putf(putp, ch);
        else {
            char lz = 0;
            char lng = 0;
            int w = 0;
            ch=*(fmt++);
            if (ch=='0') 
            {
                ch=*(fmt++);
                lz=1;
            }
            
            if (ch >= '0' && ch <= '9') 
            {
                ch = a2i(ch, &fmt, 10, &w);
            }
            if (ch == 'l') 
            {
               ch = *(fmt++);
               lng = 1;
            }
            switch (ch) {
                case 0: 
                    goto abort;
                case 'u' : {
                    if (lng)
                        uli2a(va_arg(va, uint32_t),10,0,bf);
                    else
                        ui2a(va_arg(va, unsigned int),10,0,bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                case 'd' :  {
                    if (lng)
                        li2a(va_arg(va, int32_t),bf);
                    else
                    i2a(va_arg(va, int),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                
                case 'x': 
                case 'X' : 
                    if (lng)
                        uli2a(va_arg(va, uint32_t),16,(ch=='X'),bf);
                    else
                        ui2a(va_arg(va, unsigned int),16,(ch=='X'),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                case 'c' : 
                    putf(putp,(char)(va_arg(va, int)));
                    break;
                case 's' : 
                    putchw(putp,putf,w,0,va_arg(va, char*));
                    break;
                case '%' :
                    putf(putp,ch);
                default:
                    break;
                }
            }
        }
    abort:;
}

void tfp_printf(const char *fmt, ...)
{
    va_list va;
    va_start(va,fmt);
    tfp_format(NULL, tfp_printf_putcp, fmt, va);
    va_end(va);
}

size_t tfp_sprintf(char* s, const char *fmt, ...)
{
   const char * start = s;
   va_list va;
   va_start(va,fmt);
   tfp_format(&s, putcp, fmt, va);
   putcp(&s, 0);
   va_end(va);
   
   return s - start - 1;
}

size_t tfp_snprintf(char* s, size_t size, const char *fmt, ...)
{
   if(size == 0)
      return 0;
   
   s[size - 1] = 0;
   
   StrN strn = {
      .ptr = s,
      .remaining = size - 1,
   };
   
   va_list va;
   va_start(va,fmt);
   tfp_format(&strn, tfp_snprintf_putc, fmt, va);
   size_t len = strn.ptr - s;
   tfp_snprintf_putc(&strn, 0);
   va_end(va);
   
   return len;
}