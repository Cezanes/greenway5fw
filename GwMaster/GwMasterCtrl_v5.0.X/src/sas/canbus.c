#include "types.h"
#include "sal/debug.h"
#include "sal/timer.h"

#include "canbus.h"
#include "hal/can/CAN.h"

#include <sys/kmem.h>


#define enable_isr()   IEC2SET = 1 << _IEC2_CAN1IE_POSITION;
#define disable_isr()  IEC2CLR = 1 << _IEC2_CAN1IE_POSITION;

typedef struct
{
   const CanBusConfig * config;
   uint32_t fifo[2 * 32 * 4];
   
   size_t recv_msg_count;
   size_t send_msg_count;
   
} CanInternal;


///////////////////////////////////////////////////////////////////////////////////////////////////////


static CAN_REGISTERS * candev = (CAN_REGISTERS *)CAN1_BASE_ADDRESS;
static CanInternal can;


///////////////////////////////////////////////////////////////////////////////////////////////////////


bool can_change_mode(CAN_MODULE module, CAN_OP_MODE opmode)
{
   CANSetOperatingMode(module, opmode);
   
   uint32_t timeout = can.config->mode_timeout;
   while(CANGetOperatingMode(module) != opmode)
   {
      timer_delay_ms(1);
      
      if(timeout > 0)
         timeout--;
      
      if (timeout == 0)
      {
         DBG(kLvlError, "can, could not change mode from %u to %u", CANGetOperatingMode(module), opmode);
         return false;
      }
   }
   
   return true;
}

static bool peripheral_init(void)
{   
   CANEnableModule(CAN1, TRUE);
   
   if(!can_change_mode(CAN1, CAN_CONFIGURATION))
   {
      return false;
   }
   
   CAN_BIT_CONFIG can_config;
   can_config.phaseSeg1Tq          = can.config->clock.phaseSeg1Tq; // 3
   can_config.phaseSeg2Tq          = can.config->clock.phaseSeg2Tq; // 3
   can_config.propagationSegTq     = can.config->clock.propagationSegTq; // 3
   can_config.phaseSeg2TimeSelect  = can.config->clock.phaseSeg2TimeSelect; // true
   can_config.sample3Time          = can.config->clock.sample3Time; // true
   can_config.syncJumpWidth        = can.config->clock.syncJumpWidth; // true 
   
   CANSetSpeed(CAN1, &can_config, can.config->clock.sys_clock, can.config->clock.can_baud);
   
   CANAssignMemoryBuffer(CAN1, can.fifo, sizeof(can.fifo));
   
   CANConfigureChannelForTx(CAN1, CAN_CHANNEL0, 32, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
   CANConfigureChannelForRx(CAN1, CAN_CHANNEL1, 32, CAN_RX_FULL_RECEIVE);

   CANConfigureFilter      (CAN1, CAN_FILTER0, 0, CAN_EID);
   CANConfigureFilterMask  (CAN1, CAN_FILTER_MASK0, 0, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);
   CANLinkFilterToChannel  (CAN1, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
   CANEnableFilter         (CAN1, CAN_FILTER0, TRUE);

   CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
   CANEnableModuleEvent (CAN1, CAN_RX_EVENT, TRUE);
   
   IPC11SET = 1 << _IPC11_CAN1IP_POSITION;
   IPC11CLR = 1 << _IPC11_CAN1IS_POSITION;
   IFS2CLR = 1 << _IFS2_CAN1IF_POSITION;
   
   candev->canFifoRegisters[CAN_CHANNEL0].CxFIFOINTbits.RXFULLIF = 0;
   candev->canFifoRegisters[CAN_CHANNEL1].CxFIFOINTbits.RXFULLIF = 0;
   
   if(!can_change_mode(CAN1, CAN_NORMAL_OPERATION))
   {
      return false;
   }
   
   if (can.config->use_rx_interrupt && can.config->on_recv_msg)
   {
      enable_isr();
   }
   
   return true;
} 

void __ISR(_CAN_1_VECTOR, IPL1AUTO) CAN1_ISR(void)
{
   if((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0)
   {   
       if(CANGetPendingEventCode(CAN1) == CAN_CHANNEL1_EVENT)
       {   
         if(can.config->on_recv_msg)
         {
            CANRxMessageBuffer * message = (CANRxMessageBuffer *)CANGetRxMessage(CAN1, CAN_CHANNEL1);

            if(message != NULL)
            {
               CanMsg msg = {
                  .id = message->msgSID.SID | (message->msgEID.EID << 11),
                  .size = message->msgEID.DLC,
               };
               
               msg.data[0] = message->messageWord[2];
               msg.data[1] = message->messageWord[3];

               can.config->on_recv_msg(&msg);
            }
         }
         
         CANUpdateChannel(CAN1, CAN_CHANNEL1);
       }   
   }   

   IFS2CLR = 1 << _IFS2_CAN1IF_POSITION;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void can_init(const CanBusConfig * config)
{
   can.config = config;
   
   if(!peripheral_init())
   {
      DBG(kLvlError, "can, could not initialize CAN module");
      return;
   }
}

bool can_send_msg(const CanMsg * msg)
{
   CANTxMessageBuffer * message = CANGetTxMessageBuffer(CAN1, CAN_CHANNEL0);

   if(message == 0)
   {
      //DBG(kLvlError, "can, transmit FIFO is full");
      return false;
   }
   
   message->messageWord[0] = 0;
   message->messageWord[1] = 0;
   message->messageWord[2] = 0;
   message->messageWord[3] = 0;
   
   message->msgSID.SID = msg->id;
   message->msgEID.EID = msg->id >> 11;
   message->msgEID.DLC = msg->size;
   
   message->msgEID.IDE = 1;
      
   message->messageWord[2] = msg->data[0];
   message->messageWord[3] = msg->data[1];
   
   CANUpdateChannel(CAN1, CAN_CHANNEL0);
   CANFlushTxChannel(CAN1, CAN_CHANNEL0);
   
   return true;
}

bool can_send(uint32_t id, const void * data, size_t size)
{
   if(size > 8)
   {
      //DBG(kLvlInfo, "can, invalid TX message size %u", size);
      return false;
   }
   
   CanMsg msg = {
      .id = id,
      .size = size,
   };
   
   memcpy(msg.data, data, size);
   
   return can_send_msg(&msg);
}

bool can_recv(CanMsg * msg)
{
   CANRxMessageBuffer * message = (CANRxMessageBuffer *)CANGetRxMessage(CAN1, CAN_CHANNEL1);   
   
   if(message == NULL)
   {
      return false;
   }
   
   *msg = (CanMsg) {
      .id = message->msgSID.SID | (message->msgEID.EID << 11),
      .size = message->msgEID.DLC,
   };

   msg->data[0] = message->messageWord[2];
   msg->data[1] = message->messageWord[3];
   
   CANUpdateChannel(CAN1, CAN_CHANNEL1);
   
   return true;
}

bool can_recv_full(void)
{
   return CANIsChannelFull(CAN1, CAN_CHANNEL1);
}

bool can_recv_empty(void)
{
   return CANIsChannelEmpty(CAN1, CAN_CHANNEL1);
}

bool can_recv_overflow(void)
{
   if(CANIsChannelOverflow(CAN1, CAN_CHANNEL1))
   {
      CANClearChannelOverflow(CAN1, CAN_CHANNEL1);
      return true;
   }
   
   return false;
}

bool can_send_full(void)
{
   return CANIsChannelFull(CAN1, CAN_CHANNEL0);
}

bool can_send_empty(void)
{
   return CANIsChannelEmpty(CAN1, CAN_CHANNEL0);
}

void can_service(void)
{
   if(!can.config->use_rx_interrupt && can.config->on_recv_msg)
   {
      CanMsg msg;
      if(can_recv(&msg))
      {
         can.config->on_recv_msg(&msg);
      }
   }
}