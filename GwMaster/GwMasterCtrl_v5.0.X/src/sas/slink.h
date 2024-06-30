#ifndef SLINK_H
#define SLINK_H

#include "types.h"

enum SeMsgSlink
{
   kMsgSlinkIvalid   = 0,
   kMsgSlinkNotSupported,
   kMsgSlinkAck,
   kMsgSlinkNack,
   kMsgSlinkHello,
   kMsgSlinkCustom   = 100,
};

// Common message header format.
typedef struct __attribute__ ((packed))
{
   uint8_t tag;
   uint16_t seq;
   uint16_t src;
   uint8_t endp;
   uint16_t id;
   uint16_t size;
   uint8_t crc;
} SeMsgHead;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint16_t acked_msg;
} SeMsgAck;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint16_t nacked_msg;
   uint8_t reason;
} SeMsgNack;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint16_t unknown_msg;
} SeMsgUnknown;

typedef struct
{
   void* user;
   uint8_t * rx_buff;
   size_t rx_size;
   void (* send_byte)(void* user, const uint8_t);
   void (* enable_int)(void);
   void (* disable_int)(void);
   bool (* req_buffer)(void* user);
   void (* rel_buffer)(void* user);
   
   size_t rx_count;
   uint8_t  rx_last_byte;
   uint16_t last_seq;
   bool rx_head_checked;
   
   size_t in_msg_count;
   size_t in_msg_start;
   size_t rx_msg_count;
   uint8_t in_msg_hdr_crc;
   uint16_t in_msg_crc;
   
   size_t rx_activity;
   uint32_t last_byte_ts;
   
   size_t errors;
   
} SlinkInstance;


void slink_init(SlinkInstance * inst);
void slink_start(SlinkInstance * inst);
void slink_recv_byte(SlinkInstance * inst, uint8_t b);
bool slink_have_msg(SlinkInstance * inst);
void slink_send_msg(SlinkInstance * inst, SeMsgHead * header);
void slink_discard(SlinkInstance * inst);
void slink_service(SlinkInstance * inst);

SeMsgHead * slink_receive(SlinkInstance * inst);

uint16_t slink_begin_send_msg(SlinkInstance * inst, SeMsgHead *header, size_t size);
uint16_t slink_continue_data_msg(SlinkInstance * inst, const void * ptr, size_t size, uint16_t crc);
void slink_finalize_msg(SlinkInstance * inst, uint16_t crc);

#endif
   