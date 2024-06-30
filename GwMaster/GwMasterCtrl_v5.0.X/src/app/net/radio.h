#ifndef RADIO_HANDLER
#define RADIO_HANDLER

#include "types.h"
#include "sas/lora.h"
#include "sas/rmsg_type.h"
#include "sas/rmsg_blob.h"

enum
{
   kRadioMsgNetwProg = kRadioMsgCustom,
   kRadioMsgTime,
};


void radio_init(const NetworkConfig * radio_data, const RadioConfig * radio_config, const HwRadioConfig * hwcfg);
void radio_start(void);
void radio_service(void);

void radio_config(size_t index);
bool radio_is_busy(void);
bool radio_send_simple(RaMsgHead * msg, const uint32_t size);
bool radio_send(const RmsgMessageContext * context);

void radio_get_buff(uint8_t ** const buff, size_t * const size);
uint8_t radio_get_new_blob_id();

const char * radio_event_str(const size_t event);

#endif