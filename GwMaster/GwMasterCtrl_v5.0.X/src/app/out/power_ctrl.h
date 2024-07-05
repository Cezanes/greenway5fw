#ifndef POWER_CTRL_H
#define POWER_CTRL_H

#include "sas/canbus.h"

typedef struct
{
   CanBusConfig can;
} PCtrlConfig;

typedef struct
{
   size_t pctrl_count;
} PCtrlSetup;

void pctrl_init(const PCtrlConfig * config);
bool pctrl_setup(const PCtrlSetup * setup);
bool pctrl_set(size_t port, size_t pin);
bool pctrl_is_board_present(size_t port);
bool pctrl_is_board_powered(size_t port);
bool pctrl_is_bulb_burnt(size_t port, size_t pin);

uint32_t pctrl_get_unpowered(void);
uint32_t pctrl_get_disconnected(void);
uint32_t pctrl_get_failed(void);
uint32_t pctrl_get_burnt(size_t port);

void pctrl_pswitch_set(bool en);
void pctrl_clear_outs(void);
void pctrl_clear_status(void);
void pctrl_compile_metrics(void);
void pctrl_commit(bool led_sync);
void pctrl_on_recv_msg(const CanMsg * msg);
void pctrl_service(void);

#endif