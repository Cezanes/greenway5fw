
#include <string.h>
#include <stdarg.h>

#include "atdrv.h"

#include "hal/sys.h"
#include "sal/debug.h"
#include "sal/timer.h"

/* Local software unit data */
static struct
{
   AtConfig config;
   size_t rx_index;
   size_t rx_count;
   bool rx_error;
} at;

static void at_on_rx(void * user, uint8_t b);


///////////////////////////////////////////////////////////////////////////////////////////////////


/* 
 * Initialization of AT command module
 */
void at_init(const AtConfig * config)
{
   memset(&at, 0, sizeof(at));
   at.config = *config;
   at.config.uart_dev->init(at.config.uart_dev->lcb, NULL, at.config.clock_src, at.config.baud);
   at.config.uart_dev->set_isr(at.config.uart_dev->lcb, &at_on_rx);
   at.config.uart_dev->enable_isr(at.config.uart_dev->lcb, true);
}

/* 
 * Sends plain data to the module
 */
void at_send_data(const char * data, size_t size)
{
   for(;size; size--, data++)
   {
      at.config.uart_dev->write(at.config.uart_dev->lcb, *data);
   }
}

/* 
 * Sends an AT command to the module
 */
void at_command(const char * data)
{
   size_t len = strlen((const char *) data);
   at_send_data((const char *) data, len);
   at_send_data(AT_CMD_ENDL, strlen(AT_CMD_ENDL));
}

/* 
 * Gets the received size from the module
 */
size_t ar_rx_size(void)
{
   return at.rx_count;
}

/* 
 * Gets a single character from the module.
 */
bool at_rx_getc(char *b)
{
   if(at.rx_count)
   {
      sys_disable_ints();
      
      size_t pos = at.rx_index < at.rx_count ? 
                   at.rx_index + at.config.rx_buff_size - at.rx_count :
                   at.rx_index - at.rx_count;
      at.rx_count--;
      
      sys_enable_ints();
      
      *b = at.config.rx_buff[pos];
      
      return true;
   }
   
   return false;
}


/* 
 * Callback that receives one character over the serial interface
 */
static void at_on_rx(void* user, uint8_t b)
{
   if(at.rx_count < at.config.rx_buff_size)
   {
      at.config.rx_buff[at.rx_index] = b;
      at.rx_index++;
      if(at.rx_index >= at.config.rx_buff_size)
         at.rx_index -= at.config.rx_buff_size;
      at.rx_count++;
   }
   else
   {
      at.rx_error = true;
   }
}

/* 
 * Clears the received unprocessed data.
 */
void at_rx_clear(void)
{
   sys_disable_ints();
   at.rx_index = 0;
   at.rx_count = 0;
   sys_enable_ints();
}

bool at_rx_error(void)
{
    if(at.rx_error)
    {
        at.rx_error = false;
        return true;
    }
    
    return false;
}

/* 
 * Gets a character from the module, with timeout.
 */
bool at_get_rx_char(char *b, size_t timeout)
{
   timeout *= 100;
   while(timeout)
   {
      if(ar_rx_size())
      {
         return at_rx_getc(b);
      }
      
      timeout--;
      timer_delay_us(10);
   }

   return false;
}

/* 
 * Reads all characters from a module, until timeout expires.
 */
size_t at_read_till_to(char *data, size_t size, size_t timeout)
{
   timeout *= 100;
   int16_t count = 0;
   while(size && timeout)
   {
      char b;
      if(ar_rx_size())
      {
         at_rx_getc(&b);
         
         if(count == size)
            return count;
         
         data[count++] = b;
      }
      else
      {
         timeout--;
         timer_delay_us(10);
      }
   }

   return count;
}

/* 
 * Clears the data from a cmd response container.
 */
void at_clear_resp(AtResp *resp)
{
   *resp = (AtResp)
   {
      .buff = resp->buff,
      .buff_size = resp->buff_size,
   };
   
   memset(resp->buff, 0, resp->buff_size);
}

/* 
 * Gets an AT cmd response in a resp container, with timeout
 */
/*size_t at_get_response_to(AtResp *resp, size_t timeout)
{
   at_clear_resp(resp);
   for(;;)
   {
      char b;
      if(!at_get_rx_char(&b, timeout))
      {
         resp->code = AT_RESP_TIMEOUT;
         return resp->code;
      }
      
      if(resp->count == 0 && (b == '\n' || b == '\r'))
      {
         continue;
      }

      resp->buff[resp->count++] = b;
      
      if(resp->count >= resp->buff_size)
      {
         resp->code = AT_RESP_OVERSIZED;
         return resp->code;
      }

      if(b == '\n')
      {
         for(size_t i = 0; i < at.config.at_resp_count; ++i)
         {
            size_t len = strlen(at.config.at_resp_type[i].name);
            if(resp->count >= len)
            {
               char *pos = &resp->buff[resp->count - len];
               if(strncmp(pos, at.config.at_resp_type[i].name, len) == 0)
               {
                  resp->code = at.config.at_resp_type[i].code;
                  return resp->code;
               }
            }
         }
      }
   }
}*/

size_t at_get_response_to(AtResp *resp, uint32_t timeout)
{
   at_clear_resp(resp);
   for(;;)
   {
      char b;
      if(!at_get_rx_char(&b, timeout))
      {
         resp->code = AT_RESP_TIMEOUT;
         return resp->code;
      }
      
      if(resp->count == 0 && (b == '\n' || b == '\r'))
      {
         continue;
      }

      resp->buff[resp->count++] = b;
      
      if(resp->count >= resp->buff_size)
      {
         resp->code = AT_RESP_OVERSIZED;
         return resp->code;
      }

      if(b == '\n')
      {
         char *pos = &resp->buff[resp->count - 1];
         size_t begin_pos = resp->count;

         for(; begin_pos > 1 && (*pos == '\r' || *pos == '\n'); begin_pos--, pos--);
         for(; begin_pos > 1 && (*(pos - 1) != '\r' && *(pos - 1) != '\n'); begin_pos--, pos--);
         
         for(size_t i = 0; i < at.config.at_resp_count; ++i)
         {
            size_t str_len = strlen(at.config.at_resp_type[i].name);
            if(resp->count - begin_pos + 1 >= str_len)
            {
               if(strncmp(pos, at.config.at_resp_type[i].name, str_len) == 0)
               {
                  resp->code = at.config.at_resp_type[i].code;
                  return resp->code;
               }
            }
         }
      }
   }
}

/* 
 * Gets an AT cmd response in a resp container, with a predefined timeout.
 */
size_t at_get_response(AtResp *resp)
{
   return at_get_response_to(resp, 2000);
}

/* 
 * Gets the first line from an AT response
 */
char* at_parse_get_first_line(AtResp *resp)
{
   resp->line = &resp->buff[0];
   return resp->line;
}

/* 
 * Gets the length of a string.
 */
size_t at_parse_get_line_size(const char *line)
{
   size_t size = 0;
   while(*line != 0 && *line != '\r' && *line != '\n')
   {
      line++;
      size++;
   }
   return size;
}

/* 
 * Moves pointer to a next line from a received AT response.
 */
char* at_parse_get_next_line(AtResp *resp)
{
   if(!resp->line)
   {
      return at_parse_get_first_line(resp);
   }

   char *pos = resp->line;
   char *max = &resp->buff[resp->count];
 
   while(pos < max)
   {
      pos++;
      if(*pos == '\n') break;
   }

   pos++;
   if(pos < max)
   {
      resp->line = pos;
      return pos;
   }

   resp->line = 0;
   return 0;
}

bool at_parse_ends_with(const char *data, size_t data_size, const char *str, size_t str_size)
{
   if(str_size > data_size)
      return false;
   
   const char * ptr = &data[data_size - str_size];
   return (strncmp(ptr, str, str_size) == 0);
}

/* 
 * Looks for a specific start string in a AT command response.
 */
char* at_parse_get_line_sz(AtResp *resp, const char *start, size_t size, char **params)
{
   char *line = at_parse_get_first_line(resp);

   while(line)
   {
      if(strncmp((const char*)line, (const char *)start, size) == 0)
      {
         if(params)
         {
            *params = &line[size];
         }
         return line;
      }
      line = at_parse_get_next_line(resp);
   }
   
   return 0;
}

/* 
 * Looks for a specific start string in a AT command response.
 */
char* at_parse_get_line_arg(AtResp *resp, const char *start, char **arg)
{
   size_t len = strlen(start);
   return at_parse_get_line_sz(resp, start, len, arg);
}

/* 
 * Looks for a specific start string in a AT command response.
 */
char* at_parse_get_line(AtResp *resp, const char *start)
{
   size_t len = strlen(start);
   return at_parse_get_line_sz(resp, start, len, 0);
}

bool at_parse_is_digit(char b)
{
   return(b >= '0' && b <= '9');
}

bool at_parse_is_eol(uint8_t b)
{
   return(b == '\r' || b == '\n' || b == 0);
}

bool at_parse_is_separator(uint8_t b)
{
   return(b == ',' || b == ' ');
}

bool at_parse_is_valid_char(uint8_t b)
{
   return(b >= ' ' && b <= '~');
}

bool at_parse_get_digit(const char **line, uint8_t *value)
{
   if(!at_parse_is_digit(**line)) 
   {
      return false;
   }
   
   if(value)
      *value = **line - '0';

   (*line)++;

   return true;
}

/* 
 * Gets a unsigned 16 bit integer from a string.
 */
bool at_parse_get_num16(const char **line, uint16_t *value)
{
   const char *pos = *line;
   uint16_t num = 0;

   while(at_parse_is_digit(*pos))
   {
      num = (num << 3) + (num << 1) + (*pos - '0');
      pos++;
   }

   if(pos == *line) 
      return false;
   
   if(!at_parse_is_eol(*pos) && !at_parse_is_separator(*pos)) 
      return false;

   *line = pos;
   if(value) *value = num;
   return true;
}

/* 
 * Gets a unsigned 32 bit integer from a string.
 */
bool at_parse_get_num32(const char **line, uint32_t *value)
{
   const char *pos = *line;
   uint32_t num = 0;

   while(at_parse_is_digit(*pos))
   {
      num = (num << 3) + (num << 1) + (*pos - '0');
      pos++;
   }

   if(pos == *line) 
      return false;
   
   if(!at_parse_is_eol(*pos) && !at_parse_is_separator(*pos)) 
      return false;

   *line = pos;
   if(value) 
      *value = num;
   
   return true;
}

/* 
 * Gets a signed 16 bit integer from a string.
 */
bool at_parse_get_signed_num(const char **line, int16_t *value)
{
   const char *pos = *line;
   int16_t num = 0;
   bool minus = false;

   while(at_parse_is_digit(*pos) || *pos == '-')
   {
      if(*pos == '-')
      {
         minus = true;
      }
      else
      {
         num = (num << 3) + (num << 1) + (*pos - '0');
      }
      pos++;
   }

   if(pos == *line) 
      return false;
   
   if(!at_parse_is_eol(*pos) && !at_parse_is_separator(*pos)) 
      return false;

   *line = pos;
   if(value) *value = minus ? -num : num;
   
   return true;
}

/* 
 * Gets a signed 32 bit integer from a string.
 */
bool at_parse_get_signed_num32(const char **line, int32_t *value)
{
   const char *pos = *line;
   int32_t num = 0;
   bool minus = false;

   while(at_parse_is_digit(*pos) || *pos == '-')
   {
      if(*pos == '-')
      {
         minus = true;
      }
      else
      {
         num = (num << 3) + (num << 1) + (*pos - '0');
      }
      pos++;
   }

   if(pos == *line) return false;
   if(!at_parse_is_eol(*pos) && !at_parse_is_separator(*pos)) return false;

   *line = pos;
   if(value) *value = minus ? -num : num;
   
   return true;
}

/* 
 * Gets a quoted substring from a string.
 */
bool at_parse_get_string(const char **line, char *str, size_t size)
{
   const char *pos = *line;

   if(*pos != '\"') return false;
   pos++;

   while(size && *pos != '\"')
   {
      if(!at_parse_is_valid_char(*pos))
      {
         // Invalid char.
         return false;
      }

      if(str)
      {
         *str = *pos;
         str++;
         size--;
      }
      pos++;
   }

   if(size == 0)
   {
      // Buffer too small.
      return false;
   }

   pos++;
   *line = pos;
   if(str) *str = 0;
   
   return true;
}

bool at_parse_get_param(const char *src, const char * header, char * dest, size_t dest_size)
{
   memset(dest, 0, dest_size);
   
   while(header && *header)
   {
      if(*header != *src)
         return false;
      
      header++;
      src++;
   }
   
   size_t size = 0;
   
   while(*src && size < dest_size - 1)
   {
      if(!at_parse_is_valid_char(*src))
      {
         return true;
      }
      
      *dest++ = *src++;
      size++;
   }
   
   return true;
}

/* 
 * Extracts the parameter values from a string.
 */
bool at_parse_extract_arg(const char *arg, const char *header, const char *format, ...)
{
   va_list argp;
   va_start(argp, format);

   if(!*format)
   {
      DBG(kLvlError, "at_parse, empty format provided.");
      return false;
   }
   
   // DBG(kLvlDbg, "arg = %s", arg);
   
   while(header && *header)
   {
      if(*header != *arg)
         return false;
      
      header++;
      arg++;
   }

   while(*format)
   {
      switch(*format)
      {
         case 'd':
         {
            uint8_t *digit = va_arg(argp, uint8_t *);
            if(!at_parse_get_digit(&arg, digit))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 'n':
         {
            uint16_t *num = va_arg(argp, uint16_t *);
            if(!at_parse_get_num16(&arg, num))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 'N':
         {
            uint32_t *num = va_arg(argp, uint32_t *);
            if(!at_parse_get_num32(&arg, num))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 'i':
         {
            int16_t *num = va_arg(argp, int16_t *);
            if(!at_parse_get_signed_num(&arg, num))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 'I':
         {
            int32_t *num = va_arg(argp, int32_t *);
            if(!at_parse_get_signed_num32(&arg, num))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 's':
         {
            char *str = va_arg(argp, char *);
            if(!at_parse_get_string(&arg, str, 256))
            {
               // DbgPrint
               return false;
            }
            break;
         }
         case 'k':
         {
            arg++;
            break;
         }
         default:
         {
            if(*format != *arg)
            {
               DBG(kLvlError,"at_parse, invalid format provided.");
               return false;
            }
            arg++;
         }
      }
      format++;
   }
   
   va_end(argp);

   return true;
}
