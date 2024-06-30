/*
 * File:   atdrv.h
 * Author: cezane
 *
 * Generic AT command handler. It's meant for any device that uses AT command
 * set, like GSM Modems, Bluetooth or WiFi modules.
 */


#ifndef AT_DRV_H
#define AT_DRV_H

#include "types.h"
#include "hal/uart32mx.h"

#define AT_RESP_OVERSIZED                           200
#define AT_RESP_TIMEOUT                             201
#define AT_CMD_ENDL                              "\r\n"


typedef struct
{
   size_t code;
   const char *name;
} AtRespType;

typedef struct
{
   char *buff;
   char *line;
   size_t buff_size;
   size_t count;
   size_t code;
} AtResp;

typedef struct
{
   UartDev * uart_dev;
   uint32_t clock_src;
   uint32_t baud;
   uint8_t * rx_buff;
   size_t rx_buff_size;
   const AtRespType * at_resp_type;
   size_t at_resp_count;
} AtConfig;


void at_init(const AtConfig * config);
void at_command(const char *data);

void at_rx_clear(void);
size_t ar_rx_size(void);
bool at_rx_error(void);
void at_clear_resp(AtResp *resp);
void at_send_data(const char * data, size_t size);
bool at_get_rx_char(char *b, size_t timeout);
bool at_rx_getc(char *b);

size_t at_get_response(AtResp *resp);
size_t at_get_response_to(AtResp *resp, uint32_t timeout);

char* at_parse_get_first_line(AtResp *resp);
char* at_parse_get_next_line(AtResp *resp);
bool at_parse_ends_with(const char *data, size_t data_size, const char *str, size_t str_size);
   
bool at_parse_is_valid_char(uint8_t b);
size_t at_parse_get_line_size(const char *line);
size_t at_read_till_to(char *data, size_t size, size_t timeout);
bool at_repeat_till_to(const char * cmd, AtResp *resp, size_t code, size_t timeout_ms, size_t delay_ms);

bool at_parse_get_num32(const char **line, uint32_t *value);
bool at_parse_get_string(const char **line, char *str, size_t size);
bool at_parse_get_param(const char *src, const char * header, char * dest, size_t dest_size);
bool at_parse_extract_arg(const char *arg, const char *header, const char *format, ...);



#endif
