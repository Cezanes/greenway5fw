#include "rmsg_blob.h"
#include "rmsg_type.h"
#include "slink.h"

#include "sal/debug.h"
#include "sal/timer.h"


typedef enum
{
   kBlobStateIdle = 0,
   kBlobStateTxStart,
   kBlobStateTxData,
   kBlobStateTxSeq,
   kBlobStateTxDone,
      
   kBlobStateRxData,
   kBlobStateRxDone,
      
   kBlobStateLast,
} BlobState;

static const char * state_str[] = 
{
   "Idle",
   "TxStart",
   "TxData",
   "TxSeq",
   "TxDone",
   "RxData",
   "RxDone",
};

static const char * blob_cmd_str[] = 
{
   "Invalid",
   "Ack",
   "Nack",
   "Start",
   "Data",
   "SeqReq",
   "SeqRsp",
   "Cancel",
   "Done",
};


typedef void (* BlobRecvMsgHandler)(const RaMsgHead * msg, const uint32_t size);

typedef struct
{
   uint32_t data_size;
   uint32_t ref_segment;
   uint32_t cur_segment;
   uint32_t total_segments;
   uint32_t map;

   uint32_t packet_loss;
   uint32_t packet_sent;
   uint32_t packet_recv;
   uint32_t last_received_stamp;
   
   uint32_t start_stamp;
   
   RmsgMessageContext context;
   
   size_t segment_size;
   size_t burst_count;
   size_t burst_index;
} BlobSession;

typedef struct
{
   BlobState state;
   
   uint8_t * buff;
   size_t buff_size;
   
   size_t ref_burst_count;
   size_t ref_segment_size;
   uint32_t ref_ota_header_period;
   uint32_t ref_ota_byte_period;
   uint32_t ref_msg_process_period;
   
   BlobSession session;
   
   uint8_t peer_addr;
   
   size_t map_size;
   bool use_timeout;
   uint32_t request_timestamp;
   uint32_t response_timeout;
   
   size_t timeout_retry_count;
   
   void (*on_send_msg)(RaMsgHead * msg, const uint32_t size);
   void (*on_recv_msg)(const RaMsgHead * msg, const uint32_t size);
   void (*on_event)(const size_t event);
   void (*on_busy)(const bool busy);
   
} BlobInternal;

//////////////////////////////////////////////////////////////////////////////

static void handle_msg_ack(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_nack(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_start(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_data(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_seq_req(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_seq_rsp(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_cancel(const RaMsgHead * msg, const uint32_t size);
static void handle_msg_done(const RaMsgHead * msg, const uint32_t size);

static void blob_tx_start();
static void blob_tx_data();
static void blob_tx_req_seq();
static void blob_tx_done();
static void blob_activate_timeout(bool on);

//////////////////////////////////////////////////////////////////////////////

static BlobInternal blob;

static const struct 
{
   uint8_t cmd;
   BlobRecvMsgHandler handler;
} blob_recv_msg_handlers[] = 
{
   {kRadioBlobAck,     &handle_msg_ack},
   {kRadioBlobNack,    &handle_msg_nack},
   {kRadioBlobStart,   &handle_msg_start},
   {kRadioBlobData,    &handle_msg_data},
   {kRadioBlobSeqReq,  &handle_msg_seq_req},
   {kRadioBlobSeqRsp,  &handle_msg_seq_rsp},
   {kRadioBlobCancel,  &handle_msg_cancel},
   {kRadioBlobDone,    &handle_msg_done},
};

//////////////////////////////////////////////////////////////////////////////

void rmsg_blob_init(const BlobConfig * const config)
{
   blob = (BlobInternal) 
   {
      .buff = config->buff,
      .buff_size = config->buff_size,
      .on_send_msg = config->on_send_msg,
      .on_recv_msg = config->on_recv_msg,
      .on_event = config->on_event,
      .on_busy = config->on_busy,
      .ref_burst_count = config->burst_count,
      .ref_msg_process_period = config->msg_process_period,
   };
   
   blob.map_size = (sizeof(blob.session.map) * 8) - 2;
   
   if (blob.ref_burst_count > blob.map_size)
      blob.ref_burst_count = blob.map_size;
   
   if (blob.ref_segment_size > 200)
      blob.ref_segment_size = 200;
}

bool rmsg_blob_config(const BlobSessionConfig * config)
{
   if (blob.state != kBlobStateIdle)
   {
      DBG(kLvlError, "blob, cannot change param while in session (%s)", state_str[blob.state]);
      return false;
   }
   
   blob.ref_segment_size = config->segment_size;
   blob.ref_ota_header_period = config->ota_header_period;
   blob.ref_ota_byte_period = config->ota_byte_period;
   
   return true;
}

bool rmsg_blob_busy()
{
   return (blob.state != kBlobStateIdle);
}

void rmsg_blob_event(const size_t event_id)
{
   if (blob.session.context.event)
      (*blob.session.context.event)(blob.session.context.id, event_id);
}

void rmsg_blob_progress(const uint32_t sent)
{
   if (blob.session.context.progress)
      (*blob.session.context.progress)(blob.session.context.id, sent, blob.session.data_size);
}

static void blob_state(const size_t state)
{
   bool activate_resend = false;
   
   if (blob.state != state)
   {
      activate_resend = true;
      DBG(kLvlVerb, "blob, state %s", state_str[state]);
      
      if (blob.state == kBlobStateIdle)
      {
         blob.session.last_received_stamp = timer_tick();
         blob.session.start_stamp = blob.session.last_received_stamp;
         
         if(blob.on_busy)
            (blob.on_busy)(true);
      }
      
      if(state == kBlobStateIdle)
      {
         if(blob.on_busy)
            (blob.on_busy)(false);
      }
   }
   
   switch(state)
   {
      case kBlobStateIdle:
      {
         activate_resend = false;
         blob_activate_timeout(false);
         blob.session = (BlobSession) {0};
         break;
      }
     
      case kBlobStateTxStart:
      {
         blob_tx_start();
         break;
      }
      
      case kBlobStateTxData:
      { 
         activate_resend = false;
         blob_activate_timeout(false);
         blob_tx_data();
         break;
      }
      
      case kBlobStateTxSeq:
      {
         blob_tx_req_seq();
         break;
      }
      
      case kBlobStateTxDone:
      {
         blob_tx_done();
         break;
      }
      
      case kBlobStateRxData:
      {
         activate_resend = false;
         break;
      }
      
      case kBlobStateRxDone:
      {
         activate_resend = false;
         break;
      }
   }
   
   if (activate_resend)
      blob_activate_timeout(true);
   
   blob.state = state;
}

static bool skip = false;
static bool emulate = false;

static void blob_send_msg(RaMsgHead * msg, const size_t size)
{
   const RaMsgBlobCmd * msg_blob = (const RaMsgBlobCmd *)msg;
   
   blob.response_timeout = blob.ref_ota_header_period + size * blob.ref_ota_byte_period + blob.ref_msg_process_period;
   blob.response_timeout += blob.ref_ota_header_period + blob.ref_segment_size * blob.ref_ota_byte_period;
   blob.response_timeout += blob.ref_msg_process_period;

   DBG(kLvlDbg, "blob, sending msg %s, %u, to %u", blob_cmd_str[msg_blob->blob_cmd], size, msg->dest);

   blob.session.packet_sent++;
   
   skip = !skip;
   
   /*if (msg_blob->blob_cmd == kRadioBlobData)
   {
      if (!skip)
      {
         if (blob.on_send_msg)
            (*blob.on_send_msg)(msg, size);
      }
      else
      {
         emulate = true;
      }
   }
   else*/
   {
      if (blob.on_send_msg)
         (*blob.on_send_msg)(msg, size);
   }
}

static void blob_rx_done(void)
{
   DBG(kLvlInfo, "blob, recv successful %u bytes, %u sent, %u recv, %u loss, duration %u", 
      blob.session.data_size, 
      blob.session.packet_sent, 
      blob.session.packet_recv, 
      blob.session.packet_loss, 
      timer_tick() - blob.session.start_stamp);
   
   uint32_t recv_size = blob.session.data_size;
   
   blob_state(kBlobStateIdle);
   
   if (blob.on_recv_msg)
      (*blob.on_recv_msg)((const RaMsgHead *)blob.buff, recv_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void blob_send_cmd(const uint8_t cmd)
{
   RaMsgBlobCmd msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      
      .blob_cmd = cmd,
   };
   
   blob_send_msg(&msg.head, sizeof(msg));
}

static void blob_send_ack(const uint8_t cmd)
{
   RaMsgBlobAck msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobAck,
      .acked_cmd = cmd,
   };
   
   blob_send_msg(&msg.head, sizeof(msg));
}

static void blob_send_nack(const uint8_t cmd, const uint8_t error)
{
   RaMsgBlobNack msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobNack,
      .error = error,
      .nacked_cmd = cmd,
   };
   
   blob_send_msg(&msg.head, sizeof(msg));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void blob_tx_start(void)
{
   RaMsgBlobStart msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobStart,
      .total_size = blob.session.data_size,
      .segment_size = blob.session.segment_size,
      .burst_count = blob.session.burst_count,
   };
   
   blob_send_msg(&msg.head, sizeof(msg));
}

static void blob_tx_data(void)
{   
   if (blob.session.burst_index >= blob.session.burst_count ||
       blob.session.cur_segment - blob.session.ref_segment >= blob.map_size)
   {
      blob_state(kBlobStateTxSeq);
      return;
   }
   
   while(blob.session.map & 1)
   {
      blob.session.map >>= 1;
      blob.session.cur_segment++;
   }
   
   blob.session.map >>= 1;
   
   uint32_t offs = blob.session.cur_segment * blob.session.segment_size;
   
   uint32_t size = blob.session.data_size - offs;
   if (size > blob.session.segment_size)
      size = blob.session.segment_size;

   if (blob.session.cur_segment >= blob.session.total_segments ||
       blob.session.cur_segment - blob.session.ref_segment >= blob.map_size)
   {
       blob_state(kBlobStateTxSeq);
       return;
   }
   
   DBG(kLvlVerb, "blob, send %u/%u, %u/%u %04X", blob.session.cur_segment + 1, blob.session.total_segments, offs + size, blob.session.data_size, blob.session.map);

   uint8_t buff[sizeof(RaMsgBlobData) + RMSG_MAX_SEGMENT_SIZE];
   RaMsgBlobData * msg = (RaMsgBlobData *) buff;

   *msg = (RaMsgBlobData)
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobData,
      .segment = blob.session.cur_segment,
   };

   blob.session.burst_index++;
   blob.session.cur_segment++;

   memcpy(msg + 1, &blob.buff[offs], size);
   blob_send_msg(&msg->head, sizeof(RaMsgBlobData) + size);
}

static void blob_tx_req_seq(void)
{
   RaMsgBlobCmd msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobSeqReq,
   };

   blob_send_msg(&msg.head, sizeof(RaMsgBlobCmd));
}

static void blob_tx_done()
{
   RaMsgBlobCmd msg =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobDone,
   };

   blob_send_msg(&msg.head, sizeof(RaMsgBlobCmd));
}

static void blob_rx_timeout()
{
   DBG(kLvlWarn, "blob, rx timeout, resend...");
   blob_state(blob.state);
}

static void blob_rx_timeout_final()
{
   DBG(kLvlWarn, "blob, rx timeout, canceling");
   
   if (blob.state == kBlobStateTxStart)
   {
      rmsg_blob_event(kRmsgEventDestUnreachable);
   }
   else
   {
      rmsg_blob_event(kRmsgEventBadConnection);
   }
   
   blob_state(kBlobStateIdle);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void handle_msg_start(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobStart * msg_start = (const RaMsgBlobStart *)msg;

   if (blob.state != kBlobStateIdle && blob.state != kBlobStateRxData)
   {
      blob_send_nack(kRadioBlobStart, kRadioBlobErrBusy);
      DBG(kLvlWarn, "blob, recv start but wrong state %s", state_str[blob.state]);
      return;
   }
   
   if (msg_start->total_size > blob.buff_size)
   {
      blob_send_nack(kRadioBlobStart, kRadioBlobErrSize);
      DBG(kLvlWarn, "blob, recv start but size too big %u vs %u", msg_start->total_size, blob.buff_size);
      return;
   }
   
   if (msg_start->total_size < sizeof(RaMsgHead))
   {
      blob_send_nack(kRadioBlobStart, kRadioBlobErrSize);
      DBG(kLvlWarn, "blob, recv start but size too small %u vs %u", msg_start->total_size, sizeof(RaMsgHead));
      return;
   }
   
   if (msg_start->burst_count == 0 || msg_start->segment_size == 0)
   {
      blob_send_nack(kRadioBlobStart, kRadioBlobErrSize);
      DBG(kLvlWarn, "blob, recv start but zero param %u, %u", msg_start->burst_count, msg_start->segment_size);
      return;
   }
   
   blob.peer_addr = msg_start->head.source;
   
   blob.session = (BlobSession) {
      .data_size = msg_start->total_size,
      .segment_size = msg_start->segment_size,
      .burst_count = msg_start->burst_count,
   };
   
   blob.session.total_segments = blob.session.data_size / blob.session.segment_size;
   if ((blob.session.data_size % blob.session.segment_size) > 0)
      blob.session.total_segments++;
   
   DBG(kLvlInfo, "blob, start recv %u bytes, %u segments, %u segsize", blob.session.data_size, blob.session.total_segments, blob.session.segment_size);
   
   blob_send_ack(kRadioBlobStart);
   blob_state(kBlobStateRxData);
}

static void handle_msg_ack(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobAck * msg_ack = (const RaMsgBlobAck *)msg;
   
   if (msg_ack->acked_cmd == kRadioBlobStart)
   {
      if (blob.state != kBlobStateTxStart)
      {
         DBG(kLvlError, "blob, recv start ack but state %s", state_str[blob.state]);
         return;
      }
      
      rmsg_blob_event(kRmsgEventStarted);
      blob_state(kBlobStateTxData);
   }
   else if (msg_ack->acked_cmd == kRadioBlobDone)
   {
      if (blob.state != kBlobStateTxDone)
      {
         DBG(kLvlError, "blob, recv done ack but state %s", state_str[blob.state]);
         return;
      }
      
      DBG(kLvlInfo, "blob, send successful %u bytes, %u sent, %u recv, %u loss, duration %u", 
         blob.session.data_size, 
         blob.session.packet_sent, 
         blob.session.packet_recv, 
         blob.session.packet_loss, 
         timer_tick() - blob.session.start_stamp);
      
      rmsg_blob_event(kRmsgEventDone);
      
      blob_state(kBlobStateIdle);
   }
   else
   {
      DBG(kLvlError, "blob, unexpected ack %s, state %s", blob_cmd_str[msg_ack->acked_cmd], state_str[blob.state]);
   }
}

static void handle_msg_nack(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobNack * msg_nack = (const RaMsgBlobNack *)msg;
   
   if (msg_nack->nacked_cmd != kRadioBlobStart && blob.state != kBlobStateTxStart)
   {
      DBG(kLvlError, "blob, unexpected nack %s for %s", blob_cmd_str[msg_nack->nacked_cmd], state_str[blob.state]);
      return;
   }
   
   DBG(kLvlWarn, "blob, peer nacked coz %u", msg_nack->error);
   
   rmsg_blob_event(kRmsgEventRefused);
   
   blob_state(kBlobStateIdle);
}

static void handle_msg_data(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobData * msg_data = (const RaMsgBlobData *)msg;
   
   if (blob.state != kBlobStateRxData)
   {
      DBG(kLvlError, "blob, recv msg data but in wrong state %s", state_str[blob.state]);
      return;
   }
   
   uint32_t data_size = size - sizeof(RaMsgBlobData);
   
   if (data_size > blob.session.segment_size)
   {
      DBG(kLvlError, "blob, recv segment size larger than expected size %u vs %u", data_size, blob.session.segment_size);
      return;
   }
   
   if (msg_data->segment != blob.session.total_segments - 1 && data_size != blob.session.segment_size)
   {
      DBG(kLvlError, "blob, recv segment size different than expected %u vs %u", data_size, blob.session.segment_size);
      return;
   }
   
   if (msg_data->segment < blob.session.ref_segment)
   {
      DBG(kLvlError, "blob, recv lower segment index %u vs %u", msg_data->segment, blob.session.ref_segment);
      return;
   }
   
   if (msg_data->segment >= blob.session.total_segments)
   {
      DBG(kLvlError, "blob, recv invalid segment index %u vs %u", msg_data->segment, blob.session.total_segments);
      return;
   }

   uint32_t offs = msg_data->segment * blob.session.segment_size;
   memcpy(&blob.buff[offs], msg_data + 1, data_size);

   if (blob.session.ref_segment == msg_data->segment)
   {
      blob.session.ref_segment++;
      
      while(blob.session.map & 1)
      {
         blob.session.ref_segment++;
         blob.session.map >>= 1;
      }
      
      blob.session.map >>= 1;
   }
   else
   {
      uint32_t dif = msg_data->segment - blob.session.ref_segment;
      
      if (dif > blob.map_size)
      {
         DBG(kLvlWarn, "blob, recv too farther segment %u", dif);
         return;
      }
      
      blob.session.map |= (uint32_t)1 << (dif - 1);
   }
   
   DBG(kLvlVerb, "blob, recv %u/%u, %u/%u %04X", msg_data->segment + 1, blob.session.total_segments, offs + data_size, blob.session.data_size, blob.session.map);
}

static void handle_msg_seq_req(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobCmd * msg_seq = (const RaMsgBlobCmd *)msg;
   
   if (blob.state != kBlobStateRxData)
   {
      blob_send_nack(msg_seq->blob_cmd, kRadioBlobErrProto);
      return;
   }
   
   RaMsgBlobSeqRsp rsp =
   {
      .head = (RaMsgHead) {
         .cmd = kRadioMsgBlob,
         .dest = blob.peer_addr,
      },
      .blob_cmd = kRadioBlobSeqRsp,
      .segment = blob.session.ref_segment,
      .map = blob.session.map,
   };

   blob_send_msg(&rsp.head, sizeof(RaMsgBlobSeqRsp));
}

static void handle_msg_seq_rsp(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobSeqRsp * msg_rsp = (const RaMsgBlobSeqRsp *)msg;
   
   if (blob.state != kBlobStateTxSeq)
   {
      blob_send_nack(msg_rsp->blob_cmd, kRadioBlobErrProto);
      return;
   }
   
   uint32_t map = msg_rsp->map;
   size_t lost_count = 0;
   size_t fw_count =  blob.session.cur_segment - msg_rsp->segment;
   
   uint32_t total_sent = msg_rsp->segment * blob.session.segment_size;
   if (total_sent > blob.session.data_size)
      total_sent = blob.session.data_size;
      
   rmsg_blob_progress(total_sent);
   
   while(fw_count)
   {
      fw_count--;
      if ((map & 1) == 0)
         lost_count++;
      map >>= 1;
   }
   
   blob.session.packet_loss += lost_count;
   
   blob.session.ref_segment = msg_rsp->segment;
   blob.session.cur_segment = msg_rsp->segment;
   blob.session.burst_index = 0;
   blob.session.map = msg_rsp->map << 1;
   
   DBG(kLvlVerb, "blob, sent stats seq %u, lost %u, %04X", blob.session.ref_segment, lost_count, blob.session.map);
   
   if (blob.session.ref_segment >= blob.session.total_segments)
   {
      blob_state(kBlobStateTxDone);
   }
   else
   {
      blob_state(kBlobStateTxData);
   }
}

static void handle_msg_cancel(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobCmd * msg_cancel = (const RaMsgBlobCmd *)msg;
   
   if (blob.state == kBlobStateIdle)
   {
      DBG(kLvlError, "blob, recv msg cancel but in wrong state %s", state_str[blob.state]);
      return;
   }
   
   rmsg_blob_event(kRmsgEventCancelled);
   
   blob_state(kBlobStateIdle);
   
   DBG(kLvlWarn, "blob, transfer canceled by peer.");
}

static void handle_msg_done(const RaMsgHead * msg, const uint32_t size)
{
   const RaMsgBlobDone * msg_done = (const RaMsgBlobDone *)msg;
   
   if (blob.state != kBlobStateRxData && blob.state != kBlobStateRxDone)
   {
      DBG(kLvlError, "blob, recv msg done but in wrong state %s", state_str[blob.state]);
      return;
   }
   
   blob_send_ack(msg_done->blob_cmd);
   
   // DBGHEX(kLvlDbg, "recv data: ", blob.buff, blob.session.data_size);
   
   blob_state(kBlobStateRxDone);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool rmsg_blob_send(const RmsgMessageContext * context)
{
   if (rmsg_blob_busy())
   {
      DBG(kLvlError, "blob, cannot tx start coz busy %s", state_str[blob.state]);
      return false;
   }
   
   if (context->size > blob.buff_size)
   {
      DBG(kLvlError, "blob, cannot tx start coz size too big %u vs %u", context->size, blob.buff_size);
      return false;
   }
   
   blob.session = (BlobSession) {
      .data_size = context->size,
      .segment_size = blob.ref_segment_size,
      .burst_count = blob.ref_burst_count,
      .context = *context,
   };
   
   blob.peer_addr = context->dest;
   
   blob.session.total_segments = blob.session.data_size / blob.session.segment_size;
   if ((blob.session.data_size % blob.session.segment_size) > 0)
      blob.session.total_segments++;
   
   DBG(kLvlInfo, "blob, radio start send %u bytes, %u segments, %u segsize", blob.session.data_size, blob.session.total_segments, blob.session.segment_size);
   
   blob_state(kBlobStateTxStart);
   
   return true;
}

void rmsg_blob_get_buff(uint8_t ** const buff, size_t * const size)
{
   *buff = blob.buff;
   *size = blob.buff_size;
}

void rmsg_blob_handle_msg(const RaMsgHead * const msg, const uint32_t size)
{
   if (msg->cmd != kRadioMsgBlob)
      return;
   
   const RaMsgBlobCmd * blob_msg = (const RaMsgBlobCmd *) msg;
   
   if (blob_msg->blob_cmd < COUNT(blob_cmd_str))
   {
      DBG(kLvlDbg, "blob, recv msg %s", blob_cmd_str[blob_msg->blob_cmd]);
   }
   
   if(blob.state != kBlobStateIdle && blob.peer_addr != msg->source)
   {
      DBG(kLvlWarn, "blob, wrong peer addr %u vs %u", msg->source, blob.peer_addr);
      return;
   }
   
   bool found = true;
   
   for(size_t i = 0; i < COUNT(blob_recv_msg_handlers); i++)
   {
      if (blob_recv_msg_handlers[i].cmd == blob_msg->blob_cmd)
      {
         blob.session.packet_recv++;
         blob.session.last_received_stamp = timer_tick();
         
         (*blob_recv_msg_handlers[i].handler)(msg, size);
         
         found = true;
         break;
      }
   }
   
   if (!found)
   {
      DBG(kLvlError, "blob, unhandled msg %u", blob_msg->blob_cmd);
   }
}

static void blob_activate_timeout(bool on)
{
   if(on)
   {
      blob.request_timestamp = timer_tick();
      blob.use_timeout = true;
      blob.timeout_retry_count = RMSG_MSG_RETRY_COUNT;
   }
   else
   {
      blob.use_timeout = false;
   }
}

void rmsg_blob_msg_tx_done(const uint32_t duration)
{
   DBG(kLvlDbg, "blob, msg sent %u", duration);
   
   switch (blob.state)
   {
      case kBlobStateTxData:
      {
         blob_tx_data();
         break;
      }
   }
}

void rmsg_blob_msg_tx_fail(void)
{
   
}

void rmsg_blob_service(void)
{
   if (blob.use_timeout)
   {
      uint32_t tick = timer_tick();
      if(tick - blob.request_timestamp > blob.response_timeout)
      {
         blob.session.packet_loss++;
         
         if(blob.timeout_retry_count)
         {
            blob.timeout_retry_count--;
            blob.request_timestamp = tick;
            blob_rx_timeout();
         }
         else
         {
            blob.use_timeout = false;
            blob_rx_timeout_final();
         }
      }
   }
   
   if (blob.state == kBlobStateRxDone)
   {
      uint32_t ack_timeout =  blob.session.segment_size * blob.ref_ota_byte_period;
      ack_timeout += blob.ref_ota_header_period + blob.ref_msg_process_period;
      
      uint32_t tick = timer_tick();
      if (tick - blob.session.last_received_stamp > ack_timeout)
      {
         blob_rx_done();
      }
   }
   else if (blob.state != kBlobStateIdle)
   {
      uint32_t tick = timer_tick();
      
      uint32_t data_response_timeout =  blob.session.segment_size * blob.ref_ota_byte_period;
      data_response_timeout += blob.ref_ota_header_period + blob.ref_msg_process_period;
      data_response_timeout *= blob.session.burst_count * 2;
      
      if (blob.session.packet_sent + blob.session.packet_recv > blob.session.total_segments * 10)
      {
         DBG(kLvlWarn, "blob, unreliable connection, too many packets (%u), canceled", blob.session.total_segments * 10);
         rmsg_blob_event(kRmsgEventBadConnection);
         blob_state(kBlobStateIdle);
      }
      else if (tick - blob.session.last_received_stamp > data_response_timeout)
      {
         DBG(kLvlWarn, "blob, connection timeout (%u), %u sent, %u recv, %u loss", 
            data_response_timeout, 
            blob.session.packet_sent, 
            blob.session.packet_recv, 
            blob.session.packet_loss);
         
         rmsg_blob_event(kRmsgEventBadConnection);
         blob_state(kBlobStateIdle);
      }
   }
   
   if (emulate)
   {
      emulate = false;
      rmsg_blob_msg_tx_done(1000);
   }
}