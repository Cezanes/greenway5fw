
#if !defined(MQTT_PLATFORM_H)
#define MQTT_PLATFORM_H

#include "types.h"

typedef struct MqttNetwork
{
   int (*mqttconnect)(struct MqttNetwork *, const char * host, size_t port);
	int (*mqttread)(struct MqttNetwork *, unsigned char * read_buffer, int size, int);
	int (*mqttwrite)(struct MqttNetwork *, const unsigned char * send_buffer, int size, int);
   int (*mqttdisconnect)(struct MqttNetwork *);
} MqttNetwork;


typedef struct 
{
   uint32_t tick;
} Timer;

/* The Timer structure must be defined in the platform specific header,
 * and have the following functions to operate on it.  */

void TimerInit(Timer *);
char TimerIsExpired(Timer *);
void TimerCountdownMS(Timer *, unsigned int);
void TimerCountdown(Timer *, unsigned int);
int TimerLeftMS(Timer *);


#endif