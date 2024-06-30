#include <xc.h>

#include "CAN.h"
#include "CANTypes.h"

UINT CANTotalModules(void)
{
	/* This function returns the total number
	 * of modules on the device. */
   
	return(CAN_NUMBER_OF_MODULES);
}

UINT CANTotalChannels(void)
{
	/* This function returns the total number
	 * of channels per CAN module. */

	return(CAN_ALL_CHANNELS);
}

UINT CANTotalFilters(void)
{
	/* This function returns the total number
	 * of filter available per CAN module. */

	return(CAN_NUMBER_OF_FILTERS);
}

UINT CANTotalMasks(void)
{
	/* This function returns the total number
	 * of filter masks available per CAN module. */

	return(CAN_NUMBER_OF_FILTER_MASKS);
}


