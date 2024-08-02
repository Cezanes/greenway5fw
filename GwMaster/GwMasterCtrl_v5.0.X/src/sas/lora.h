#ifndef RADIO_H
#define RADIO_H

#include "types.h"

#define LORA_CALLBACKS_MAX                        15
#define LORA_FREQ                                868
#define LORA_MAX_MSG_SIZE                        200
#define LORA_HOST_BROADCAST                      255

enum
{
   kRadioAddrBroadcast = 0,
   kRadioAddrInvalid   = 0xFF,
};

enum 
{
   kRmsgEventUnkown = 0,
   kRmsgEventDestUnreachable,
   kRmsgEventRefused,
   kRmsgEventStarted,
   kRmsgEventBadConnection,
   kRmsgEventCancelled,
   kRmsgEventDone,
};

typedef struct __attribute__ ((packed))
{
   uint16_t crc;
   uint8_t seed;
   uint8_t network;
   uint8_t dest;
   uint8_t source;
   uint8_t cmd;
} RaMsgHead;

typedef struct __attribute__ ((packed))
{
   uint8_t addr_network;
   uint8_t addr_local;   
} NetworkConfig;

typedef struct __attribute__ ((packed))
{
   uint8_t bandwidth_index;
   int8_t tx_power;
   uint16_t preamble_len;
   uint32_t freq;
   uint8_t blob_burst_count;
   uint32_t msg_process_period;
} RadioConfig;

typedef struct
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   volatile uint32_t * volatile int_reg;
   uint32_t ss_mask;
   uint32_t int_mask;
   uint8_t (* spi_xfer)(uint8_t);
   
   uint8_t * rx_buff;
   size_t rx_buff_size;
   
} HwRadioConfig;

typedef struct
{
   uint8_t reg[3];
   size_t segment_size;
   uint32_t ota_header_period;
   uint32_t ota_byte_period;
} LoraMode;


typedef void (*RaMsgCallback)(const RaMsgHead * msg, uint32_t size);


void lora_init(const NetworkConfig * net_config, const RadioConfig * app_config, const HwRadioConfig * spi);
void lora_start(void);
void lora_service(void);
void lora_int_sig(void);

void lora_set_cb(void (*on_msg_sent)(uint32_t));
void lora_update_config(const RadioConfig * config);
void lora_add_handler(const uint8_t type, const RaMsgCallback cb);
void lora_prepare_send(RaMsgHead * msg, const uint32_t size);
void lora_send(RaMsgHead * msg, const uint32_t size);
void lora_handle_msg(const RaMsgHead * msg, uint32_t size);

bool lora_available(void);

bool lora_clear_to_send(void);
uint32_t lora_air_time(const size_t size);
const LoraMode * lora_bandwidth(const size_t index);

const char * lora_event_str(const size_t event);

#endif