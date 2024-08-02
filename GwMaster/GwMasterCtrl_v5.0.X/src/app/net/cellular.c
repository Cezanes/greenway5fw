
#include "cfg/app_config.h"

#include "hal/sys.h"

#include "lib/utils.h"
#include "lib/datetime.h"
#include "lib/shared_buff.h"

#include "sal/timer.h"
#include "sal/debug.h"

#include "sas/sim800c.h"
#include "cellular.h"

#include "app/logic/logic.h"
#include "app/sem/semaphore.h"
#include "app/edge/edge.h"
#include "serial.h"

#include <stdio.h>

extern void __pic32_software_reset(void);


/////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct 
{
   const char cmd[16];
   const char usage[128];
   void (*cb)(size_t itf, const char *phonenr, char * msg, size_t msg_buff_size, size_t role);
} SmsCommand;

static void sms_process_new_msg(size_t itf, const char * phonenr, char * msg, size_t msg_buff_size);

static void sms_cmd_list(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_status(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_resume(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_disable(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_reset(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_suspend(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);
static void sms_cmd_user(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role);

static const SmsCommand sms_cmds[] = 
{
   {"list", "list", &sms_cmd_list},
   {"status", "status", &sms_cmd_status}, 
   {"suspend", "suspend", &sms_cmd_suspend}, 
   {"resume", "resume", &sms_cmd_resume}, 
   {"disable", "disable", &sms_cmd_disable}, 
   {"reset", "reset", &sms_cmd_reset}, 
   {"user", "user list\nuser add <name> <nr> <role>\nuser rem <name>", &sms_cmd_user},
};

static const char * role_str[kCellUserRoleMax] = 
{
   "unknown", "operator", "admin", "officer",
};

static const char * yes = "Yes";
static const char * no  = "No";


/////////////////////////////////////////////////////////////////////////////////////////////////////////


static struct
{
   CellData * data;
   const CellConfig * config;
   const GsmConfig * sim;
   
   bool modem_working;
   bool modem_powered;
   bool network_registered;
   bool connected;
   
   bool req_sms_read;
   bool req_tcp_read;
   bool req_tcp_disconnect;
   bool req_reconnect;
   bool req_reset;
   
   size_t reconnect_timer;
   size_t reconnect_retry_count;
   
} cell;

static void modem_connect_timer(void);


////////////////////////////////////////////////  Utils  /////////////////////////////////////////////


static bool reply_sms(size_t itf, const char *phonenr, const char *msg)
{
   //DBG(kLvlVerb, "replying sms itf %u:\n\n%s", itf, msg);
   
   if(app_config.have_gsm && cell.modem_working && 
      (itf == kSlinkItfAll || itf & kSlinkItfCell))
   {
      DBG(kLvlInfo, "disabled sms:\n\n%s", msg);
      return true;

      if(!gsm_send_sms(phonenr, msg))
      {
         DBG(kLvlError, "cell, cannot send SMS to %s", phonenr);
         cell.modem_working = false;
         timer_reset(cell.reconnect_timer);
         return false;
      }
   }
   
   edge_send_sms(phonenr, msg);
   //serial_send_sms_msg(itf, phonenr, msg, strlen(msg));
   
   return true;
}

static void read_stored_sms(void)
{
   char nr[24];
   size_t index;

   char * buff = cell.config->sms_buff;
   size_t buff_size = cell.config->sms_buff_size;
      
   while(gsm_read_sms(nr, buff, buff_size, &index))
   {
      gsm_delete_sms(index);
      sms_process_new_msg(kSlinkItfCell, nr, buff, buff_size);
   }
}

static void send_role_sms(size_t itf, const char *msg, size_t role)
{
   for(size_t i = 0; i < cell.data->user_count; i++)
   {
      if(cell.data->users[i].role == role)
      {
         reply_sms(itf, cell.data->users[i].nr, msg);
      }
   }
}


static void reply_invalid_param(size_t itf, const char *phonenr, const char *param)
{
   if(param == NULL)
   {
      reply_sms(itf, phonenr, "GW: error, missing parameter");
   }
   else
   {
      char buff[96];
      snprintf(buff, sizeof(buff), "GW: error, invalid parameter \n'%.20s'", param);
      reply_sms(itf, phonenr, buff);
   }
}

static const char * next_word(const char * str)
{
   if(str == NULL)
      return NULL;
   
   for(;*str != 0; str++)
   {
      if(*str == ' ')
      {
         while(*str == ' ') str++;
         if(*str == 0)
            return NULL;
         
         return str;
      }
   }
   
   return NULL;
}

static bool same_number(const char *nr1, const char * nr2)
{
   size_t size1 = strlen(nr1);
   size_t size2 = strlen(nr2);
   
   if(size1 < 10 || size2 < 10)
   {
      //DBG(kLvlWarn, "invalid phone number '%s' or '%s'", nr1, nr2);
      return false;
   }
   
   size1--;
   size2--;
   
   for(;size1 > 0 && size2 > 0; size1--, size2--)
   {
      size_t c1 = nr1[size1];
      size_t c2 = nr2[size2];
      
      if(c1 == '+') c1 = '0';
      if(c2 == '+') c2 = '0';
      
      if(c1 != c2)
         return false;
   }
   
   return true;
}

static size_t get_role(const char *phonenr)
{
   for(size_t i = 0; i < cell.data->user_count; i++)
   {
      if(same_number(phonenr, cell.data->users[i].nr))
         return cell.data->users[i].role;
   }
   
   return kCellUserRoleUnknown;
}

static size_t get_role_from_str(const char *str)
{
   for(size_t i = 0; i < COUNT(role_str); i++)
   {
      if(utils_strncasecmp(str, role_str[i], strlen(role_str[i])) == 0)
         return i;
   }
   
   return kCellUserRoleUnknown;
}

static const CellUser * add_user(const char *name, const char *nr, size_t role)
{
   if(cell.data->user_count >= COUNT(cell.data->users))
   {
      return NULL;
   }
   
   CellUser user = {0};
   utils_strncpy_word(user.name, name, sizeof(user.name) - 1);
   utils_strncpy_word(user.nr, nr, sizeof(user.nr) - 1);
   user.role = role;
   
   cell.data->users[cell.data->user_count] = user;
   cell.data->user_count++;
   app_config_write();
   
   return &cell.data->users[cell.data->user_count - 1];
}

static int find_user(const char *name)
{
   CellUser user = {0};
   utils_strncpy_word(user.name, name, sizeof(user.name) - 1);
   size_t len = strlen(user.name) + 1;
   
   for(size_t i = 0; i < cell.data->user_count; i++)
   {
      if(utils_strncasecmp(user.name, cell.data->users[i].name, len) == 0)
      {
         return i;
      }
   }
   
   return -1;
}

static bool remove_user(int index)
{
   if(index >= cell.data->user_count)
      return false;
   
   if(index != cell.data->user_count - 1)
   {
      memcpy(
         &cell.data->users[index], 
         &cell.data->users[index + 1], 
         sizeof(CellUser) * (cell.data->user_count - index - 1));
   }
   
   cell.data->user_count--;
   app_config_write();
   
   return true;
}


//////////////////////////////////////////  SMS Handler  //////////////////////////////////////////


static void sms_process_new_msg(size_t itf, const char * phonenr, char * msg, size_t msg_buff_size)
{
   DBG(kLvlInfo, "sms, received cmd: '%s'", msg);
   
   size_t role = get_role(phonenr);
   if(role == kCellUserRoleUnknown)
   {
      DBG(kLvlWarn, "sms, unregistered user %s", phonenr);
      
      size_t end = utils_str_shift_end(msg, msg_buff_size);
      size_t len = snprintf(msg, end, "GW: unregistered user %s send msg:\n", phonenr);
      len = len > end ? end : len;
      utils_str_shift_back(msg, msg_buff_size, end, len);
      
      send_role_sms(itf, msg, kCellUserRoleOfficer);
      
      return;
   }
   
   
   bool found = false;
   
   char cmd[16] = {0};
   utils_strncpy_word(cmd, msg, sizeof(cmd) - 1);
      
   for(size_t i = 0; i < COUNT(sms_cmds); i++)
   {
      if(utils_strcasecmp(sms_cmds[i].cmd, cmd) == 0)
      {
         found = true;
         sms_cmds[i].cb(itf, phonenr, msg, msg_buff_size, role);
         break;
      }
   }
   
   if (false == found)
   {
      DBG(kLvlWarn, "sms, unknown sms command: %s", msg);
      reply_sms(itf, phonenr, "GW: error, unknown command.\nUse 'list' to print all supported commands.");
      return;
   }
}

static void sms_cmd_user(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{   
   const char *word = next_word(msg);
   
   char subcmd[16] = {0};
   utils_strncpy_word(subcmd, word, sizeof(subcmd) - 1);
   
   if(utils_strcasecmp(subcmd, "list") == 0)
   {
      strcpy(msg, "GW: user list:\n");
      
      for(size_t i = 0; i < cell.data->user_count; i++)
      {
         char str[64];
         size_t count = snprintf(str, sizeof(str), "%.24s, %.15s, %s", cell.data->users[i].name, cell.data->users[i].nr, role_str[cell.data->users[i].role]);
         
         if((strlen(msg) + count + 4) < msg_buff_size)
         {
            strcat(msg, str);

            if(i != cell.data->user_count - 1)
               strcat(msg, "\n");
         }
      }
      
      reply_sms(itf, phonenr, msg);
   }
   else if(utils_strcasecmp(subcmd, "add") == 0)
   {
      if(role < kCellUserRoleAdmin)
      {
         snprintf(msg, msg_buff_size, "GW: error, insufficient privileges");
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      if(cell.data->user_count >= COUNT(cell.data->users))
      {
         snprintf(msg, msg_buff_size, "GW: error, user slots full");
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      const char *name = next_word(word);
      const char *nr = next_word(name);
      const char *role = next_word(nr);
      
      if(!name || !nr || !role)
      {
         snprintf(msg, msg_buff_size, "GW: error, invalid format, use:\nuser add <name> <nr> <role>");
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      if(!utils_valid_phone_nr(nr))
      {
         snprintf(msg, msg_buff_size, "GW: error, invalid phone nr '%s'", nr);
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      int index = find_user(name);
      if(index >= 0)
      {
         snprintf(msg, msg_buff_size, "GW: error, user already exists");
         reply_sms(itf, phonenr, msg);
         return;
      }

      size_t new_role = get_role_from_str(role);
      if(new_role == kCellUserRoleUnknown || new_role >= kCellUserRoleOfficer)
      {
         snprintf(msg, msg_buff_size, "GW: error, invalid role '%s'. Available roles:\n", role);
         
         for(size_t i = 0; i < COUNT(role_str); i++)
         {
            if(i == kCellUserRoleUnknown || i == kCellUserRoleOfficer)
               continue;
            
            strcat(msg, role_str[i]);
            strcat(msg, "\n");
         }
         
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      const CellUser * new_user = add_user(name, nr, new_role);
      
      if(new_user != NULL)
      {
         snprintf(msg, msg_buff_size, "GW: new user added:\n%.24s, %.15s, %s", new_user->name, new_user->nr, role_str[new_user->role]);
         reply_sms(itf, phonenr, msg);
      }
   }
   else if(utils_strcasecmp(subcmd, "rem") == 0)
   {
      if(role < kCellUserRoleAdmin)
      {
         snprintf(msg, msg_buff_size, "GW: error, insufficient privileges");
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      const char *name = next_word(word);
      
      if(!name)
      {
         snprintf(msg, msg_buff_size, "GW: error, invalid format, use:\nuser rem <name>");
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      int index = find_user(name);
      if(index < 0)
      {
         snprintf(msg, msg_buff_size, "GW: error, could not find user '%s'", name);
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      if(cell.data->users[index].role == kCellUserRoleOfficer)
      {
         snprintf(msg, msg_buff_size, "GW: error, cannot remove %s roles.", role_str[kCellUserRoleOfficer]);
         reply_sms(itf, phonenr, msg);
         return;
      }
      
      remove_user(index);
      
      snprintf(msg, msg_buff_size, "GW: user '%s' removed", name);
      reply_sms(itf, phonenr, msg);
      
   }
   else
   {
      reply_invalid_param(itf, phonenr, word);
   }
}

static void sms_cmd_list(size_t itf, const char *phonenr, char * msg, size_t msg_buff_size, size_t role)
{
   snprintf(msg, msg_buff_size, "GW: command list:\n");
   
   for(size_t i = 0; i < COUNT(sms_cmds); i++)
   {
      if((strlen(msg) + strlen(sms_cmds[i].usage) + 4) < msg_buff_size)
      {
         strcat(msg, sms_cmds[i].usage);
         
         if(i != COUNT(sms_cmds) - 1)
            strcat(msg, "\n");
      }
   }
   
   msg[msg_buff_size - 1] = 0;
   
   reply_sms(itf, phonenr, msg);
}

static size_t add_id_header(char * buff, size_t dest_size)
{
   size_t size = 0;
   const SignalNetwork * netw = logic_slink_get_prog();
   
   if(netw != NULL)
   {
      size += snprintf(&buff[size], dest_size - size, "%s\n", netw->name);
      if(netw->controller_count)
      {
         const SignalController * ctrl = (const SignalController *) (netw + 1);
         size += snprintf(&buff[size], dest_size - size, "%u: %s\n", ctrl->id, ctrl->name);
      }
   }
   
   return size;
}

static void sms_cmd_status(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{
   size_t size = snprintf(msg, msg_buff_size, "GW: status\n");   
   size += add_id_header(&msg[size], msg_buff_size - size);
   
   const SignalSchedule * sch = sem_get_current_sch();
   if(sch != NULL)
   {
      size += snprintf(&msg[size], msg_buff_size - size, "Sch: %s\n", sch->name);   
   }
   
   uint32_t uptime = logic_get_uptime();
   if(uptime > 0)
   {
      DateTime dt;
      dte_get_datetime(uptime, &dt);
      size += snprintf(&msg[size], msg_buff_size - size, "Uptime: %u.%u.%u %02u:%02u:%02u\n", dt.years - 1970, dt.months - 1, dt.days - 1, dt.hours, dt.minutes, dt.seconds);
   }
   
   size += snprintf(&msg[size], msg_buff_size - size, "Status: %s\n", sem_get_state_str(true));   
   
   msg[msg_buff_size - 1] = 0;
   reply_sms(itf, phonenr, msg);
}

static void sms_cmd_resume(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{
   sem_operation_resume();
}

static void sms_cmd_disable(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{
   sem_operation_disable();
}

static void sms_cmd_reset(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{
   cell.req_reset = true;
}

static void sms_cmd_suspend(size_t itf, const char *phonenr, char *msg, size_t msg_buff_size, size_t role)
{
   sem_operation_suspend();
}


//////////////////////////////////////////     Network      //////////////////////////////////////////


static bool modem_start(void)
{
   if(!cell.modem_powered)
   {
      gsm_power(true);
      cell.modem_powered = true;
      return (kOK == gsm_init_modem());
   }
   
   return true;
}

static void modem_stop(void)
{
   if(cell.modem_powered)
   {
      if(kOK == gsm_tcp_is_connected())
      {
         gsm_tcp_disconnect();
         gsm_pdp_deactivate();
      }
      
      cell.modem_powered = false;
      gsm_power(false);
   }
   
   cell.network_registered = false;
   cell.modem_working = false;
}

static bool modem_is_network_connected(void)
{
    if (!cell.modem_powered)
        return false;

    if (kOK != gsm_is_network_connected())
        return false;

    if (kOK != gsm_is_pdp_active())
        return false;

    return true;
}

static bool modem_network_connect(void)
{
   if (!cell.modem_powered)
   {
       if (!modem_start())
       {
           DBG(kLvlError, "cell, failed to initalize modem");
           return false;
       }

       if (kOK != gsm_config())
       {
           DBG(kLvlError, "cell, failed to configure modem");
           return false;
       }
   }
   
#if 0
   {
      if(!cell.network_registered)
      {
         (void)gsm_pdp_deactivate();
         (void)gsm_network_disconnect();
      }

      if (!modem_is_network_connected())
      {
         (void)gsm_pdp_deactivate();
         (void)gsm_network_disconnect();

         if (kOK != gsm_network_connect())
         {
            DBG(kLvlError, "cell, fail to connect to GSM network");
            return false;
         }

         if (kOK != gsm_is_pdp_active())
         {
            const GsmNetworkAPN * apn;

            int resp = gsm_find_apn(&apn);
            if(resp != kOK)
            {
               DBG(kLvlError, "cell, cannot get APN");
               return false;
            }

            resp = gsm_pdp_activate(apn->apn, "", "");
            if(resp != kOK)
            {
               DBG(kLvlError, "cell, cannot activate PDP context");
               return false;
            }
         }   
      }
   }
#endif
   
   cell.network_registered = true;
   cell.modem_working = true;
   cell.req_sms_read = true;
   
   return true;
}

static void server_disconnect(void)
{
   if(cell.connected)
   {
      //mqtt_disconnect();
      gsm_tcp_disconnect();

      cell.connected = false;
      
      if(cell.reconnect_retry_count < 3)
      {
         cell.reconnect_retry_count++;
         cell.req_reconnect = true;
      }
      else 
      {
         timer_reset(cell.reconnect_timer);
      }
   }
}

static bool server_connect(void)
{
   cell.connected = false;
   
   if (!modem_network_connect())
   {
       DBG(kLvlError, "cell, failed to connect to network operator");
       return false;
   }
   
   cell.connected = true;
   
   /*if(mqtt_enabled() && !mqtt_connect())
   {
      cell_server_disconnect();
      return false;
   }*/

    
   return true;
}

static void modem_connect_timer(void)
{
   cell.reconnect_retry_count++;
   
   if((cell.reconnect_retry_count % 5) == 0)
   {
      modem_stop();
      timer_delay_ms(500);
   }
   
   if(modem_network_connect())
   {
      if(server_connect())
      {
         cell.reconnect_retry_count = false;
         timer_set_period(cell.reconnect_timer, 30 * 1000);
         return;
      }
   }
   
   uint32_t period = timer_get_period(cell.reconnect_timer) * 2;
   
   if(period > 6 * 60 * 60 * 1000)
      period = 6 * 60 * 60 * 1000;
   
   DBG(kLvlInfo, "cell, reschedule modem connect after %u sec", period / 1000);
   
   timer_set_period(cell.reconnect_timer, period);
   timer_reset(cell.reconnect_timer);
}


///////////////////////////////////////////////    Events   //////////////////////////////////////////////////


static void on_gsm_event(size_t id, const char * param)
{
   switch(id)
   {
      case kGsmAtUrcRecvSms:
      {
         cell.req_sms_read = true;
         break;
      }
      
      case kGsmAtUrcRing:
      {
         DBG(kLvlInfo, "cell, receiving call from %s", param);
         break;
      }
      
      case kGsmAtUrcNoCarrier:
      {
         DBG(kLvlInfo, "cell, call ended");
         break;
      }
      
      case kGsmAtUrcTcpRecv:
      {
         cell.req_tcp_read = true;
         break;
      }
      
      case kGsmAtUrcTcpDisconnect:
      {
         cell.req_tcp_disconnect = true;
         break;
      }
      
      case kGsmAtUrcPdpDeact:
      case kGsmAtUrcBearerDeact:
      {
         gsm_pdp_deactivate();
         break;
      }
   }
}



//////////////////////////////////////////////////   Public   /////////////////////////////////////////////////


bool cell_sms_send(size_t itf, const char *phonenr, const char *msg)
{
   return reply_sms(itf, phonenr, msg);
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

void cell_report_new_state(void)
{
   //if(!app_config.have_gsm || !cell.modem_working)
   //   return;
   
   const GlobalState * state = state_global();

   char * buff = cell.config->sms_buff;
   size_t buff_size = cell.config->sms_buff_size;
   const SignalNetwork * netw = logic_slink_get_prog();
   const SignalController * ctrl = (const SignalController *) (netw + 1);
   
   bool add_boards = false;
   bool add_bulbs = false;
   uint32_t map = 0;
   size_t size = 0;
   
   switch(state->sem->global)
   {
      case kSemStateUnknown:
      case kSemStateInit:
      {
         return;
      }
      
      case kSemStateNormal:
      {
         //if(state->sem->just_booted)
         //   return;
         
         size += snprintf(&buff[size], buff_size - size, "GW: Normal operation\n");
         
         break;
      }
      
      case kSemStateAlert:
      {
         size += snprintf(&buff[size], buff_size - size, "GW: Alert! Bulb failure!\n");\
         add_bulbs = true;
         break;
      }
      
      case kSemStateSuspended:
      {
         size += snprintf(&buff[size], buff_size - size, "GW: Controller suspended\n");
         break;
      }
      
      case kSemStateSuspendedManually:
      {
         size += snprintf(&buff[size], buff_size - size, "GW: Controller manually suspended\n");
         break;
      }
      
      case kSemStateDisabled:
      {
         size += snprintf(&buff[size], buff_size - size, "GW: Controller disabled\n");
         break;
      }
      
      case kSemStateError:
      {
         switch(state->sem->error)
         {
            case kSemErrorBulbFailure:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Error! Bulb failure!\nController suspended!\n");
               add_bulbs = true;
               break;
            }
            
            case kSemErrorBoardUnpowered:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Error! Unpowered board!\nController suspended!\n");
               map = state->metrics->unpowered_boards;
               add_boards = true;
               break;
            }
            
            case kSemErrorBoardFailure:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Error! Failed board!\nController disabled!\n");
               map = state->metrics->failed_boards;
               add_boards = true;
               break;
            }
            
            default:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Error! Unknown error!\n");
               break;
            }
         }
         
         break;
      }
      
      case kSemStateFatal:
      {
         switch(state->sem->error)
         {
            case kSemErrorBoardDisconnected:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Fatal Error! Disconnected board. Controller disabled!\n");
               map = state->metrics->disconnected_boards;
               add_boards = true;
               break;
            }
            
            case kSemErrorBoardFailure:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Fatal Error! Failed board. Controller disabled!\n");
               map = state->metrics->failed_boards;
               add_boards = true;
               break;
            }
            
            default:
            {
               size += snprintf(&buff[size], buff_size - size, "GW: Fatal Error! Internal error. Controller disabled!\n");
               break;
            }
         }
         
         break;
      }
      
      default:
      {
         DBG(kLvlError, "cell, unhandled sem state %u", state->sem->global);
         break;
      }
   };
   
   size += add_id_header(&buff[size], buff_size - size);
   
   if(add_boards)
   {
      size += str_add_boards(&buff[size], buff_size - size, map);
   }
   
   if(add_bulbs)
   {
      size += str_add_bulbs(
         &buff[size], 
         buff_size - size, 
         state->metrics->burnt_bulbs_critical, 
         state->metrics->burnt_bulbs_non_critical, 
         COUNT(state->metrics->burnt_bulbs_critical));
   }
   
   // DBG(kLvlWarn, "state:\n%s", buff);
      
   send_role_sms(kSlinkItfAll, buff, kCellUserRoleOfficer);
   send_role_sms(kSlinkItfAll, buff, kCellUserRoleAdmin);
   send_role_sms(kSlinkItfAll, buff, kCellUserRoleOperator);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void cell_server_connect(void)
{
   server_connect();
}

void cell_server_disconnect(void)
{
   server_disconnect();
}

void cell_http_action(void)
{
   gsm_ip_init();
   
   uint8_t * payload = shared_buff_get_chunk();
   size_t payload_max_size = shared_buff_chunk_size();
   size_t http_code;
   size_t payload_size = payload_max_size;

   payload_max_size--;  
     
   gsm_http_get("get-url.com/", payload, &payload_size, &http_code);
   DBG(kLvlInfo, "cell, payload %u, %u\r\n%s", payload_size, http_code, payload);

   size_t send_size = 5;
   payload_size = payload_max_size;
   gsm_http_post("httpbin.org/post", "hello", send_size, payload, &payload_size, &http_code);

   DBG(kLvlInfo, "cell, payload %u, %u, %s", payload_size, http_code, payload);
   shared_buff_release_chunk(payload);
}

static void cell_modem_service(void)
{
   gsm_service();

   if(cell.req_sms_read)
   {
      cell.req_sms_read = false;
      cell.modem_working = true;
      read_stored_sms();
   }
   
   if(cell.req_tcp_read)
   {
      cell.req_tcp_read = false;
      //mqtt_on_data_recv();
   }
   
   if(cell.connected)
   {
      //mqtt_keep_alive();
   }
   
   if(cell.req_tcp_disconnect)
   {
      cell.req_tcp_disconnect = false;
      cell_server_disconnect();
   }
   
   if(cell.req_reconnect)
   {
      cell.req_reconnect = false;
      modem_connect_timer();
   }
}


//////////////////////////////////////////////////   Public Base   //////////////////////////////////////////////////


bool cell_receive_sms(size_t itf, const char *phonenr, const char *text, size_t len)
{
   char * buff = cell.config->sms_buff;
   size_t buff_size = cell.config->sms_buff_size - 1;
   
   memset(buff, 0, buff_size);
   size_t min = buff_size < len ? buff_size : len;
   
   strncpy(buff, text, min);   
   
   sms_process_new_msg(itf, phonenr, buff, buff_size);
}


//////////////////////////////////////////////////   Public Base   //////////////////////////////////////////////////


void cell_init(CellData * cell_data, const CellConfig * config)
{
   cell.data = cell_data;
   cell.config = config;
   
   if(app_config.have_gsm)
   {
      cell.reconnect_timer = timer_add(modem_connect_timer, 30 * 1000, false, false);

      gsm_init(&config->gsm);
      gsm_set_event_cb(on_gsm_event);
   }
}

void cell_start(void)
{
   if(app_config.have_gsm)
   {
      modem_connect_timer();
   }
}

void cell_service(void)
{
   if(app_config.have_gsm && cell.modem_working)
   {
      cell_modem_service();
   }
 
   if(cell.req_reset)
   {
      cell.req_reset = false;
      
      if(app_config.have_gsm && cell.modem_working)
         gsm_power(false);
      
      __pic32_software_reset();
   }
}