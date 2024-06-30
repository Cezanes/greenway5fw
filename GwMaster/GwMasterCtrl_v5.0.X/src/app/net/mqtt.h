#ifndef MQTT_H
#define MQTT_H

#include "types.h"

#include "sas/mqtt/MQTTClient.h"


typedef struct
{
   bool enabled;
   const char * host;
   size_t port;
   uint8_t * send_buff;
   size_t send_buff_size;
   uint8_t * recv_buff;
   size_t recv_buff_size;
} MqttConfig;


void mqtt_init(const MqttConfig * config, MqttNetwork * network);
void mqtt_start(void);
bool mqtt_enabled(void);
bool mqtt_connect(void);
void mqtt_disconnect(void);
void mqtt_on_data_recv(void);
void mqtt_keep_alive(void);


void mqtt_status_changed(void);


void mqtt_report_board_disconnected(const char * details);
void mqtt_report_board_failed(const char * details);
void mqtt_report_board_unpowered(const char * details);
void mqtt_report_burnt_bulbs(const char * details, bool is_critical);
void mqtt_report_normal_operation(const char * details);
void mqtt_report_suspend(const char * details);

void mqtt_service(void);


#endif