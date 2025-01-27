#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "edge_msg.h"

void edge_send_ctrl_status(void);

void edge_send_sms(const char * nr, const char * text);
bool edge_parse_ctrl_get(DataCtrlReq * req, const void * data, size_t data_size);
bool edge_parse_ctrl_set_config(DataCtrlConfig * data, const void * jsonstr, size_t jsonstr_size);
bool edge_parse_ctrl_set_title(DataCtrlTitle * data, const void * jsonstr, size_t jsonstr_size);
bool edge_parse_mon_sms(DataMonSms * msg, const void * jsonstr, size_t jsonstr_size);


void edge_send_to_server(size_t id, const void *msg, size_t size);
void edge_send_to_monitor(size_t id, const void *msg, size_t size);

void edge_init();
void edge_start();
void edge_service();