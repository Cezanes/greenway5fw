#ifndef SMSG_HANDLER
#define SMSG_HANDLER

#include "types.h"

#include "sas/server.h"
#include "sas/lora.h"

enum
{
   kSlinkItfAll  = 0 << 0,
   kSlinkItfPc   = 1 << 0,
   kSlinkItfEdge = 1 << 1,
   kSlinkItfCell = 1 << 2,
};

enum
{
   kSlinkEpServer = 0,
   kSlinkEpMonitor = 1,
};


enum CustomMsgType
{
   kMsgSlinkInfo           = 0x0100,
   kMsgSlinkGetSemProg,
   kMsgSlinkSetSemProg,
   kMsgSlinkGetConfig,
   kMsgSlinkSetConfig,
   kMsgSlinkGetTime,
   kMsgSlinkSetTime,
   kMsgSlinkGetNetProg,
   kMsgSlinkSetNetProg,
   
   kMsgSlinkSetSms         = 0x0201,
};


enum MsgIdCtrl
{
   kMsgSlinkCtrlInvalid        = 0x0000,
   kMsgSlinkCtrlCfg            = 0x0100,
      kMsgSlinkCtrlGet         = kMsgSlinkCtrlCfg + 0x04,
      kMsgSlinkCtrlNoConfig    = kMsgSlinkCtrlCfg + 0x08,
      kMsgSlinkCtrlSetConfig   = kMsgSlinkCtrlCfg + 0x0C,
      kMsgSlinkCtrlStatus      = kMsgSlinkCtrlCfg + 0x10,
      kMsgSlinkCtrlSetState    = kMsgSlinkCtrlCfg + 0x14,

};

enum MsgIdMonitor
{
   kMsgSlinkMonCfg           = 0x0100,
      kMsgSlinkMonGet        = kMsgSlinkMonCfg + 0x04,

   kMsgSlinkMonCmd           = 0x0200,
      kMsgSlinkMonSms    = kMsgSlinkMonCmd + 0x04,
};


typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint8_t description[24];
   uint16_t device_type;
   uint32_t serial;
   uint32_t fw_version;
   uint32_t rx_buff_size;
} SeMsgInfo;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint8_t addr_network;
   uint8_t addr_local;
   RadioConfig radio;
} SeMsgConfig;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint8_t remote;
} SeMsgProg;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint32_t time;
} SeMsgTime;

typedef struct __attribute__ ((packed))
{
   SeMsgHead head;
   uint8_t phone_nr[16];
} SeMsgSetSms;

void serial_init(const ServerConfig * config);
void serial_start(void);
void serial_service(void);

void serial_send_msg_old(size_t itf, SeMsgHead * msg);
void serial_send_msg(size_t itf, const void * msg, size_t size, size_t id, size_t ep);
void serial_send_sms_msg(size_t itf, const char * no, const char * text, size_t len);

#endif