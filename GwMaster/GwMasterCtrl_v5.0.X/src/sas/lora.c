#include "lora.h"
#include "types.h"

#include "sal/debug.h"
#include "sal/timer.h"
#include "sal/pulse.h"

#include "drv/rfm95.h"

#include "lib/utils.h"
#include "lib/aes.h"

#include "cfg/app_config.h"
#include "cfg/hw_config.h"

#include "rmsg_type.h"

static const LoraMode lora_mode_table[] =
{
   {
      .reg = { 0x98,   0x74,    0x00}, // Bw500Cr45Sf128
      .segment_size = 128,
      .ota_header_period = 10,
      .ota_byte_period = 1,
   },
   
   {
      .reg = { 0x88,   0x94,    0x00}, // 250kbps, 4/8, SF9
      .segment_size = 64,
      .ota_header_period = 50,
      .ota_byte_period = 4,
   },
   
   {
      .reg = { 0x88,   0xA4,    0x00}, // 250kbps, 4/8, SF10
      .segment_size = 64,
      .ota_header_period = 100,
      .ota_byte_period = 7,
   },
   
   {
      .reg = { 0x58,   0x74,    0x00}, // 31.25kbps, 4/8, SF7
      .segment_size = 32,
      .ota_header_period = 100,
      .ota_byte_period = 9,
   },
   
   {
      .reg = { 0x78,   0xA4,    0x00}, // 125kbps, 4/8, SF10
      .segment_size = 32,
      .ota_header_period = 200,
      .ota_byte_period = 14,
   },
   
   {
      .reg = { 0x58,   0x74,    0x00}, // 15.6kbps, 4/8, SF7
      .segment_size = 32,
      .ota_header_period = 200,
      .ota_byte_period = 17,
   },
   
   {
      .reg = { 0x78,   0xB4,    0x00}, // 125kbps, 4/8, SF11
      .segment_size = 16,
      .ota_header_period = 300,
      .ota_byte_period = 27,
   },
   
   {
      .reg = { 0x78,   0xC4,    0x00}, // 125kbps, 4/8, SF12
      .segment_size = 16,
      .ota_header_period = 550,
      .ota_byte_period = 60,
   },
};

static const char * event_str[] = 
{
   "EventUnkown",
   "EventDestUnreachable",
   "EventRefused",
   "EventStarted",
   "EventBadConnection",
   "EventCancelled",
   "EventDone",
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const uint8_t aes_iv[16]  = {0x84, 0xe1, 0xc0, 0x45, 0x3f, 0x7a, 0xb3, 0xac, 0xb3, 0xa1, 0x2b, 0xfc, 0xd3, 0x06, 0x9b, 0xa6};
const uint8_t aes_key[16] = {0xd7, 0x9d, 0xc5, 0xa6, 0x9d, 0xee, 0x46, 0x72, 0xf3, 0xc2, 0x2e, 0xa9, 0xf3, 0x39, 0xc2, 0x4d};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct
{
   uint8_t id;
   RaMsgCallback cb;
} RaMsgHandler;

typedef struct
{
   RadioConfig config;
   const NetworkConfig * net;
   
   bool available;
   
   size_t mode_index;
   size_t radio_modes_count;
   uint32_t current_trans_duration;
   uint32_t last_msg_stamp;
   
   size_t handler_count;
   RaMsgHandler handlers[LORA_CALLBACKS_MAX];   
   void (*on_msg_sent)(uint32_t);
   
} LoraInternal;

static LoraInternal lora;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void send_unknown(const uint8_t cmd, const uint8_t dest);

static void lora_on_recv(const uint8_t *, uint32_t, uint8_t);
static void lora_on_recv_to(void);
static void lora_on_recv_crc_err(void);
static void lora_on_sent(void);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void lora_init(const NetworkConfig * net_config, const RadioConfig * radio_config, const HwRadioConfig * hwcfg)
{
   lora = (LoraInternal) 
   {
     .config = *radio_config,
     .mode_index = radio_config->bandwidth_index,
     .radio_modes_count = COUNT(lora_mode_table),
     .net = net_config,
   };
   
   const Rfm95Config rfm95_config = 
   {
      .ss_reg_set = hwcfg->ss_reg_set,
      .ss_reg_clear = hwcfg->ss_reg_clear,
      .int_reg = hwcfg->int_reg,
      .ss_mask = hwcfg->ss_mask,
      .int_mask = hwcfg->int_mask,
      .spi_xfer = hwcfg->spi_xfer, 
      
      .on_recv = &lora_on_recv,
      .on_recv_to = &lora_on_recv_to,
      .on_recv_crc_err = &lora_on_recv_crc_err,
      .on_sent = &lora_on_sent,
   };
      
   rfm95_init(&rfm95_config);
}

void lora_int_sig(void)
{
   rfm95_int_sig();
}

static void print_config(void)
{
   //DBG(kLvlVerb, "lora, addr %u, net %u", lora.net->addr_network, lora.net->addr_local);
   DBG(kLvlVerb, "lora, bw %u, pow %u, pre %u, freq %u", lora.config.bandwidth_index, lora.config.tx_power, lora.config.preamble_len, lora.config.freq);
}

void lora_start(void)
{
   if(!rfm95_start())
   {
      DBG(kLvlError, "lora, rfm95 init failed");
      return;
   }
   
   lora.available = true;
   
   rfm95_set_tx_power(lora.config.tx_power, false);
   rfm95_set_preamble_length(lora.config.preamble_len);
   
   uint32_t freq = (868 * 1000000.0) / RH_RF95_FSTEP;
   rfm95_set_frequency(freq);
   
   lora_bandwidth(lora.mode_index);
   
   print_config();
   
   rfm95_set_mode_rx();
   
   
}

bool lora_available(void)
{
   return lora.available;
}

void lora_set_cb(void (*on_msg_sent)(uint32_t))
{
   lora.on_msg_sent = on_msg_sent;
}

void lora_update_config(const RadioConfig * config)
{
   if(!lora.available)
   {
      DBG(kLvlWarn, "lora, rfm95 not available");
      return;
   }
   
   rfm95_set_mode_idle();
   
   if(config->bandwidth_index != lora.config.bandwidth_index)
   {
      lora_bandwidth(config->bandwidth_index);
   }
   
   if(config->preamble_len != lora.config.preamble_len)
   {
      rfm95_set_preamble_length(config->preamble_len);
   }
   
   if(config->tx_power != lora.config.tx_power)
   {
      rfm95_set_tx_power(config->tx_power, false);
   }
   
   lora.config = *config;
   
   print_config();
   rfm95_set_mode_rx();
}

const LoraMode * lora_bandwidth(const size_t index)
{
   if(!lora.available)
   {
      DBG(kLvlWarn, "lora, rfm95 not available");
      return NULL;
   }
   
   if (index >= lora.radio_modes_count)
   {
      DBG(kLvlError, "lora, invalid config index %u", index);
      return NULL;
   }
   
   lora.mode_index = index;
   
   rfm95_set_modem_registers(lora_mode_table[index].reg);
   rfm95_set_mode_rx();
   
   return &lora_mode_table[index];
}

static void encrypt(void * msg, uint8_t dest, uint32_t size)
{
   uint8_t iv[16];
   for(size_t i = 0; i < sizeof(iv); i++)
      iv[i] = (dest + i) ^ aes_iv[i];
   
   uint8_t buff[256];
   memset(buff, 0, sizeof(buff));
   memcpy(buff, msg, size);
   
   size_t chunks = size / sizeof(iv);
   if(size % sizeof(iv) > 0)
      chunks++;
   
   struct AES_ctx ctx;
   AES_init_ctx_iv(&ctx, aes_key, iv);
   AES_CTR_xcrypt_buffer(&ctx, buff, chunks * sizeof(iv));
   
   memcpy(msg, buff, size);
}

static void decrypt(void * msg, uint8_t src, uint32_t size)
{
   uint8_t iv[16];
   for(size_t i = 0; i < sizeof(iv); i++)
      iv[i] = (src + i) ^ aes_iv[i];
   
   uint8_t buff[256];
   memset(buff, 0, sizeof(buff));
   memcpy(buff, msg, size);
   
   size_t chunks = size / sizeof(iv);
   if(size % sizeof(iv) > 0)
      chunks++;
   
   struct AES_ctx ctx;
   AES_init_ctx_iv(&ctx, aes_key, iv);
   AES_CTR_xcrypt_buffer(&ctx, buff, chunks * sizeof(iv));
   
   memcpy(msg, buff, size);
}

void lora_handle_msg(const RaMsgHead * msg, uint32_t size)
{
   /*if(msg->dest == LORA_HOST_BROADCAST)// && msg->cmd != kRadioMsgTime)
   {
      //DBG(kLvlError, "lora, only kRadioMsgTime can be broadcasted %u", msg->cmd);
      DBG(kLvlError, "lora, broadcast deactivated %u", msg->cmd);
      return;
   }*/
   
   //DBG(kLvlVerb, "%u %u %u", lora.net->addr_local, lora.net->addr_network, msg->network);
   
   if (lora.net->addr_local != 0 && msg->network != lora.net->addr_network)
   {
      DBG(kLvlVerb, "lora, different network %u", msg->network);
      return;
   }
   
   if (msg->source == lora.net->addr_local)
   {
      DBG(kLvlError, "lora, config error, source ID collision %u", lora.net->addr_local);
      return;
   }
   
   if (msg->dest != lora.net->addr_local && msg->dest != LORA_HOST_BROADCAST)
   {
      DBG(kLvlVerb, "lora, skipping msg src %u", msg->dest);
      return;
   }
   
   pulse_start(kPulseRadio);
   
   bool found = false;
   
   for(size_t i = 0; i < lora.handler_count; i++)
   {
      if (lora.handlers[i].id == msg->cmd)
      {
         DBG(kLvlDbg, "lora, handling message %u, size %u", msg->cmd, size);
         (*lora.handlers[i].cb)(msg, size);
         found = true;
         break;
      }
   }
   
   if (!found)
   {
      DBG(kLvlWarn, "lora, unknown message type %u", msg->cmd);
      send_unknown(msg->cmd, msg->source);
   } 
}

static void lora_on_recv(const uint8_t * buff , uint32_t size, uint8_t rssi)
{   
   lora.last_msg_stamp = timer_tick();
   
   if (size < sizeof(RaMsgHead))
   {
      DBG(kLvlDbg, "lora, received message too short %u (req %u)", size, sizeof(RaMsgHead));
      return;
   }
   
   uint8_t msg_copy[256];
   const RaMsgHead * msg = (const RaMsgHead *) msg_copy;
   
   memset(msg_copy, 0, sizeof(msg_copy));
   memcpy(msg_copy, buff, size);
   decrypt(msg_copy, lora.net->addr_local, size);
   
   uint16_t crc = utils_crc16t(&msg->crc + 1, size - sizeof(msg->crc), CRC_START_CCITT_1D0F);
   if (crc != msg->crc)
   {
      memcpy(msg_copy, buff, size);
      decrypt(msg_copy, LORA_HOST_BROADCAST, size);
      
      crc = utils_crc16t(&msg->crc + 1, size - sizeof(msg->crc), CRC_START_CCITT_1D0F);
      if (crc != msg->crc)
      {
         DBG(kLvlDbg, "lora, message crc failed %04X vs %04X", msg->crc, crc);
         return;
      }
   }
   
   DBG(kLvlDbg, "lora, message received from %u, size %u", msg->source, size);
   DBGHEX(kLvlDbg, "lora, data: ", msg, size);
   
   lora_handle_msg(msg, size);
}

static void lora_on_recv_to(void)
{
   DBG(kLvlWarn, "lora, receive timeout");
}

static void lora_on_recv_crc_err(void)
{
   lora.last_msg_stamp = timer_tick();
   DBG(kLvlDbg, "lora, receive crc error");
}

static void lora_on_sent(void)
{
   uint32_t duration = timer_tick() - lora.current_trans_duration;
   DBG(kLvlDbg, "lora, message sent, %ums", duration);
   
   rfm95_set_mode_rx();
   if(lora.on_msg_sent)
      lora.on_msg_sent(duration);
}

void lora_add_handler(const uint8_t id, const RaMsgCallback cb)
{
   if(lora.handler_count >= LORA_CALLBACKS_MAX)
   {
      DBG(kLvlError, "lora, unable to add new message handlers.");
      return;
   }
   
   lora.handlers[lora.handler_count] = (RaMsgHandler) {.id = id, .cb = cb};
   lora.handler_count++;
}

static void send_unknown(const uint8_t cmd, const uint8_t dest)
{
   RaMsgUnsupported msg = {
     .head = {
       .cmd = kRadioMsgUnsupported,
       .dest = dest,
     },
     .unsupported_cmd = cmd,
   };
   
   lora_send(&msg.head, sizeof(msg));
}

void lora_prepare_send(RaMsgHead * msg, const uint32_t size)
{
   msg->network = lora.net->addr_network;
   msg->source = lora.net->addr_local;
   msg->seed = _CP0_GET_COUNT();
   msg->crc = utils_crc16t(&msg->crc + 1, size - sizeof(msg->crc), CRC_START_CCITT_1D0F);
}

void lora_send(RaMsgHead * msg, const uint32_t size)
{
   if(!lora.available)
   {
      DBG(kLvlWarn, "lora, rfm95 not available");
      return;
   }
   
   lora_prepare_send(msg, size);
   
   DBG(kLvlDbg, "lora, encrypt %u, dest %u, cmd %u, size %u, crc %04X", msg->seed, msg->dest, msg->cmd, size, msg->crc);
   
   uint8_t buff[256];
   memcpy(buff, msg, size);
   encrypt(buff, msg->dest, size);
   
   lora.current_trans_duration = timer_tick();

   pulse_start(kPulseRadio);
   
   DBG(kLvlDbg, "lora, sending msg to %u, size %u", msg->dest, size);
   DBGHEX(kLvlDbg, "lora, data: ", msg, size);
   
   lora.last_msg_stamp = timer_tick();
   rfm95_send(buff, size);
}

bool lora_clear_to_send(void)
{
   if (timer_tick() - lora.last_msg_stamp > TM_SEC_T0_TICK(5))
      return true;
   
   return false;
}

uint32_t lora_air_time(const size_t size)
{
   return lora_mode_table[lora.mode_index].ota_header_period +
      lora_mode_table[lora.mode_index].ota_byte_period * size;
}

const char * lora_event_str(const size_t event)
{  
   if(event >= COUNT(event_str))
      return NULL;
   
   return event_str[event];
}

void lora_service(void)
{
   if(!rfm95_is_valid() /*|| ((timer_tick() - radio.last_msg_stamp) > TM_MIN_T0_TICK(15))*/)
   {
      /*radio.last_msg_stamp = timer_tick() - TM_SEC_T0_TICK(10);
      DBG(kLvlWarn, "lora, rfm95 not responding, restarting...");
      radio_start();*/
   }
   else
   {
      rfm95_service(false);
   }
}
