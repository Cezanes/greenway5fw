#ifndef SIM800C_H
#define SIM800C_H

#include "atdrv.h"
#include "hal/pin32.h"


enum
{
   kGsmAtRespOK = 0,
   kGsmAtRespConnect,
   kGsmAtRespError,
   kGsmAtRespBusy,
   kGsmAtRespHttpAct,
   kGsmAtRespHttpRead,
   kGsmAtRespHttpDownload,
   kGsmAtRespTcpConnected,
   kGsmAtRespTcpDisconnected,
   kGsmAtRespTcpSend,
   kGsmAtRespTcpRecv,
   kGsmAtRespTcpState,
   
   kGsmAtRespMax,
   
   kGsmAtUrcRecvSms,
   kGsmAtUrcRing,
   kGsmAtUrcNoCarrier,
   kGsmAtUrcNoAnswer,
   kGsmAtUrcSmsReady,
   kGsmAtUrcTcpConnected,
   kGsmAtUrcTcpRecv,
   kGsmAtUrcTcpDisconnect,
   kGsmAtUrcPdpDeact,
   kGsmAtUrcBearerDeact,
};


typedef struct 
{
   const char *name;
   const char *apn;
   const char *user;
   const char *pass;
} GsmNetworkAPN;


typedef struct
{
   UartDev * uart_dev;
   uint32_t clock_src;
   uint32_t baud;
   uint8_t * uart_rx_buff;
   size_t uart_rx_buff_size;
   uint8_t * response_buff;
   size_t response_buff_size;
      
   const GsmNetworkAPN * apn;
   size_t apn_size;
   
   Pin pin_key;
   Pin pin_ring;
   Pin pin_power;
} GsmConfig;



void gsm_init(const GsmConfig * config);
bool gsm_detect(void);
void gsm_service(void);

void gsm_set_event_cb(void (*on_gsm_event)(size_t event_id, const char * param));
void gsm_get_internal_buff(void **buff, size_t * buff_size);

void gsm_power(bool on);
int gsm_init_modem(void);
int gsm_config(void);

int gsm_network_connect(void);
int gsm_network_disconnect(void);
int gsm_is_network_connected(void);

int gsm_pdp_activate(const char * apn, const char * user, const char * pass);
int gsm_pdp_reactivate(void);
int gsm_is_pdp_active(void);
int gsm_pdp_deactivate(void);

int gsm_find_apn(const GsmNetworkAPN ** apn);

bool gsm_send_sms(const char *dest, const char *content);
bool gsm_read_sms(char *src, char *content, size_t size, size_t *index);
bool gsm_delete_sms(size_t index);

int gsm_ip_init(void);
int gsm_http_get(const char * url, void * recv_data, size_t * recv_data_size, size_t * http_code);
int gsm_http_post(const char * url, const void * send_data, size_t send_data_size, void * recv_data, size_t * recv_data_size, size_t * http_code);

int gsm_tcp_connect(const char * host, size_t port);
int gsm_tcp_is_connected(void);
int gsm_tcp_send(const void * data, size_t data_size);
int gsm_tcp_read(void * data, size_t to_read, size_t * actual_read, size_t * remaining);
int gsm_tcp_wait_recv(uint32_t timeout);
int gsm_tcp_disconnect(void);







#endif