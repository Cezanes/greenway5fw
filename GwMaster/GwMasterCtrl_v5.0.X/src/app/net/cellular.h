#ifndef CELL_H
#define CELL_H

#include "types.h"
#include "sas/sim800c.h"
#include "app/sem/sem_objects.h"

enum 
{
   kCellUserRoleUnknown = 0,
   kCellUserRoleOperator,
   kCellUserRoleAdmin,
   kCellUserRoleOfficer,
   kCellUserRoleMax,
};

typedef struct __attribute__ ((packed))
{
   uint8_t role;
   char nr[kSizePhoneNr];
   char name[kSizeUserName];
} CellUser;


typedef struct __attribute__ ((packed))
{
  CellUser users[10];
  uint8_t user_count;
} CellData;

typedef struct
{
   GsmConfig gsm;

   bool ext_modem;
   size_t ext_modem_itf;
   void (*send_sms)(const char* no, const char * text, size_t len);
   void (*recv_sms)(const char* no, const char * text, size_t len);
   
   uint8_t * sms_buff;
   size_t sms_buff_size;
   
} CellConfig;


void cell_init(CellData * cell_data, const CellConfig * hconfig);
void cell_start(void);
void cell_service(void);

bool cell_sms_send(size_t itf, const char *phonenr, const char *text);
bool cell_receive_sms(size_t itf, const char *phonenr, const char *text, size_t len);

void cell_server_connect(void);
void cell_server_disconnect(void);
void cell_http_action(void);

void cell_report_new_state(void);




#endif