#ifndef SERVER_H
#define SERVER_H

#include "types.h"
#include "slink.h"
#include "hal/uart32mx.h"

#define SERVER_CALLBACKS_MAX         20

typedef void (*SeMsgCallback)(size_t itf, const SeMsgHead * msg);

typedef struct
{
   UartDev * uart;
   uint32_t clock_src;
   uint32_t baud;
   uint8_t * rx_buff;
   size_t rx_buff_size;
} SocketConfig;

typedef struct
{
   const SocketConfig * sockets;
   size_t socket_count;
   uint16_t * data_crc_per_itf;
   uint8_t * shared_rx_buff;
   size_t shared_rx_buff_size;
} ServerConfig;


void server_init(const ServerConfig * config);
void server_start(void);
void server_service(void);
void server_add_handler(size_t itf, uint16_t id, SeMsgCallback cb);
void server_send_msg(size_t itf, SeMsgHead * msg);

void server_begin_send_msg(size_t itf, SeMsgHead *header, size_t size);
void server_continue_data_msg(size_t itf, const void * ptr, size_t size);
void server_finalize_msg(size_t itf);

size_t server_rx_buff_size(void);


#endif