
#include "mqtt.h"

#include "lib/shared_buff.h"
#include "lib/utils.h"
#include "lib/jparsing.h"

#include "sal/debug.h"
#include "cfg/app_config.h"

#include "app/logic/logic.h"

enum
{
   kMqttSubCmd = 0,
   kMqttSubMax,
};

enum
{
   kMqttPubConnected = 0,
   kMqttPubGlobalState,
   kMqttPubMax,
};


typedef struct
{
   char topic[32];
   void (* on_data)(const MessageData * data);
} MqttTopicSubs;


static void mqtt_sub_ctrl_cmd(const MessageData * data);

static MqttTopicSubs mqtt_subs[] = 
{
   {"/ctrl/cmd", mqtt_sub_ctrl_cmd},
};

static const char * mqtt_pubs[] = 
{
   "tc%02u%02u/state/connected",
   "tc%02u%02u/state/global",
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////


static struct
{
   const MqttConfig * config;
   MqttNetwork network;
   MQTTClient client;
   char client_id[16];
   bool connected;
} mqtt;


//////////////////////////////////////////////////   Utils   //////////////////////////////////////////////////


static void mqtt_drop(void)
{
   mqtt.network.mqttdisconnect(&mqtt.network);
}

static void publish(size_t id, const void * data, size_t size)
{
   if(!mqtt.connected)
      return;
   
   if(id >= kMqttPubMax)
   {
      DBG(kLvlError, "cell, MQTT publish invalid id %u", id);
      return;
   }
   
   MQTTMessage message = {
      .qos = 2,
      .retained = 1,
      .payload = data,
      .payloadlen = size,
   };
   
   char topic[64];
   snprintf(topic, sizeof(topic), mqtt_pubs[id], (uint32_t) app_config.net.addr_network, (uint32_t) app_config.net.addr_local);
   
   int ret = MQTTPublish(&mqtt.client, topic, &message);
   if(ret != MQTT_SUCCESS)
   {
      DBG(kLvlWarn, "cell, MQTT publish failed %d", ret);
      mqtt_drop();
   }
}


static size_t str_add_boards(char * buff, size_t buff_size, uint32_t map)
{
   size_t size = 0;
   
   uint32_t mask = 1;
   for(size_t i = 0; map; i++, mask <<= 1)
   {
      if(mask & map)
      {
         size += snprintf(&buff[size], buff_size - size, "P%u\n", i + 1);
         map -= mask;
      }
   }
   
   return size;
}

static size_t str_add_bulbs(char * buff, size_t buff_size, const uint32_t * critical, const uint32_t * non_critical, size_t count)
{
   size_t size = 0;
   size_t items_count = 0;
   
   const SignalNetwork * netw = logic_slink_get_prog();
   const SignalController * ctrl = (const SignalController *) (netw + 1);
   
   for(size_t i = 0; i < count && items_count < 10; i++)
   {
      uint32_t map = critical[i];

      if(map == 0)
         continue;

      uint32_t mask = 1;

      for(size_t j = 0; map && items_count < 10; j++, mask <<= 1)
      {
         if(map & mask)
         {
            map -= mask;
            items_count++;

            const SignalBulbDesc * desc = sem_get_bulb_desc(ctrl, i, j);
            if(desc != NULL)
            {
               uint8_t str[sizeof(desc->name) + 1] = {0};
               strncpy(str, desc->name, sizeof(desc->name));
               size += snprintf(&buff[size], buff_size - size, "%s\n", str);
            }
            else
            {
               size += snprintf(&buff[size], buff_size - size, "P%u:%u\n", i + 1, j + 1);
            }
         }
      }
   }

   for(size_t i = 0; i < count && items_count < 10; i++)
   {
      uint32_t map = non_critical[i];

      if(map == 0)
         continue;

      uint32_t mask = 1;

      for(size_t j = 0; map && items_count < 10; j++, mask <<= 1)
      {
         if(map & mask)
         {
            map -= mask;
            items_count++;

            const SignalBulbDesc * desc = sem_get_bulb_desc(ctrl, i, j);         
            if(desc != NULL)
            {
               uint8_t str[sizeof(desc->name) + 1] = {0};
               strncpy(str, desc->name, sizeof(desc->name));
               size += snprintf(&buff[size], buff_size - size, "%s\n", str);
            }
            else
            {
               size += snprintf(&buff[size], buff_size - size, "P%u:%u\n", i + 1, j + 1);
            }
         }
      }
   }
   
   return size;
}

static void mqtt_status_update(void)
{
   if(!mqtt.connected)
      return;
   
   const GlobalState * global = state_global();
   
   char * json = shared_buff_get_chunk();
   size_t buff_size = shared_buff_chunk_size();
   
   if(json == NULL)
   {
      DBG(kLvlError, "mqtt, cannot get shared buffer");
      return;
   }
   
   size_t size = 0;
   
   size += json_begin_object(&json[size], buff_size - size, NULL);
   size += json_add_string(&json[size], buff_size - size, "state", global->sem->str_global);
   size += json_add_string(&json[size], buff_size - size, "error", global->sem->str_error);
   size += json_add_string(&json[size], buff_size - size, "network", global->sem->str_net);
   size += json_add_string(&json[size], buff_size - size, "name", global->sem->str_ctrl);
   size += json_add_string(&json[size], buff_size - size, "schedule", global->sem->str_sch);
   size += json_add_bool(&json[size], buff_size - size, "gps_lock", global->gps_lock);
   size += json_end_object(&json[size], buff_size - size);
   
   publish(kMqttPubGlobalState, json, size);
   
   shared_buff_release_chunk(json);
}


//////////////////////////////////////////////////   Handlers   //////////////////////////////////////////////////


static void mqtt_sub_ctrl_cmd(const MessageData * data)
{
   DBG(kLvlVerb, "cell, MQTT recv cmd: %.*s", data->message->payloadlen, data->message->payload);
   
   char buff[256];
   snprintf(buff, sizeof(buff), "%.*s", data->message->payloadlen, data->message->payload);
   
   char cmd[16];
   utils_strncpy_word(cmd, buff, sizeof(cmd) - 1);
   
   if(strcmp(cmd, "suspend") == 0)
   {
      sem_operation_suspend();
   }
   else if(strcmp(cmd, "resume") == 0)
   {
      sem_operation_resume();
   }
}


//////////////////////////////////////////////////   Public    ///////////////////////////////////////////////////

bool mqtt_enabled(void)
{
   return mqtt.config->enabled;
}

bool mqtt_connect(void)
{
   if (!mqtt.config->enabled)
      return false;
   
   mqtt.connected = false;
   
   if(MQTT_SUCCESS != mqtt.network.mqttconnect(&mqtt.network, mqtt.config->host, mqtt.config->port))
   {
      DBG(kLvlWarn, "mqtt, connection failed");
      return false;
   }

   /*if(MQTTIsConnected(&mqtt.client))
   {
      DBG(kLvlWarn, "mqtt, already connected");
      mqtt.connected = true;
      return true;
   }*/
   
   MQTTClientInit(
      &mqtt.client, 
      &mqtt.network, 
      30000,
      mqtt.config->send_buff,
      mqtt.config->send_buff_size, 
      mqtt.config->recv_buff,
      mqtt.config->recv_buff_size);

   
   MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;   
   connectData.clientID = (MQTTString) {
      .cstring = mqtt.client_id,
   };
   
   char connect_topic[64];
   snprintf(connect_topic, sizeof(connect_topic), mqtt_pubs[kMqttPubConnected], (uint32_t) app_config.net.addr_network, (uint32_t) app_config.net.addr_local);
   
   connectData.will.topicName.cstring = connect_topic;
   connectData.will.message.lenstring.data = "0";
   connectData.will.message.lenstring.len = 1;
   connectData.will.retained = 1,
   connectData.willFlag = true;

   int ret = MQTTConnect(&mqtt.client, &connectData);
   if(ret != MQTT_SUCCESS)
   {
      DBG(kLvlWarn, "cell, MQTT connect failed %d", ret);
      return false;
   }
   
   mqtt.connected = true;
   
   DBG(kLvlInfo, "cell, MQTT connected");
   
   publish(kMqttPubConnected, "1", 1);
   
   for(size_t i = 0; i < COUNT(mqtt_subs); i++)
   {
      ret = MQTTSubscribe(&mqtt.client, mqtt_subs[i].topic, 2, mqtt_subs[i].on_data);
      if(ret != MQTT_SUCCESS)
      {
         DBG(kLvlError, "cell, MQTT subscription failed for %s", mqtt_subs[i].topic);
         mqtt_drop();
         return false;
      }

      DBG(kLvlVerb, "cell, MQTT sub %s", mqtt_subs[i].topic);
   }
;
    
   return true;
}

void mqtt_disconnect(void)
{
   if(mqtt.connected)
   {
      MQTTCloseSession(&mqtt.client);
      mqtt.connected = false;
      DBG(kLvlInfo, "mqtt, disconnected");
   }
}


void mqtt_keep_alive(void)
{
   if(!mqtt.connected)
      return;
   
   if(MQTTIsConnected(&mqtt.client))
   {
      if(MQTT_SUCCESS == MQTTKeepAlive(&mqtt.client))
         return;
   }
   
   DBG(kLvlWarn, "mqtt, keep alive failed");
   
   mqtt_drop();
}


void mqtt_on_data_recv(void)
{
   if(!mqtt.connected)
      return;
   
   if(MQTT_SUCCESS != MQTTYield(&mqtt.client, 100))
   {
      DBG(kLvlWarn, "cell, MQTT Yield failed");
      mqtt_drop();
   }
}


//////////////////////////////////////////////////   Events    ///////////////////////////////////////////////////


void mqtt_status_changed(void)
{
   mqtt_status_update();
}


//////////////////////////////////////////////////   Events    ///////////////////////////////////////////////////


void mqtt_init(const MqttConfig * config, MqttNetwork * network)
{
   mqtt.config = config;
   mqtt.network = *network;
}

void mqtt_start(void)
{
   snprintf(mqtt.client_id, sizeof(mqtt.client_id), "tc%02u%02u", (uint32_t) app_config.net.addr_network, (uint32_t) app_config.net.addr_local);
   
   for(size_t i = 0; i < COUNT(mqtt_subs); i++)
   {
      utils_str_prefix(mqtt_subs[i].topic, sizeof(mqtt_subs[i].topic), mqtt.client_id);
   }
}

void mqtt_service(void)
{
   
}
