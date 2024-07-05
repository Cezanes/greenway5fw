#include "slink.h"
#include "sal/debug.h"
#include "lib/utils.h"
#include "sal/timer.h"

enum
{
   kSlinkErrorSkipJunk          = 1 << 0,
   kSlinkErrorDiscardUnfinished = 1 << 1,
   kSlinkErrorHdrCrc            = 1 << 2,
   kSlinkErrorDataCrc           = 1 << 3,
   kSlinkErrorBufferOverrun     = 1 << 4,
   
   kSlinkInfoRecvMsg            = 1 << 10,
};


#define SE_MSG_FRAME_START                  0x7E
#define SE_MSG_ESC_CHAR                     0x7D
#define SE_MSG_CRC_SIZE          sizeof(uint16_t)
#define SE_MSG_MIN_SIZE         sizeof(SeMsgHead)


/////////////////////////////////////////////////////////////////////////////////

// Forward declarations.
void SeStoreByte(uint8_t b);


/////////////////////////////////////////////////////////////////////////////////


void slink_init(SlinkInstance * inst)
{
   
}

void slink_start(SlinkInstance * inst)
{

}

void slink_recv_byte(SlinkInstance * inst, uint8_t b)
{
   // U1TXREG = '0' + b;
   
   if (inst->in_msg_count == 0 && b != SE_MSG_FRAME_START)
   {
      inst->errors |= kSlinkErrorSkipJunk;
      return;
   }

   // A new start? Check if previous msgs is complete.
   if (b == SE_MSG_FRAME_START)
   {
      if (inst->in_msg_count)
      {
         // Discard unfinished msg
         inst->errors |= kSlinkErrorDiscardUnfinished;
      }

      inst->rx_count -= inst->in_msg_count;
      inst->in_msg_start = inst->rx_count;
      inst->in_msg_count = 0;
   }

   if (inst->rx_count == 0 && !inst->req_buffer(inst))
   {
      // No shared buffer available
      return;
   }
   
   inst->rx_activity = true;

   // Escape it, if required.
   if (inst->rx_last_byte == SE_MSG_ESC_CHAR)
   {
      inst->rx_last_byte = 0;
      b = b ^ 0x20;
   }
   else if (b == SE_MSG_ESC_CHAR)
   {
      inst->rx_last_byte = SE_MSG_ESC_CHAR;
      return;
   }

   // If we reached the end of our buffer, discard last message.
   if (inst->rx_count >= inst->rx_size)
   {
      inst->rx_count -= inst->in_msg_count;
      inst->in_msg_start = inst->rx_count;
      inst->in_msg_count = 0;
      
      inst->errors |= kSlinkErrorBufferOverrun;
      
      if (inst->rx_count == 0)
         inst->rel_buffer(inst);
      
   }
   else
   {
      // Store it.
      inst->rx_buff[inst->rx_count] = b;
      inst->rx_count++;
      inst->in_msg_count++;

      if (inst->in_msg_count == 1)
      {
         inst->in_msg_hdr_crc = utils_crc8t_start(b);
         inst->in_msg_crc = utils_crc16t_start(b);
      }
      else if (inst->in_msg_count < sizeof(SeMsgHead))
      {
         inst->in_msg_hdr_crc = utils_crc8t_step(b, inst->in_msg_hdr_crc);
         inst->in_msg_crc = utils_crc16t_step(b, inst->in_msg_crc);
      }
      else
      {
         const SeMsgHead* hdr = (const SeMsgHead*)&inst->rx_buff[inst->in_msg_start];

         if (inst->in_msg_count == sizeof(SeMsgHead))
         {
            inst->in_msg_hdr_crc = utils_crc8t_finish(inst->in_msg_hdr_crc);
            inst->in_msg_crc = utils_crc16t_step(b, inst->in_msg_crc);

            if (inst->in_msg_hdr_crc != hdr->crc || hdr->size < SE_MSG_MIN_SIZE)
            {
               // discard
               inst->rx_count -= inst->in_msg_count;
               inst->in_msg_start = inst->rx_count;
               inst->in_msg_count = 0;
               inst->errors |= kSlinkErrorHdrCrc;
               
               if (inst->rx_count == 0)
                  inst->rel_buffer(inst);
            }
         }
         else if (inst->in_msg_count <= hdr->size)
         {
            inst->in_msg_crc = utils_crc16t_step(b, inst->in_msg_crc);
         }
         else if (inst->in_msg_count < hdr->size + SE_MSG_CRC_SIZE)
         {
            // loading crc16
         }
         else if (inst->in_msg_count == hdr->size + SE_MSG_CRC_SIZE)
         {
            inst->in_msg_crc = utils_crc16t_finish(inst->in_msg_crc);
            uint16_t found_crc = (((uint16_t)inst->rx_buff[inst->in_msg_count - 1]) << 8) | inst->rx_buff[inst->in_msg_count - 2];

            if (inst->in_msg_crc != found_crc)
            {
               DBG(kLvlVerb, "s: %u %u %u", inst->rx_count, inst->in_msg_start, inst->in_msg_count);
               DBGHEX(kLvlVerb, "data: ", &inst->rx_buff[inst->in_msg_start], inst->in_msg_count);
            
               // bad CRC, discard
               inst->rx_count -= inst->in_msg_count;
               inst->in_msg_start = inst->rx_count;
               inst->in_msg_count = 0;
               inst->errors |= kSlinkErrorDataCrc;
               
               if (inst->rx_count == 0)
                  inst->rel_buffer(inst);
            }
            else
            {
               inst->rx_msg_count++;
               inst->in_msg_start = inst->rx_count;
               inst->in_msg_count = 0;
               inst->errors |= kSlinkInfoRecvMsg;
            }
         }
      }  
   }
}

// Sends a byte to the server. Takes consideration of escaped characters.
static void slink_send_esc_byte(SlinkInstance * inst, uint8_t b)
{
   if((b == SE_MSG_FRAME_START) || (b == SE_MSG_ESC_CHAR))
   {
      (*inst->send_byte)(inst->user, SE_MSG_ESC_CHAR);
      (*inst->send_byte)(inst->user, b ^ 0x20);
   }
   else (*inst->send_byte)(inst->user, b);
}


// Sends a byte to server, ignoring any escaping.
static void slink_send_byte(SlinkInstance * inst, uint8_t b)
{
   (*inst->send_byte)(inst->user, b);
}


// Sends a message to server.
void slink_send_msg(SlinkInstance * inst, SeMsgHead * header)
{
   header->tag = SE_MSG_FRAME_START;
   header->seq = 0;
   header->crc = utils_crc8t(header, sizeof(SeMsgHead) - 1);
   
   size_t size = header->size;
   uint8_t *ptr = (uint8_t *) header;
   
   // Compute the CRC.
   uint16_t crc = utils_crc16t(ptr, size, CRC_START_CCITT_1D0F);
   
   // Send frame start;
   slink_send_byte(inst, SE_MSG_FRAME_START); 
   ptr++; size--;
   
   // Send the message.
   for(; size; size--, ptr++)
   {
      slink_send_esc_byte(inst, *ptr);
   }
   
   // Send the crc.
   slink_send_esc_byte(inst, crc);
   slink_send_esc_byte(inst, crc >> 8);
}

void slink_send(SlinkInstance * inst, const void * msg, size_t size, size_t id, size_t endp)
{
   SeMsgHead header = {
      .tag = SE_MSG_FRAME_START,
      .seq = 0,
      .endp = (uint8_t)endp,
      .id = (uint16_t)id,
      .size = size + sizeof(SeMsgHead),
      .crc = 0,
   };

   uint8_t* ptr = (uint8_t*)&header;
   header.crc = utils_crc8t(ptr, sizeof(SeMsgHead) - 1);
     
   // Compute the CRC.
   uint16_t crc = utils_crc16t(ptr, sizeof(SeMsgHead), CRC_START_CCITT_1D0F);
   crc = utils_crc16t(msg, size, crc);

   // Send frame start;
   slink_send_byte(inst, SE_MSG_FRAME_START);
   size_t count = sizeof(SeMsgHead);
   ptr++; count--;

   // Send the header
   for (; count; count--, ptr++)
      slink_send_esc_byte(inst, *ptr);

   // Send the message
   ptr = (uint8_t *)msg;
   count = size;
   for (; count; count--, ptr++)
      slink_send_esc_byte(inst, *ptr);

   // Send the crc.
   slink_send_esc_byte(inst, (uint8_t)crc);
   slink_send_esc_byte(inst, (uint8_t)(crc >> 8));
}

// Sends only the header to the server.
uint16_t slink_begin_send_msg(SlinkInstance * inst, SeMsgHead * header, size_t size)
{
   header->tag = SE_MSG_FRAME_START;
   header->seq = 0;
   header->crc = utils_crc8t(header, sizeof(SeMsgHead) - 1);
   
   uint8_t *ptr = (uint8_t *) header;
   
   uint16_t crc = utils_crc16t(header, size, CRC_START_CCITT_1D0F);
   
   // Send frame start;
   slink_send_byte(inst, SE_MSG_FRAME_START); 
   ptr++; size--;
   
   // Send the message.
   for(; size; size--, ptr++)
   {
      slink_send_esc_byte(inst, *ptr);
   }
   
   return crc;
}

// Sends the content of a message to the server.
uint16_t slink_continue_data_msg(SlinkInstance * inst, const void * ptr, size_t size, uint16_t crc)
{
   const uint8_t * data = ptr;
   
   // Compute the CRC.
   uint16_t new_crc = utils_crc16t(data, size, crc);
   
   // Send the body.
   for(; size; size--, data++)
   {
      slink_send_esc_byte(inst, *data);
   }
   
   return new_crc;
}


// Sends the remaining crc byte to the server.
void slink_finalize_msg(SlinkInstance * inst, uint16_t crc)
{
   slink_send_esc_byte(inst, crc);
   slink_send_esc_byte(inst, crc >> 8);
}

bool slink_have_msg(SlinkInstance * inst)
{
   bool have = inst->rx_msg_count > 0;
   return have;
}

// Obtains oldest received message.
SeMsgHead* slink_receive(SlinkInstance * inst)
{
   return (SeMsgHead *)&inst->rx_buff[0];
}

void slink_discard(SlinkInstance * inst)
{
   if (!inst->rx_msg_count)
      return;
   
   SeMsgHead *hdr = (SeMsgHead *) &inst->rx_buff[0];
   size_t msg_size = hdr->size + SE_MSG_CRC_SIZE;
   
   inst->disable_int();
   
   if (inst->rx_count == msg_size)
   {
      inst->rx_msg_count = 0;
      inst->rx_count = 0;
      inst->in_msg_count = 0;
      inst->in_msg_start = 0;
   }
   else
   {
      memcpy(&inst->rx_buff[0], &inst->rx_buff[msg_size], inst->rx_count - msg_size);
      inst->rx_msg_count--;
      inst->rx_count -= msg_size;
      inst->in_msg_start -= msg_size;
   }
   
   if (inst->rx_count == 0)
      inst->rel_buffer(inst);
   
   inst->enable_int();
}

void slink_print_errors(SlinkInstance * inst)
{
   if (inst->errors & kSlinkErrorSkipJunk)
   {
      inst->errors -= kSlinkErrorSkipJunk;
      DBG(kLvlWarn, "slink, skipped junk data");
   }
   if (inst->errors & kSlinkErrorDiscardUnfinished)
   {
      inst->errors -= kSlinkErrorDiscardUnfinished;
      DBG(kLvlWarn, "slink, discarded unfinished msg");
   }
   if (inst->errors & kSlinkErrorHdrCrc)
   {
      inst->errors -= kSlinkErrorHdrCrc;
      DBG(kLvlWarn, "slink, header crc mismatch");
   }
   if (inst->errors & kSlinkErrorDataCrc)
   {
      inst->errors -= kSlinkErrorDataCrc;
      DBG(kLvlWarn, "slink, data crc mismatch");
   }
   if (inst->errors & kSlinkErrorDataCrc)
   {
      inst->errors -= kSlinkErrorBufferOverrun;
      DBG(kLvlWarn, "slink, buffer overrun %u", inst->rx_size);
   }
   if (inst->errors & kSlinkInfoRecvMsg)
   {
      inst->errors -= kSlinkInfoRecvMsg;
      // DBG(kLvlVerb, "slink, received msg");
   }
}

void slink_service(SlinkInstance * inst)
{
   if(inst->rx_activity)
   {
      inst->rx_activity = false;
      inst->last_byte_ts = timer_tick();
   }
   
   if (inst->rx_count && timer_tick() - inst->last_byte_ts >= TM_MLS_T0_TICK(100))
   {
      inst->disable_int();
      size_t count = inst->rx_count;
      inst->rx_count = 0;
      inst->in_msg_count = 0;
      inst->in_msg_start = 0;
      inst->rx_msg_count = 0;
      inst->rel_buffer(inst);
      inst->enable_int();
      DBG(kLvlWarn, "slink, rx timeout, discarding %u", count);
   }
   
   slink_print_errors(inst);
}