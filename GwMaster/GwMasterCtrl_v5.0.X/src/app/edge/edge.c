#include "edge.h"
#include "edge_msg.h"
#include "lib/jparsing.h"
#include "app/net/serial.h"
#include "sal/debug.h"

#include <stdlib.h>


char buffz[1024];

static size_t json_ser_meta(char *json, size_t buff_size, const char * status)
{
   size_t size = 0;
   size += json_begin_object(&json[size], buff_size - size, "meta");
   size += json_add_string(&json[size], buff_size - size, "status", status);
   size += json_end_object(&json[size], buff_size - size);
   return size;
}

static size_t json_ser_ctrl_id(const DataCtrlId* id, char *json, size_t buff_size, const char * tag)
{
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, tag);
   
   size += json_add_int32(&json[size], buff_size - size, "fwv", id->fwv);
   size += json_add_int32(&json[size], buff_size - size, "hwv", id->hwv);
   size += json_add_string(&json[size], buff_size - size, "devid", id->devid);
   
   size += json_end_object(&json[size], buff_size - size);
   
   return size;
}

static size_t json_ser_ctrl_title(const DataCtrlTitle* title, char *json, size_t buff_size, const char * tag)
{
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, tag);
   
   size += json_add_string(&json[size], buff_size - size, "name", title->name);
   size += json_add_string(&json[size], buff_size - size, "description", title->description);
   
   size += json_end_object(&json[size], buff_size - size);
   
   return size;
}

static size_t json_ser_ctrl_status(const DataCtrlStatus* status, char *json, size_t buff_size, const char * tag)
{
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, tag);
   
   size += json_add_string(&json[size], buff_size - size, "state", status->state);
   size += json_add_string(&json[size], buff_size - size, "error", status->error);
   size += json_add_uint32(&json[size], buff_size - size, "program_active_id", status->program_active_id);
   size += json_add_uint32(&json[size], buff_size - size, "schedule_active_id", status->schedule_active_id);
   size += json_add_uint32(&json[size], buff_size - size, "pinout_active_id", status->pinout_active_id);
   
   size += json_end_object(&json[size], buff_size - size);
   
   return size;
}

static size_t json_ser_ctrl_info(const DataCtrlInfo* info, char *json, size_t buff_size, const char * tag)
{
   size_t size = 0;

   size += json_begin_object(&json[size], buff_size - size, tag);
   
   size += json_ser_ctrl_id(&info->id, &json[size], buff_size - size, "id");
   size += json_next_object(&json[size], buff_size - size);
   size += json_ser_ctrl_title(&info->title, &json[size], buff_size - size, "title");
   size += json_next_object(&json[size], buff_size - size);
   size += json_ser_ctrl_status(&info->status, &json[size], buff_size - size, "status");
   
   size += json_end_object(&json[size], buff_size - size);
   
   return size;
}

static size_t json_ser_mon_sms(const DataMonSms * sms, char *json, size_t buff_size, const char * tag)
{
   size_t size = 0;

   size += json_begin_object(&json[size], buff_size - size, tag);
   
   size += json_add_string(&json[size], buff_size - size, "nr", sms->nr);
   size += json_add_string(&json[size], buff_size - size, "text", sms->text);
   
   size += json_end_object(&json[size], buff_size - size);
   
   return size;
}

static bool json_des_get_string(const JsonInst * json, const char * key, const jsmntok_t * node, char * dest, size_t dest_size)
{
   const jsmntok_t * tok = json_parse_find_tag(json, node, key);
   
   if (tok == NULL)
      return false;
   
   if (!json_parse_get_string(json, tok + 1, dest, dest_size))
      return false;
   
   return true;
}

static bool json_des_get_string_ref(const JsonInst * json, const char * key, const jsmntok_t * node, const char ** dest, size_t* dest_size)
{
   const jsmntok_t * tok = json_parse_find_tag(json, node, key);
   
   if (tok == NULL)
      return false;
   
   if (!json_parse_get_string_ref(json, tok + 1, dest, dest_size))
      return false;
   
   return true;
}


bool edge_parse_ctrl_get(DataCtrlReq * req, const void * data, size_t data_size)
{
   *req = (DataCtrlReq){0};
   
   JsonInst json = {
      .tokens = (jsmntok_t *)buffz,
      .token_available = sizeof(buffz) / sizeof(jsmntok_t),
   };
   
   if (!json_parse_tokens(&json, data, data_size))
   {
      DBG(kLvlError, "edge, failed to deserialize ctrl req");
      return false;
   }
   
   const jsmntok_t * root = json_parse_find_tag(&json, NULL, "data");
   if (root == NULL)
   {
      DBG(kLvlError, "edge, failed to deserialize ctrl req, root key 'data' is missing");
      return false;
   }

   if (!json_des_get_string(&json, "what", root, req->what, sizeof(req->what)))
   {
      DBG(kLvlError, "edge, failed to deserialize ctrl req, key 'what' is missing");
      return false;
   }
   
   return true;
}

bool edge_parse_mon_sms(DataMonSms * msg, const void * data, size_t data_size)
{
   *msg = (DataMonSms) {0};
   
   JsonInst json = {
      .tokens = (jsmntok_t *)buffz,
      .token_available = sizeof(buffz) / sizeof(jsmntok_t),
   };
   
   if (!json_parse_tokens(&json, data, data_size))
   {
      DBG(kLvlError, "edge, failed to deserialize mon sms");
      return false;
   }
   
   const jsmntok_t * root = json_parse_find_tag(&json, NULL, "data");
   if (root == NULL)
   {
      DBG(kLvlError, "edge, failed to deserialize mon sms, root key 'data' is missing");
      return false;
   }
   
   if (!json_des_get_string_ref(&json, "nr", root, &msg->nr, NULL))
   {
      DBG(kLvlError, "edge, failed to deserialize mon sms, key 'nr' is missing");
      return false;
   }
    
   if (!json_des_get_string_ref(&json, "text", root, &msg->text, NULL))
   {
      DBG(kLvlError, "edge, failed to deserialize mon sms, key 'text' is missing");
      return false;
   }
   
   return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void edge_send_sms(const char * nr, const char * text)
{
   char * json = buffz;
   size_t buff_size = sizeof(buffz);
   
   const DataMonSms msg = {
      .nr = nr,
      .text = text,
   };
   
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, NULL);
   size += json_ser_meta(&json[size], buff_size - size, "ok");
   size += json_next_object(&json[size], buff_size - size);
   size += json_ser_mon_sms(&msg, &json[size], buff_size - size, "data");      // here
   size += json_end_object(&json[size], buff_size - size);
   
   edge_send_to_monitor(kMsgSlinkMonSms, json, size);
}

void edge_send_to_server(size_t id, const void *msg, size_t size)
{
   DBG(kLvlVerb, "edge, sending msg %04X, size %u:\r\n %s", id, size, msg);
   serial_send_msg(kSlinkItfEdge, msg, size, id, kSlinkEpServer);
}

void edge_send_to_monitor(size_t id, const void *msg, size_t size)
{
   DBG(kLvlVerb, "edge, sending msg %04X, size %u:\r\n %s", id, size, msg);
   serial_send_msg(kSlinkItfEdge, msg, size, id, kSlinkEpMonitor);
}

void edge_send_status(void)
{
   char * json = buffz;
   size_t buff_size = sizeof(buffz);
   
   DataCtrlInfo info = {
      .id = {
         .fwv = 100,
         .hwv = 100,
         .devid = "rp5user",
      },
      .title = {
         .name = "Podu Ioaiei",
         .description = "Intersectia cu Farmacia",
      },
      .status = {
         .state = "normal",
         .error = "none",
      },
   };
   
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, NULL);
   size += json_ser_meta(&json[size], buff_size - size, "ok");
   size += json_next_object(&json[size], buff_size - size);
   size += json_ser_ctrl_info(&info, &json[size], buff_size - size, "data");    // here
   size += json_end_object(&json[size], buff_size - size);
   
   edge_send_to_server(kMsgSlinkCtrlStatus, json, size);
}

