#ifndef RMSG_TYPE
#define RMSG_TYPE

#include "lora.h"

enum
{
   kRadioMsgInvalid = 0,
   kRadioMsgAck,
   kRadioMsgNack,
   kRadioMsgUnsupported,
   kRadioMsgHello,
   kRadioMsgForward,
   kRadioMsgBlob,
   
   kRadioMsgCustom = 100,
};

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t acked_cmd;
} RaMsgAck;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t nacked_cmd;
   uint8_t reason;
} RaMsgNack;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t unsupported_cmd;
} RaMsgUnsupported;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t src;
   uint8_t dest;
   uint8_t ttl;
} RaMsgForward;


//////////////////////////////////////////////////////////////////////////////////


enum RadioBlob
{
   kRadioBlobInvalid = 0,
   kRadioBlobAck,
   kRadioBlobNack,
   kRadioBlobStart,
   kRadioBlobData,
   kRadioBlobSeqReq,
   kRadioBlobSeqRsp,
   kRadioBlobCancel,
   kRadioBlobDone,
   kRadioBlobLast,
};

enum
{
   kRadioBlobErrNone = 0,
   kRadioBlobErrBusy,
   kRadioBlobErrSize,
   kRadioBlobErrProto,
};

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
} RaMsgBlobCmd;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint8_t acked_cmd;
} RaMsgBlobAck;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint8_t nacked_cmd;
   uint8_t error;
} RaMsgBlobNack;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint32_t total_size;
   uint8_t segment_size;
   uint8_t burst_count;
} RaMsgBlobStart;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint32_t segment;
} RaMsgBlobData;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint32_t segment;
   uint32_t map;
} RaMsgBlobSeqRsp;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t blob_cmd;
   uint32_t crc;
} RaMsgBlobDone;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint8_t ttl;
} RaMsgNetworkProg;

typedef struct __attribute__ ((packed))
{
   RaMsgHead head;
   uint32_t time;
   uint32_t jitter;
} RaMsgTime;


#endif