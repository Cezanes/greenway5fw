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

#define COUNT(a)              (sizeof(a)/sizeof(a[0]))
#define FIELD_SIZE(t, field)  (sizeof((t *)0)-> field)

enum 
{
   kOK = 0,
   kErrorGeneric,
   kErrorParam,
   kErrorTimeout,
   kErrorNotSupported,
   kErrorNotInitialized,
   kErrorNotResponding,
   kErrorNoSpace,
   kErrorNoData,
   kErrorConnection,
   kErrorNotFound,
   kErrorSize,
   kErrorCrc,
   kErrorFlash,
   kErrorData,
   kErrorId,
   kErrorConfig,
   kErrorBusy,
   kErrorProtocol,
   kErrorRead,
   kErrorWrite,
   kErrorRadio,
   kErrorSim,
   kErrorBus,
};

#endif	