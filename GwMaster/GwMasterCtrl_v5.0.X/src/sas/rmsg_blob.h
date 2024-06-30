#ifndef RMSG_BLOB
#define RMSG_BLOB

#include "types.h"
#include "lora.h"


#define RMSG_MAX_SEGMENT_SIZE      200
#define RMSG_MSG_RETRY_COUNT         5


typedef struct
{
   uint8_t * buff;
   uint32_t buff_size;

   size_t burst_count;
   uint32_t msg_process_period;
   
   void (*on_send_msg)(RaMsgHead * msg, const uint32_t size);
   void (*on_recv_msg)(const RaMsgHead * data, const uint32_t size);
   void (*on_busy)(const bool busy);
   void (*on_event)(const size_t event);
} BlobConfig;


typedef struct
{
   size_t segment_size;
   uint32_t ota_header_period;
   uint32_t ota_byte_period;
} BlobSessionConfig;


typedef struct
{
   RaMsgHead * msg;
   uint32_t size;
   uint32_t id;
   uint8_t dest;
   bool req_ack;
   bool retry_count;
   void (* event)(const size_t id, const size_t event);
   void (* progress)(const size_t id, const uint32_t sent, const uint32_t total);
} RmsgMessageContext;


////////////////////////////////////////////////////////////////////////////////////


void rmsg_blob_init(const BlobConfig * const config);
bool rmsg_blob_config(const BlobSessionConfig * config);
bool rmsg_blob_busy(void);

void rmsg_blob_get_buff(uint8_t ** const buff, size_t * const size);
bool rmsg_blob_send(const RmsgMessageContext * context);

void rmsg_blob_handle_msg(const RaMsgHead * const msg, const uint32_t size);
void rmsg_blob_msg_tx_done(const uint32_t duration);
void rmsg_blob_msg_tx_fail(void);

void rmsg_blob_service(void);




#endif