#ifndef LOGIC_H
#define LOGIC_H

#include "cfg/app_config.h"
#include "app/sem/sem_objects.h"

void logic_init();
void logic_start();
void logic_service();
uint32_t logic_get_uptime(void);

size_t logic_slink_set_local_prog(const SignalNetwork * netw);
size_t logic_slink_set_remote_prog(const SignalNetwork * netw);

size_t logic_slink_set_netw(const SignalNetwork * netw);
size_t logic_slink_set_config(const NetworkConfig * network, const RadioConfig * config);

size_t logic_rlink_set_netw(const SignalNetwork * netw);
bool logic_rlink_is_remote(void);

const SignalNetwork * logic_slink_get_prog(void);

uint32_t logic_slink_get_time(void);
void logic_slink_set_time(const uint32_t time);


void logic_have_gps_time(const bool have);
void logic_broadcast_time(const uint32_t time);
void logic_on_gps_status(bool available, uint32_t time);



#endif