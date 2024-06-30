/*
 * File:   types.h
 * Author: cezane
 *
 * Data types used in this whole project.
 */

#ifndef DATATYPES_H
#define	DATATYPES_H

#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define COUNT(a)       (sizeof(a)/sizeof(a[0]))


enum 
{
   kOK = 0,
   kErrorGeneric,
   kErroroTimeout,
   kErrorNotSupported,
   kErrorNotInitialized,
   kErrorNotResponding,
   kErrorNoSpace,
   kErrorNoData,
   kErrorSize,
   kErrorCrc,
   kErrorFlash,
   kErrorId,
   kErrorConfig,
   kErrorBusy,
   kErrorProtocol,
   kErrorRead,
   kErrorWrite,
   kErrorRadio,
   kErrorSimError,
};

#endif	