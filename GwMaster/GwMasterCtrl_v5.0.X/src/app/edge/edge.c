#include "edge.h"
#include "edge_msg.h"
#include "lib/jparsing.h"
#include "app/net/serial.h"
#include "sal/debug.h"
#include "cfg/app_config.h"

#include <stdlib.h>


struct
{
   char local_buff[1024];
   JsonInst json_inst;
   JsonInst * json;
   const char * context_str;
} edge;


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
   size += json_add_uint32(&json[size], buff_size - size, "ctrl_id", id->ctrl_id);
   
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

static bool json_des_get_string(const char * key, const jsmntok_t * node, char * dest, size_t dest_size)
{
   const jsmntok_t * tok = json_parse_find_tag(edge.json, node, key);
   
   if (tok == NULL)
   {
      DBG(kLvlWarn, "edge, key '%s' is missing from '%s'", key, edge.context_str);
      return false;
   }
   
   if (!json_parse_get_string(edge.json, tok + 1, dest, dest_size))
   {
      DBG(kLvlWarn, "edge, key '%s' is not string, from '%s'", key, edge.context_str);
      return false;
   }
   
   return true;
}

static bool json_des_get_string_ref(const char * key, const jsmntok_t * node, const char ** dest, size_t* dest_size)
{
   const jsmntok_t * tok = json_parse_find_tag(edge.json, node, key);
   
   if (tok == NULL)
   {
      DBG(kLvlWarn, "edge, key '%s' is missing from '%s'", key, edge.context_str);
      return false;
   }
   
   if (!json_parse_get_string_ref(edge.json, tok + 1, dest, dest_size))
   {
      DBG(kLvlWarn, "edge, key '%s' is not string, from '%s'", key, edge.context_str);
      return false;
   }
   
   return true;
}

static bool json_des_get_uint32(const char * key, const jsmntok_t * node, uint32_t * dest)
{
   const jsmntok_t * tok = json_parse_find_tag(edge.json, node, key);
   
   if (tok == NULL)
      return false;
   
   if (!json_parse_get_uint32(edge.json, tok + 1, dest))
      return false;
   
   return true;
}

static const jsmntok_t * json_parse_local_till_data(const void * jsonstr, size_t jsonstr_size, const char * context_str)
{
   edge.json_inst = (JsonInst) {
      .tokens = (jsmntok_t *)edge.local_buff,
      .token_available = sizeof(edge.local_buff) / sizeof(jsmntok_t),
   };
   
   edge.json = &edge.json_inst;
   edge.context_str = context_str;
   
   if (!json_parse_tokens(edge.json, jsonstr, jsonstr_size))
   {
      DBG(kLvlError, "edge, failed to deserialize %s", context_str);
      return NULL;
   }
   
   const jsmntok_t * root = json_parse_find_tag(edge.json, NULL, "data");
   if (root == NULL)
   {
      DBG(kLvlError, "edge, failed to deserialize %s, root key 'data' is missing", context_str);
      return NULL;
   }
   
   return root;
}


///////////////////////////////////////////////     Ctrl     /////////////////////////////////////////////////////


bool edge_parse_ctrl_get(DataCtrlReq * data, const void * jsonstr, size_t jsonstr_size)
{
   *data = (DataCtrlReq){0};
   
   const jsmntok_t * root = json_parse_local_till_data(jsonstr, jsonstr_size, "ctrl get");
   if (root == NULL)
      return false;
   
   if (!json_des_get_string_ref("what", root, &data->what, NULL))
      return false;
   
   return true;
}

bool edge_parse_ctrl_set_config(DataCtrlConfig * data, const void * jsonstr, size_t jsonstr_size)
{
   *data = (DataCtrlConfig){0};
   
   const jsmntok_t * root = json_parse_local_till_data(jsonstr, jsonstr_size, "ctrl set config");
   if (root == NULL)
      return false;

   if (!json_des_get_uint32("ctrl_id", root, &data->ctrl_id))
      return false;
   
   return true;
}

bool edge_parse_ctrl_set_title(DataCtrlTitle * data, const void * jsonstr, size_t jsonstr_size)
{
   *data = (DataCtrlTitle){0};
   
   const jsmntok_t * root = json_parse_local_till_data(jsonstr, jsonstr_size, "ctrl set title");
   if (root == NULL)
      return false;
   
   if (!json_des_get_string("name", root, data->name, sizeof(data->name)))
      return false;
   
   if (!json_des_get_string("description", root, data->description, sizeof(data->description)))
      return false;
   
   return true;
}


///////////////////////////////////////////////     Monitor     /////////////////////////////////////////////////////


bool edge_parse_mon_sms(DataMonSms * msg, const void * jsonstr, size_t jsonstr_size)
{
   *msg = (DataMonSms) {0};
   
   const jsmntok_t * root = json_parse_local_till_data(jsonstr, jsonstr_size, "mon sms");
   if (root == NULL)
      return false;
   
   if (!json_des_get_string_ref("nr", root, &msg->nr, NULL))
      return false;
    
   if (!json_des_get_string_ref("text", root, &msg->text, NULL))
      return false;
   
   return true;
}

///////////////////////////////////////////////     Send     /////////////////////////////////////////////////////


void edge_send_sms(const char * nr, const char * text)
{
   char * json = edge.local_buff;
   size_t buff_size = sizeof(edge.local_buff);
   
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

void edge_send_ctrl_status(void)
{
   char * json = edge.local_buff;
   size_t buff_size = sizeof(edge.local_buff);
 
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, NULL);
   size += json_ser_meta(&json[size], buff_size - size, "ok");
   size += json_next_object(&json[size], buff_size - size);
   size += json_begin_object(&json[size], buff_size - size, "data");
   
   size_t msg_id = kMsgSlinkCtrlStatus;
   
   DataCtrlId id = {
      .fwv = 100,
      .hwv = 100,
      .ctrl_id = app_config.ctrl.config.ctrl_id,
   };
      
   if (app_config.ctrl.config.ctrl_id != 0)
   {

      DataCtrlStatus status = {
         .state = state_global()->sem->str_global,
         .error = state_global()->sem->str_error,
      };
      
      size += json_ser_ctrl_id(&id, &json[size], buff_size - size, "id");
      size += json_next_object(&json[size], buff_size - size);
      size += json_ser_ctrl_title(&app_config.ctrl.title, &json[size], buff_size - size, "title");
      size += json_next_object(&json[size], buff_size - size);
      size += json_ser_ctrl_status(&status, &json[size], buff_size - size, "status");

      msg_id = kMsgSlinkCtrlStatus;
   }
   else
   {
      // Not configured
      
      size += json_ser_ctrl_id(&id, &json[size], buff_size - size, "id");
      msg_id = kMsgSlinkCtrlNoConfig;
   }

   size += json_end_object(&json[size], buff_size - size);   // Data
   size += json_end_object(&json[size], buff_size - size);   // root
   
   edge_send_to_server(msg_id, json, size);
}

