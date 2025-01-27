#include <xc.h>
#include "CANTypes.h"
#include "CAN.h"

#include <sys/kmem.h>

/***************************
 * CAN Receive
 * *************************/

CANRxMessageBuffer * CANGetRxMessage(CAN_MODULE module, CAN_CHANNEL channel)
{
	/* This function return a pointer to
	 * the next message to read. */

	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
	
	if(canRegisters->canFifoRegisters[channel].CxFIFOINTbits.RXNEMPTYIF == 0)
	{
		return(NULL);
	}
	else
	{
		return((CANRxMessageBuffer *)PA_TO_KVA1(canRegisters->canFifoRegisters[channel].CxFIFOUA));
	}
}

void CANUpdateChannel(CAN_MODULE module, CAN_CHANNEL channel)
{
	/* This function shoudl be called by the 
	 * application when it is done processing
	 * the last message that was read
	 */

	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];

	canRegisters->canFifoRegisters[channel].CxFIFOCONSET = CxFIFOCON_UINC_MASK;
}


void CANConfigureChannelForRx(CAN_MODULE module, CAN_CHANNEL channel, 
        UINT32 channelSize, CAN_RX_DATA_MODE dataOnly)
{
	/* This function will configure a channel for RX. */

	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
	canRegisters->canFifoRegisters[channel].CxFIFOCONCLR = CxFIFOCON_TXEN_MASK;
	canRegisters->canFifoRegisters[channel].CxFIFOCONbits.FSIZE = channelSize - 1;


	if(dataOnly == CAN_RX_DATA_ONLY)
	{
		canRegisters->canFifoRegisters[channel].CxFIFOCONSET = CxFIFOCON_DONLY_MASK;
	}

	else if(dataOnly == CAN_RX_FULL_RECEIVE)
	{
		canRegisters->canFifoRegisters[channel].CxFIFOCONCLR = CxFIFOCON_DONLY_MASK;
	}
   else
   {

   }
}

BOOL CANIsChannelOverflow(CAN_MODULE module, CAN_CHANNEL channel)
{
	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
   return canRegisters->canFifoRegisters[channel].CxFIFOINTbits.RXOVFLIF;
}

BOOL CANIsChannelFull(CAN_MODULE module, CAN_CHANNEL channel)
{
	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
   return canRegisters->canFifoRegisters[channel].CxFIFOINTbits.RXFULLIF;
}

BOOL CANIsChannelEmpty(CAN_MODULE module, CAN_CHANNEL channel)
{
	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
   return !canRegisters->canFifoRegisters[channel].CxFIFOINTbits.RXNEMPTYIF;
}

void CANClearChannelOverflow(CAN_MODULE module, CAN_CHANNEL channel)
{
	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];
	canRegisters->canFifoRegisters[channel].CxFIFOINTCLR = 0x08;
}
