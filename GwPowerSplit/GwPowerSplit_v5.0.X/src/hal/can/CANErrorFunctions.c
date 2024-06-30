#include <xc.h>
#include "CAN.h"
#include "CANTypes.h"


UINT CANGetRxErrorCount(CAN_MODULE module)

{

	/* This function returns TX Error Counter. */



	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];



	return((canRegisters->CxTREC) & (UINT32)0xFF);



}



UINT CANGetTxErrorCount(CAN_MODULE module)

{

	/* This function returns TX Error Counter. */



	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];



	return((canRegisters->CxTREC >> 8) & (UINT32)0xFF);

}



CAN_ERROR_STATE CANGetErrorState(CAN_MODULE module)

{

	/* This function returns error states. The returned

	 * value can be masked to check for specific error 

	 * state. */



	CAN_REGISTERS * canRegisters = (CAN_REGISTERS *)canModules[module];



	return((canRegisters->CxTREC) & (UINT32)0xFFFF0000);

}
