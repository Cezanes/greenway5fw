#include "types.h"
#include "sim800c.h"

#include "sal/debug.h"
#include "sal/timer.h"

#include "hal/sys.h"
#include "lib/utils.h"

#include <stdio.h>

#define AT_CMD_RETRY_COUNT                            3
#define AT_CMD_RETRY_DELAY                          500


/////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct
{
   const GsmConfig * config;
   void (*on_gsm_event)(size_t event_id, const char *param);
   uint8_t urc_buff[128];
   AtResp urc_resp;
} GsmInternal;


/////////////////////////////////////////////////////////////////////////////////////////////////


/* Supported responses from AT comands */
static const AtRespType at_resp_type[] = 
{
   { kGsmAtRespOK,              "OK" AT_CMD_ENDL},
   { kGsmAtRespConnect,         "CONNECT" AT_CMD_ENDL},
   { kGsmAtRespError,           "ERROR" AT_CMD_ENDL},
   { kGsmAtRespBusy,            "BUSY" AT_CMD_ENDL},
   { kGsmAtRespHttpAct,         "+HTTPACTION: "},
   { kGsmAtRespHttpRead,        "+HTTPREAD: "},
   { kGsmAtRespHttpDownload,    "DOWNLOAD" AT_CMD_ENDL},
   { kGsmAtRespTcpConnected,    "CONNECT OK" AT_CMD_ENDL},
   { kGsmAtRespTcpDisconnected, "CLOSE OK" AT_CMD_ENDL},
   { kGsmAtRespTcpSend,         "SEND OK" AT_CMD_ENDL},
   { kGsmAtRespTcpRecv,         "+CIPRXGET"},
   { kGsmAtRespTcpState,        "STATE: "},
};

static const AtRespType at_urc_resp_type[] = 
{
   { kGsmAtUrcRecvSms,       "+CMTI: "},
   { kGsmAtUrcRing,          "+CLIP" },
   { kGsmAtUrcNoCarrier,     "NO CARRIER" },
   { kGsmAtUrcNoAnswer,      "NO ANSWER" },
   { kGsmAtUrcSmsReady,      "SMS Ready" },
   { kGsmAtUrcTcpConnected,  "CONNECT OK"},
   { kGsmAtUrcTcpRecv,       "+CIPRXGET: 1"},
   { kGsmAtUrcTcpDisconnect, "CLOSED"},
   { kGsmAtUrcPdpDeact,      "+SAPBR 1: DEACT"},
   { kGsmAtUrcBearerDeact,   "+PDP: DEACT"},
};

static GsmInternal gsm;


////////////////////////////////////////////////////////////////////////////////////////////////


void gsm_init(const GsmConfig * config)
{
   gsm.config = config;
   gsm.urc_resp.buff = gsm.urc_buff;
   gsm.urc_resp.buff_size = sizeof(gsm.urc_buff);
   
   const AtConfig at_config = 
   {
      .uart_dev = config->uart_dev,
      .clock_src = config->clock_src,
      .baud = config->baud,
      .rx_buff = config->uart_rx_buff,
      .rx_buff_size = config->uart_rx_buff_size,
      .at_resp_type = at_resp_type,
      .at_resp_count = COUNT(at_resp_type),
   };
   
   pin_output(&gsm.config->pin_key);
   pin_write(&gsm.config->pin_key, 0);  
   pin_input(&gsm.config->pin_ring);
   
   pin_write(&gsm.config->pin_power, 0);
   pin_output(&gsm.config->pin_power);
   
   at_init(&at_config);
}

void gsm_set_event_cb(void (*on_gsm_event)(size_t event_id, const char * param))
{
   gsm.on_gsm_event = on_gsm_event;
}

void gsm_get_internal_buff(void **buff, size_t * buff_size)
{
   *buff = gsm.config->response_buff;
   *buff_size = gsm.config->response_buff_size;
}

static AtResp new_resp(void)
{
   return (AtResp) {
      .buff = gsm.config->response_buff,
      .buff_size = gsm.config->response_buff_size,
   };
}

static void send_command(const char *cmd)
{
   timer_delay_ms(50);
   DBG(kLvlDbg, "gsm, sent %s", cmd);
   at_rx_clear();
   at_command(cmd);
}

static void send_command_param(const char * head, const char * param, const char * foot)
{
   timer_delay_ms(50);
   
   DBG(kLvlDbg, "sent %s%s%s", head, param, foot);
   at_rx_clear();
   
   size_t len = strlen(head);
   at_send_data(head, len);
   
   len = strlen(param);
   at_send_data(param, len);
   
   at_command(foot);
}

static size_t get_response_to(AtResp *resp, size_t timeout)
{
   size_t code = at_get_response_to(resp, timeout);  
   DBG(kLvlDbg, "gsm, GSM resp %s", &resp->buff[0]);
   return code;
}

static size_t get_response(AtResp *resp)
{
   return get_response_to(resp, 2000);
}

void static gsp_print_resp(int lvl, const char * cmd, AtResp *resp)
{
   dbg_print_hdr(lvl, "gsm, cmd %s: ", cmd);
   char * pos = at_parse_get_first_line(resp);
   while(*pos)
   {
      char c = *pos;
      if(!at_parse_is_valid_char(c))
      {
         c = ' ';
      }
      
      dbg_print_raw(lvl, "%c", c);
      
      pos++;
   }

   dbg_println(lvl);
}

void static gsp_print_resp_param(int lvl, const char * head, const char * param, const char * foot, AtResp *resp)
{
   dbg_print_hdr(lvl, "gsm, cmd %s%s%s: ", head, param, foot);
   char * pos = at_parse_get_first_line(resp);
   while(*pos)
   {
      char c = *pos;
      if(!at_parse_is_valid_char(c))
      {
         c = ' ';
      }
      
      dbg_print_raw(lvl, "%c", c);
      
      pos++;
   }

   dbg_println(lvl);
}

bool gsm_cmd_single(const char *cmd)
{
   AtResp resp = new_resp();
   send_command(cmd);
   bool ok = kGsmAtRespOK == get_response(&resp);
   gsp_print_resp(kLvlVerb, cmd, &resp);
   return ok;
}

bool gsm_cmd(const char *cmd)
{
   uint8_t retry = AT_CMD_RETRY_COUNT;
   while(retry--)
   {
      for(;;)
      {
         AtResp resp = new_resp();

         send_command(cmd);
         if(kGsmAtRespOK != get_response(&resp))
         {
            if (resp.code < COUNT(at_resp_type))
            {
               DBG(kLvlWarn, "gsm, failed cmd %s, err %s", cmd, at_resp_type[resp.code].name);
            }
            else if (resp.code == AT_RESP_TIMEOUT)
            {
               DBG(kLvlWarn, "gsm, failed cmd %s, err timeout", cmd);
            }
            else
            {
               DBG(kLvlWarn, "gsm, failed cmd %s, err %u", cmd, resp.code);
            }
            
            break;
         }
         else
         {
            gsp_print_resp(kLvlVerb, cmd, &resp);
         }

         return true;
      }

      // Wait some time before retrying.
      timer_delay_ms(AT_CMD_RETRY_DELAY);
   }

   return false;
}

bool gsm_param_cmd(const char * head, const char * param, const char * foot)
{
   uint8_t retry = AT_CMD_RETRY_COUNT;
   while(retry--)
   {
      for(;;)
      {
         AtResp resp = new_resp();

         send_command_param(head, param, foot);
         
         if(kGsmAtRespOK != get_response(&resp))
         {
            if (resp.code < COUNT(at_resp_type))
            {
               DBG(kLvlWarn, "failed cmd %s%s%s, err %s", head, param, foot, at_resp_type[resp.code].name);
            }
            else if (resp.code == AT_RESP_TIMEOUT)
            {
               DBG(kLvlWarn, "failed cmd %s%s%s, err timeout", head, param, foot);
            }
            else
            {
               DBG(kLvlWarn, "failed cmd %s%s%s, err %u", head, param, foot, resp.code);
            }
            
            break;
         }
         else
         {
            gsp_print_resp_param(kLvlVerb, head, param, foot, &resp);
         }

         return true;
      }

      // Wait some time before retrying.
      timer_delay_ms(AT_CMD_RETRY_DELAY);
   }

   return false;
}

bool gsm_repeat_till_to(const char * cmd, AtResp *resp, size_t code, size_t total_timeout_ms, size_t cmd_timeout_ms, size_t cmd_repeat_ms)
{
   uint32_t time_start = timer_tick();
   while(timer_tick() - time_start < TM_MLS_T0_TICK(total_timeout_ms))
   {
      send_command(cmd);
      
      if(code != get_response_to(resp, cmd_timeout_ms))
      {
         if (resp->code < kGsmAtRespMax)
         {
            gsp_print_resp(kLvlWarn, cmd, resp);
            timer_delay_ms(cmd_repeat_ms);
         }
         else if (resp->code == AT_RESP_TIMEOUT)
         {
            DBG(kLvlWarn, "gsm, failed cmd %s, err timeout", cmd);
         }
         else
         {
            DBG(kLvlWarn, "gsm, failed cmd %s, err %u", cmd, resp->code);
         }
      }
      else
      {
         gsp_print_resp(kLvlVerb, cmd, resp);
         return true;
      }
   }
   
   return false;
}

size_t gsm_cmd_resp(const char *cmd, AtResp *resp)
{
   send_command(cmd);   
   return get_response(resp);
}

static size_t send_cmd_to(const char *cmd, AtResp *resp, uint32_t timeout)
{
   send_command(cmd);
   size_t code = at_get_response_to(resp, timeout);  
   DBG(kLvlDbg, "recv '%s'", &resp->buff[0]);
   return code;
}

bool gsm_get_imei(uint8_t *imei, size_t size)
{
   uint8_t retry = AT_CMD_RETRY_COUNT;
   while(retry--)
   {
      for(;;)
      {
         DBG(kLvlInfo, "gsm, getting IMEI.");
        
         send_command("AT+GSN");
         
         AtResp resp = new_resp();
         if(kGsmAtRespOK != get_response(&resp))
         {
            DBG(kLvlError, "gsm, unable to get IMEI, err %u", resp.code);
            break;
         }
         
         char *line = at_parse_get_first_line(&resp);
         if(!line)
         {
            DBG(kLvlError, "gsm, invalid reply format from AT+GSN:\n%s", &resp.buff[0]);
            break;
         }
         
         line = at_parse_get_next_line(&resp);
         if(!line)
         {
            DBG(kLvlError, "gsm, invalid reply format from AT+GSN");
            break;
         }
         
         uint16_t imei_size = at_parse_get_line_size(line);
         imei_size = imei_size < size ? imei_size : size;
         
         memset(imei, 0, size);
         memcpy(imei, line, imei_size);

         return true;
      }

      // Wait some time before retrying.
      timer_delay_ms(AT_CMD_RETRY_DELAY);
   }

   return false;
}

void gsm_power(bool on)
{
   if (on)
   {
      pin_write(&gsm.config->pin_power, 1);
      timer_delay_ms(500);
      pin_write(&gsm.config->pin_key, 1);
      timer_delay_ms(1000);
      pin_write(&gsm.config->pin_key, 0);   
   }
   else
   {
      pin_write(&gsm.config->pin_key, 1);
      timer_delay_ms(1600);
      pin_write(&gsm.config->pin_key, 0);
      timer_delay_ms(400);
      pin_write(&gsm.config->pin_power, 0);
   }
}

int gsm_init_modem(void)
{
   AtResp resp = new_resp();
   
   if(!gsm_repeat_till_to("ATE0", &resp, kGsmAtRespOK, 10000, 1000, 500))
   {
      DBG(kLvlError, "gsm, modem is not responding");
      return kErrorNotResponding;
   }
   
   if(!gsm_cmd("AT+CMEE=0"))
   {
      DBG(kLvlError, "gsm, could not set error format");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+GSN"))
   {
      DBG(kLvlError, "gsm, cannot get serial number");
      return kErrorSim;
   }
   
   if(!gsm_cmd("AT+CREG=0"))
   {
      DBG(kLvlError, "gsm, could not disable network events");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CGMM"))
   {
      DBG(kLvlError, "gsm, could not get model number");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CGMR"))
   {
      DBG(kLvlError, "gsm, could not get hw revision");
      return kErrorProtocol;
   }
   
   gsm_cmd_single("AT+CIPMUX=0");
   gsm_cmd_single("AT+CIPRXGET=1");
   
   /*gsm_cmd_resp("AT+CSDH=0", &resp);
   if(resp.code == kGsmAtRespOK)
   {
      return gsm_config();
   }
   else if (complete)
   {
      if(!gsm_repeat_till_to("AT+CSDH=0", &resp, kGsmAtRespOK, 60000, 2000, 1000))
      {
         DBG(kLvlError, "gsm, could not set SMS mode param");
         return kErrorProtocol;
      }
      
      return gsm_config();
   }*/
   
   return kOK;
}

int gsm_config(void)
{
   DBG(kLvlVerb, "gsm, initial config");
   
   AtResp resp = new_resp();
   
   if(!gsm_repeat_till_to("AT+CSDH=0", &resp, kGsmAtRespOK, 60000, 2000, 1000))
   {
      DBG(kLvlError, "gsm, could not set SMS mode param");
      return kErrorProtocol;
   }   
   
   if(!gsm_repeat_till_to("AT+CCID=?", &resp, kGsmAtRespOK, 10000, 2000, 500))
   {
      DBG(kLvlError, "gsm, SIM not present");
      return kErrorSim;
   }
   
   const char * cmd = "AT+CPIN?";
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlVerb, cmd, &resp);
      DBG(kLvlError, "gsm, could not get pin status");
      return kErrorProtocol;
   }
   
   gsp_print_resp(kLvlVerb, cmd, &resp);
   
   char pin_state[16];
   const char * line = at_parse_get_first_line(&resp);
   
   if(!at_parse_get_param(line, "+CPIN: ", pin_state, sizeof(pin_state)))
   {
      DBG(kLvlError, "gsm, could not parse SIM status result: %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   if(strcmp(pin_state, "READY") == 0)
   {
      DBG(kLvlInfo, "gsm, pin not required");
   }
   else if(strcmp(pin_state, "SIM PIN") == 0)
   {
      DBG(kLvlInfo, "gsm, pin required");
      
      if(!gsm_cmd("AT+CPIN=\"1234\""))
      {
         DBG(kLvlError, "gsm, could not provide PIN");
         return kErrorSim;
      }
      
      if(!gsm_cmd_resp("AT+CPIN?", &resp) != kGsmAtRespOK)
      {
         DBG(kLvlError, "gsm, could not check PIN");
         return kErrorProtocol;
      }
      
      if(strncmp(at_parse_get_first_line(&resp), "+CPIN: READY", 12) == 0)
      {
         DBG(kLvlInfo, "gsm, PIN set OK");
      }
      else
      {
         DBG(kLvlError, "gsm, PIN set ERROR: %s", &resp.buff[0]);
      }
   }
   else
   {
      DBG(kLvlError, "gsm, unknown pin status %s", pin_state);
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CSQ"))
   {
      DBG(kLvlError, "gsm, could not get signal quality");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CMGF=1"))
   {
      DBG(kLvlError, "gsm, could not set SMS format");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CLIP=1"))
   {
      DBG(kLvlError, "gsm, could not supplementary service");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CNMI=2,1,0,0,0"))
   {
      DBG(kLvlError, "gsm, could not set SMS handling");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CPMS?"))
   {
      DBG(kLvlError, "gsm, could not get SMS memory status");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CPMS=\"ME\",\"ME\",\"ME\""))
   {
      DBG(kLvlError, "gsm, could not set SMS memory dest");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+CFGRI=1"))
   {
      DBG(kLvlError, "gsm, could not set URC RI signal");
      return kErrorProtocol;
   }
   
   return kOK;
}

int gsm_is_network_connected(void)
{
   AtResp resp = new_resp();

   uint8_t gprs_stat = 0xFF;
   
   for(size_t i = 0; i < 3; i++)
   {
      const char *cmd = "AT+CGATT?";
      if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
      {
         gsp_print_resp(kLvlError, cmd, &resp);
         DBG(kLvlError, "could not get GPRS attach status");
         return kErrorProtocol;
      }
      
      gsp_print_resp(kLvlVerb, cmd, &resp);
      
      if(!at_parse_extract_arg(resp.buff, "+CGATT: ", "d", &gprs_stat))
      {
         DBG(kLvlWarn, "could not parse GPRS attach result: %s", &resp.buff[0]);
         timer_delay_ms(1000);
         continue;
      }
      
      break;
   }
   
   if(gprs_stat == 1)
   {
      DBG(kLvlDbg, "gsm, GPRS already connected");
      return kOK;
   }

   return kErrorConnection;
}

int gsm_network_connect(void)
{
   AtResp resp = new_resp();

   if(kOK != gsm_is_network_connected())
   {
      //gsm_cmd_single("AT+CGCLASS=\"B\"");
      //gsm_cmd_single("AT+CGDCONT=1,\"IP\",\"net\"");

      if(!gsm_repeat_till_to("AT+CGATT=1", &resp, kGsmAtRespOK, 20000, 12000, 1000))
      {
         DBG(kLvlWarn, "gsm, problems attaching GPRS service");
         return kErrorProtocol;
      }
      
      //gsm_cmd_single(" AT+CMEE=0");
      
      DBG(kLvlVerb, "gsm, connecting to network...");
      
      const char * cmd = "AT+COPS?";

      for(size_t i = 0; i < 60 * 60; i++)
      {
         timer_delay_ms(1000);

         gsm_cmd("ATE0");

         if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
         {
            gsp_print_resp(kLvlError, cmd, &resp);
            DBG(kLvlError, "gsm, could not get service provider");
            continue;
         }

         gsp_print_resp(kLvlVerb, cmd, &resp);

         if(strncmp(resp.buff, "+COPS: 0" AT_CMD_ENDL, 10) == 0)
         {
            continue;
         }

         cmd = "AT+CSPN?";
         if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
         {
            gsp_print_resp(kLvlVerb, cmd, &resp);
            DBG(kLvlError, "gsm, could not get service provider");
            return kErrorProtocol;
         }

         gsp_print_resp(kLvlVerb, cmd, &resp);

         char network[32];
         if(!at_parse_extract_arg(resp.buff, "+CSPN: ", "s", network))
         {
            DBG(kLvlError, "gsm, could not parse network status %s", &resp.buff[0]);
            return kErrorProtocol;
         }

         DBG(kLvlInfo, "gsm, connected to network %s", &network[0]);

         gsm_cmd("AT+CGREG?");

         break;
      }
   }
   
   return kOK;
}

int gsm_find_apn(const GsmNetworkAPN ** apn)
{
   AtResp resp = new_resp();
   
   const char * cmd = "AT+CSPN?";
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlVerb, cmd, &resp);
      DBG(kLvlError, "gsm, could not get service provider");
      return kErrorProtocol;
   }

   gsp_print_resp(kLvlVerb, cmd, &resp);
         
   char network[32];
   if(!at_parse_extract_arg(resp.buff, "+CSPN: ", "s", network))
   {
      DBG(kLvlError, "gsm, could not parse network status %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   for(size_t i = 0; i < gsm.config->apn_size; i++)
   {
      if(utils_strcasecmp(network, gsm.config->apn[i].name) == 0)
      {
         *apn = &gsm.config->apn[i];
         return kOK;
      }
   }
   
   *apn = &gsm.config->apn[0];
   
   return kOK;
}

int gsm_network_disconnect(void)
{
   AtResp resp = new_resp();
   
   if(!gsm_repeat_till_to("AT+CGATT=0", &resp, kGsmAtRespOK, 10000, 1000, 100))
   {
      DBG(kLvlError, "could not detach GPRS");
      return kErrorProtocol;
   }
   
   return kOK;
}

int gsm_is_pdp_active(void)
{
   AtResp resp = new_resp();

   bool ok = false;
   uint8_t state = 0;

   for(size_t i = 0; i < 3; i++)
   {
      const char *cmd = "AT+CGACT?";
      if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
      {
         gsp_print_resp(kLvlError, cmd, &resp);
         DBG(kLvlError, "could not get PDP status");
         return kErrorProtocol;
      }
      
      gsp_print_resp(kLvlVerb, cmd, &resp);

      if(!at_parse_extract_arg(resp.buff, "+CGACT: ", "d,d", NULL, &state))
      {
         return kErrorConnection;
      }
     
      ok = true;
      break;
   }

   if(!ok)
   {
      DBG(kLvlError, "failed to get PDP status");
      return kErrorConnection;
   }
   
   if(state != 1)
   {
      return kErrorConnection;
   }
   
   const char *cmd = "AT+SAPBR=2,1";
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlWarn, cmd, &resp);
      DBG(kLvlWarn, "could not get IP/GPRS attach status");
   }
   else
   {
      gsp_print_resp(kLvlVerb, cmd, &resp);

      uint8_t gprs_stat;
      if(!at_parse_extract_arg(resp.buff, "+SAPBR: ", "d,d", NULL, &gprs_stat))
      {
         DBG(kLvlWarn, "could not parse IP/GPRS attach result: %s", &resp.buff[0]);
      }
      else
      {
         if(gprs_stat != 1)
         {
            return kErrorConnection;
         } 
      }
   }

   return kOK;
}

int gsm_pdp_activate(const char * apn, const char * user, const char * pass)
{
   DBG(kLvlVerb, "gsm, activating PDP...");
   
   if(kOK == gsm_is_pdp_active())
   {
      return kOK;
   }
   
   char cmd[128];
   if(strlen(apn) >= sizeof(cmd) - 32)
   {
      DBG(kLvlError, "gsm, gsm_set_apn buffer too small");
      return kErrorProtocol;
   }
   
   snprintf(cmd, sizeof(cmd), "AT+CGDCONT=1,\"IP\",\"%s\"", apn);
   if(!gsm_cmd(cmd))
   {
      DBG(kLvlError, "gsm, could not set GPRS APN");
      return kErrorProtocol;
   }
   
   snprintf(cmd, sizeof(cmd), "AT+CSTT=\"%s\",\"%s\",\"%s\"", apn, user, pass);
   if(!gsm_cmd(cmd))
   {
      DBG(kLvlError, "gsm, could not set TCP APN config");
      return kErrorProtocol;
   }
   
   AtResp resp = new_resp();
   const char * inq = "AT+CGACT=1";

   if(send_cmd_to(inq, &resp, 150 * 1000UL) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlError, inq, &resp);
      DBG(kLvlError, "could not activate PDP");
      return kErrorProtocol;
   }

   gsp_print_resp(kLvlVerb, inq, &resp);
   
   snprintf(cmd, sizeof(cmd), "AT+SAPBR=3,1,\"APN\",\"%s\"", apn);
   
   gsm_cmd("AT+SAPBR=3,1,\"Contype\", \"GPRS\"");
   gsm_cmd(cmd);
   
   inq = "AT+SAPBR=1,1";
   if(send_cmd_to(inq, &resp, 85 * 1000UL) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlError, inq, &resp);
      DBG(kLvlError, "could not activate PDP");
      return kErrorProtocol;
   }
   
   DBG(kLvlInfo, "gsm, PDP is activate");
   
   return gsm_is_pdp_active();
}

int gsm_pdp_reactivate(void)
{
   AtResp resp = new_resp();
   
   if(kOK != gsm_is_pdp_active())
   {
      const char * inq = "AT+CGACT=1";

      if(send_cmd_to(inq, &resp, 150 * 1000UL) != kGsmAtRespOK)
      {
         gsp_print_resp(kLvlError, inq, &resp);
         DBG(kLvlError, "could not activate PDP");
         return kErrorProtocol;
      }

      gsp_print_resp(kLvlVerb, inq, &resp);
   }
   
   
   const char * inq = "AT+SAPBR=1,1";
   if(send_cmd_to(inq, &resp, 85 * 1000UL) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlError, inq, &resp);
      DBG(kLvlError, "could not activate PDP");
      return kErrorProtocol;
   }
   
   return kOK;
}

int gsm_pdp_deactivate(void)
{
   gsm_cmd_single("AT+CGATT=0");
   gsm_cmd_single("AT+CIPCLOSE");
   gsm_cmd_single("AT+CIPSHUT");
   gsm_cmd_single("AT+SAPBR=0,1");
   
   return kOK;
}

bool gsm_send_sms(const char *dest, const char *content)
{
   char cmd[48];
   if(strlen(dest) >= sizeof(cmd) - 16)
   {
      DBG(kLvlError, "gsm, gsm_send_sms buffer too small");
      return false;
   }
   
   DBG(kLvlInfo, "gsm, sending SMS to %s: \r\n%s", dest, content);
   
   snprintf(cmd, sizeof(cmd) - 1, "AT+CMGS=\"%s\"", dest);
   cmd[sizeof(cmd) - 1] = 0;
   send_command(cmd);
   
   for(;;)
   {
      char b;
      if(!at_get_rx_char(&b, 2000))
      {
         DBG(kLvlError, "gsm, gsm_send_sms, tag '>' not received");
         return false;
      }
      
      if(b == '>')
         break;
   } 
   
   at_send_data(content, strlen(content));
   at_send_data("\032", 1);
   
   AtResp resp = new_resp();
   if(get_response_to(&resp, 60 * 1000) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlVerb, cmd, &resp);
      DBG(kLvlError, "gsm, gsm_send_sms problems %s", &resp.buff[0]);
      return false;
   }
   
   gsp_print_resp(kLvlVerb, cmd, &resp);
   DBG(kLvlDbg, "gsm, SMS message sent: %s", content);
   
   return true;
}


/*
 * Reads first SMS message from the message group.
 */
static bool read_first_sms(char *src, char *data, size_t size, size_t *index)
{
   uint16_t count = 0;
   memset(data, 0, size);
   
   bool skip = false;
   bool end = false;
   
   const char * tag_cmgl = AT_CMD_ENDL AT_CMD_ENDL "+CMGL:";
   const char * tag_ok = "OK" AT_CMD_ENDL;
   
   size_t tag_cmgl_size = strlen(tag_cmgl);
   size_t tag_ok_size = strlen(tag_ok);
   
   for(;;)
   {
      char b;
      if(!at_get_rx_char(&b, 2 * 1000))
      {
         DBG(kLvlError, "gsm, read_first_sms timeout %s", data);
         return false;
      }
      
      if(count == 0 && (b == '\n' || b == '\r'))
      {
         continue;
      }

      if(count >= size - 1)
      {
         DBG(kLvlError, "gsm, read_first_sms buff too small %u", size);
         return false;
      }
      
      //while(U3STAbits.UTXBF == 1); U3TXREG = b;
      
      data[count++] = b;
      
      if(at_parse_ends_with(data, count, tag_cmgl, tag_cmgl_size))
      {
         count -= tag_cmgl_size;
         data[count] = 0;
         skip = true;
         break;
      }
      
      if(at_parse_ends_with(data, count, tag_ok, tag_ok_size))
      {
         count -= tag_ok_size;
         data[count] = 0;
         end = true;
         break;
      }
   }
   
   while(skip)
   {
      char b;
      if(!at_get_rx_char(&b, 200))
         break;
   }
   
   if(end && count < 10)
   {
      return false;
   }
   
   DBG(kLvlDbg, "gsm, read_first_sms: %s", &data[0]);
   
   uint16_t id;
   if(!at_parse_extract_arg(data, "+CMGL: ", "n,s,s", &id, NULL, src))
   {
      DBG(kLvlError, "gsm, read_first_sms parsing error %s", data);
      return false;
   }
   
   *index = id;
   
   const char *ptr = strstr(data, AT_CMD_ENDL);
   if(ptr == NULL)
   {
      DBG(kLvlError, "gsm, read_first_sms no message content %s", data);
      return false;
   }
   
   ptr += strlen(AT_CMD_ENDL);
   strcpy(data, ptr);
   
   size_t last = strlen(data);
   while(data[last - 1] == '\r' || data[last - 1] == '\n')
   {
      data[last - 1] = 0;
      last--;
   }
   
   DBG(kLvlInfo, "gsm, read_first_sms %u, %s '%s'", *index, src, data);
   
   return true;
}

/*
 * Reads first stored SMS message (read and unread).
 */
bool gsm_read_sms(char *src, char *content, size_t size, size_t *index)
{
   /*size_t dbg_lvl = dbg_get_level();
   dbg_set_level(kLvlWarn);
   send_command("AT+CMGL=0");
   dbg_set_level(dbg_lvl);*/
   
   at_rx_clear();
   send_command("AT+CMGL=\"ALL\", 1");
   
   return read_first_sms(src, content, size, index);
}

bool gsm_delete_sms(size_t index)
{
   char cmd[64];
   snprintf(cmd, sizeof(cmd), "AT+CMGD=%u", index);

   if(!gsm_cmd(cmd))
   {
      DBG(kLvlError, "gsm, cannot delete SMS index %u", index);
      return false;
   }
   
   return true;
}

void gsm_read_urcs(void)
{
   uint8_t b;
   
   while(at_rx_getc(&b))
   {
      // DBGRAW(kLvlVerb, "%c", b);
      
      if(gsm.urc_resp.count == 0 && (b == '\r' || b == '\n'))
         continue;

      gsm.urc_resp.buff[gsm.urc_resp.count++] = b;
      
      if(gsm.urc_resp.count >= gsm.urc_resp.buff_size)
      {
         DBG(kLvlWarn, "gsm, urc buff size too small %u", gsm.urc_resp.buff_size);
         gsm.urc_resp.count = 0;
         memset(gsm.urc_resp.buff, 0, gsm.urc_resp.buff_size);
         break;
      }

      if(b == '\n')
      {
         bool found = false;
         
         // gsp_print_resp(kLvlVerb, "URC", &gsm.urc_resp);
         
         for(size_t i = 0; i < COUNT(at_urc_resp_type); ++i)
         {
            size_t len = strlen(at_urc_resp_type[i].name);
            if(gsm.urc_resp.count >= len)
            {
               if(strncmp(gsm.urc_resp.buff, at_urc_resp_type[i].name, len) == 0)
               {
                  gsm.urc_resp.code = at_urc_resp_type[i].code;
                  found = true;
                  break;
               }
            }
         }
         
         bool send_event = true;
         
         if(found)
         {
            while(at_rx_getc(&b) && b != '\n' && b != '\r' && gsm.urc_resp.count < gsm.urc_resp.buff_size - 1)
            {
               gsm.urc_resp.buff[gsm.urc_resp.count++] = b;
            }
            
            switch(gsm.urc_resp.code)
            {
               case kGsmAtUrcRecvSms:
               {
                  break;
               }
               
               case kGsmAtUrcRing: 
               {                  
                  char nr[24] = {0};
                  if(!at_parse_extract_arg(gsm.urc_resp.buff, "+CLIP: ", "s", nr))
                  {
                     DBG(kLvlError, "gsm, could not parse +CLIP URC %s", gsm.urc_resp.buff);
                     nr[0] = 0;
                  }
                  
                  if(gsm.on_gsm_event)
                     gsm.on_gsm_event(gsm.urc_resp.code, nr);
                  
                  send_event = false;
                  break;
               }
               
               case kGsmAtUrcNoCarrier:
               {
                  //DBG(kLvlInfo, "gsm, call ended");
                  break;
               }
               
               case kGsmAtUrcSmsReady:
               {
                  //DBG(kLvlInfo, "gsm, call ready");
                  gsm_config();
                  break;
               }
               
               case kGsmAtUrcTcpRecv:
               {
                  break;
               }
               
               case kGsmAtUrcTcpDisconnect:
               {
                  break;
               }
               
               case kGsmAtUrcBearerDeact:
               case kGsmAtUrcPdpDeact:
               {
                  break;
               }
               
               default:
               {
                  DBG(kLvlInfo, "gsm, received unknown URC: %s", gsm.urc_resp.buff);
                  break;
               }
            };
            
            if(send_event && gsm.on_gsm_event)
               gsm.on_gsm_event(gsm.urc_resp.code, 0);
         }
         
         gsm.urc_resp.count = 0;
         memset(gsm.urc_resp.buff, 0, gsm.urc_resp.buff_size);
      }
   }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int gsm_ip_init(void)
{
   if(kOK != gsm_is_pdp_active())
   {
      AtResp resp = new_resp();
      const char * inq = "AT+CGACT=1";

      if(send_cmd_to(inq, &resp, 150 * 1000UL) != kGsmAtRespOK)
      {
         gsp_print_resp(kLvlError, inq, &resp);
         DBG(kLvlError, "could not activate PDP");
         return kErrorProtocol;
      }

      gsp_print_resp(kLvlVerb, inq, &resp);
   }
   
   AtResp resp = new_resp();
   
   const char *cmd = "AT+SAPBR=2,1";
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlWarn, cmd, &resp);
      DBG(kLvlWarn, "could not get IP/GPRS attach status");
      gsm_cmd("AT+SAPBR=1,1");
   }
   else
   {
      gsp_print_resp(kLvlVerb, cmd, &resp);

      uint8_t gprs_stat;
      if(!at_parse_extract_arg(resp.buff, "+SAPBR: ", "d,d", NULL, &gprs_stat))
      {
         DBG(kLvlWarn, "could not parse IP/GPRS attach result: %s", &resp.buff[0]);
         gsm_cmd("AT+SAPBR=1,1");
      }
      else
      {
         if(gprs_stat != 1)
         {
            gsm_cmd_single("AT+CIPSHUT");
            
            cmd = "AT+SAPBR=1,1";
            if(send_cmd_to(cmd, &resp, 85 * 1000UL) != kGsmAtRespOK)
            {
               gsp_print_resp(kLvlError, cmd, &resp);
               DBG(kLvlError, "could not activate PDP");
            }
            
            gsm_cmd_single("AT+SAPBR=2,1");
         }
      }
   }
   
   gsm_cmd_single("AT+HTTPINIT");
   gsm_cmd_single("AT+CIICR");
   gsm_cmd_single("AT+CIFSR");
   
   return kOK;
}


static int http_action(const char * action, void * data, size_t * dest_size, size_t * http_code)
{
   if(!gsm_cmd("AT+HTTPPARA=\"CID\",1"))
   {
      DBG(kLvlError, "gsm, could not set HTTP CID");
      return kErrorProtocol;
   }
   
   if(!gsm_cmd("AT+HTTPPARA=\"REDIR\",1"))
   {
      DBG(kLvlError, "gsm, could not set HTTP REDIR");
      return kErrorProtocol;
   }
   
   const char * head = "AT+HTTPACTION=";
   const char * foot = "";
   
   if(!gsm_param_cmd(head, action, foot))
   {
      DBG(kLvlError, "gsm, could not set HTTP URL");
      return kErrorProtocol;
   }
   
   AtResp resp = new_resp();
   
   if(get_response_to(&resp, 60 * 1000) != kGsmAtRespHttpAct)
   {
      gsp_print_resp_param(kLvlError, head, action, foot, &resp);
      DBG(kLvlError, "gsm, HTTP GET problems %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   gsp_print_resp_param(kLvlVerb, head, action, foot, &resp);
   
   uint8_t status;
   uint32_t code;
   uint32_t data_len;
   
   if(!at_parse_extract_arg(resp.buff, "+HTTPACTION: ", "d,N,N", &status, &code, &data_len))
   {
      DBG(kLvlError, "gsm, could not parse HTTP ACTION result: %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   if(data_len > *dest_size)
   {
      DBG(kLvlError, "gsm, HTTP payload too large %u vs %u", data_len, *dest_size);
      return kErrorSize;
   }
   
   *http_code = (size_t)code;
   *dest_size = (size_t)data_len;
   
   if(data_len == 0)
   {
      return kOK;
   }
   
   const char * cmd = "AT+HTTPREAD";
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespHttpRead)
   {
      gsp_print_resp(kLvlError, cmd, &resp);
      DBG(kLvlError, "gsm, could not invoke HTTP READ");
      return kErrorProtocol;
   }
   
   // gsp_print_resp(kLvlVerb, cmd, &resp);

   if(!at_parse_extract_arg(resp.buff, "+HTTPREAD: ", "N", NULL, &data_len))
   {
      gsp_print_resp(kLvlError, cmd, &resp);
      DBG(kLvlError, "gsm, could extract HTTP READ");
      return kErrorProtocol;
   }
   
   uint8_t * ptr = data;
   
   for(; data_len; data_len--)
   {
      char b;
      if(!at_get_rx_char(&b, 2 * 1000))
      {
         DBG(kLvlError, "gsm, HTTP READ timeout %s", data);
         return kErrorProtocol;
      }
      
      *ptr++ = b;
   }
   
   if(get_response_to(&resp, 1000) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlError, cmd, &resp);
      DBG(kLvlError, "gsm, HTTP READ problems 2 %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   return kOK;
}


int gsm_http_get(const char * url, void * data, size_t * dest_size, size_t * http_code)
{
   const char * head = "AT+HTTPPARA=\"URL\",\"";
   const char * foot = "\"";
   
   if(!gsm_param_cmd(head, url, foot))
   {
      DBG(kLvlError, "gsm, could not set HTTP URL");
      return kErrorProtocol;
   }
   
   return http_action("0", data, dest_size, http_code);
}


int gsm_http_post(const char * url, const void * send_data, size_t send_data_size, void * recv_data, size_t * recv_data_size, size_t * http_code)
{
   const char * head = "AT+HTTPPARA=\"URL\",\"";
   const char * foot = "\"";
   
   if(!gsm_param_cmd(head, url, foot))
   {
      DBG(kLvlError, "gsm, could not set HTTP URL");
      return kErrorProtocol;
   }
   
   AtResp resp = new_resp();
   
   char cmd_buff[32];
   snprintf(cmd_buff, sizeof(cmd_buff), "AT+HTTPDATA=%u,10000", send_data_size);
   
   if(gsm_cmd_resp(cmd_buff, &resp) != kGsmAtRespHttpDownload)
   {
      gsp_print_resp(kLvlError, cmd_buff, &resp);
      DBG(kLvlError, "gsm, could download HTTP POST data");
      return kErrorProtocol;
   }
   
   at_send_data(send_data, send_data_size);
   
   if(get_response_to(&resp, 1000) != kGsmAtRespOK)
   {
      gsp_print_resp(kLvlError, cmd_buff, &resp);
      DBG(kLvlError, "gsm, HTTP POST problems 2 %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   return http_action("1", recv_data, recv_data_size, http_code);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int gsm_tcp_connect(const char * host, size_t port)
{
   gsm_tcp_disconnect();
   
   const char * head = "AT+CIPSTART=\"TCP\",\"";
   
   char foot[24];
   snprintf(foot, sizeof(foot), "\",%u", port);
   
   if(!gsm_param_cmd(head, host, foot))
   {
      DBG(kLvlError, "gsm, could not setup TCP connection");
      return kErrorProtocol;
   }

   AtResp resp = new_resp();
   
   if(get_response_to(&resp, 30 * 1000) != kGsmAtRespTcpConnected)
   {
      gsp_print_resp_param(kLvlVerb, head, host, foot, &resp);
      DBG(kLvlVerb, "gsm, TCP connection failed %u", resp.code);
      gsm_cmd_single("AT+CIPCLOSE");
      return kErrorProtocol;
   }
   
   return kOK;
}

int gsm_tcp_is_connected(void)
{
   if(!gsm_cmd("AT+CIPSTATUS"))
   {
      return kErrorConnection;
   }
   
   AtResp resp = new_resp();
   
   int code = get_response(&resp);
   if(code != kGsmAtRespTcpState)
   {
      return kErrorProtocol;
   }
   
   gsp_print_resp(kLvlVerb, "AT+CIPSTATUS", &resp);
   
   if(strcmp(resp.buff, "STATE: CONNECT OK" AT_CMD_ENDL) == 0)
   {
      return kOK;
   }
   
   return kErrorConnection;
}

static int internal_gsm_tcp_send(const void * data, size_t data_size)
{
   char cmd[32];
   snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%u", data_size);
   
   DBG(kLvlDbg, "gsm, cmd %s", cmd);
   send_command(cmd);
   
   for(;;)
   {
      char b;
      if(!at_get_rx_char(&b, 2000))
      {
         DBG(kLvlError, "gsm, TCP send, tag '>' not received");
         return kErrorProtocol;
      }
      
      if(b == '>')
         break;
   } 
   
   at_send_data(data, data_size);
   
   AtResp resp = new_resp();
   
   for(size_t i = 0; i < 2; i++)
   {
      get_response_to(&resp, 10 * 1000);
      
      if(resp.code == kGsmAtRespTcpRecv)
         continue;
      
      if(resp.code != kGsmAtRespTcpSend)
      {
         gsp_print_resp(kLvlVerb, cmd, &resp);
         DBG(kLvlError, "gsm, TCP send problems %s", &resp.buff[0]);
         return kErrorProtocol;
      }
      
      break;
   }
   
   return kOK;
}

int gsm_tcp_send(const void * data, size_t data_size)
{
   const uint8_t * ptr = data;
   
   while(data_size)
   {
      size_t to_send = data_size;
      
      if(to_send > 1460)
         to_send = 1460;
      
      int ret = internal_gsm_tcp_send(ptr, to_send);
      if(kOK != ret)
      {
         return ret;
      }
      
      data_size -= to_send;
      ptr += to_send;
   }
   
   return kOK;
}


static int internal_gsm_tcp_read(void * recv_data, size_t to_read, size_t * actual_read, size_t * remaining)
{
   char cmd[64];
   snprintf(cmd, sizeof(cmd), "AT+CIPRXGET=2,%u", to_read);
   
   memset(recv_data, 0, to_read);
        
   uint8_t * data = recv_data;
   
   AtResp resp = new_resp();
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespTcpRecv)
   {
      gsp_print_resp(kLvlError, cmd, &resp);
      DBG(kLvlError, "gsm, TCP send problems %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   uint32_t read;
   uint32_t rmng;
   
   const char * ptr = resp.buff;
   if(strncmp(resp.buff, "+CIPRXGET: 1", 12) == 0)
   {
      ptr = at_parse_get_next_line(&resp);
   }
   
   if(!at_parse_extract_arg(ptr, "+CIPRXGET: ", "d,N,N", NULL, &read, &rmng))
   {
      DBG(kLvlError, "gsm, TCP read parsing error %s", resp.buff);
      return kErrorProtocol;
   }
   
   //gsp_print_resp(kLvlDbg, cmd, &resp);
   
   if(actual_read)
      *actual_read = (size_t) read;
   
   if(remaining)
      *remaining = (size_t) rmng;
   
   while(read)
   {
      char b;
      if(!at_get_rx_char(&b, 200))
      {
         DBG(kLvlError, "gsm, TCP read timeout %s", data);
         return kErrorProtocol;
      }
      
      read--;
      *data++ = b;
   }
   
   if(get_response(&resp) != kGsmAtRespOK)
   {
      DBG(kLvlWarn, "gsm, TCP read OK timeout %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   return kOK;
}

int gsm_tcp_read(void * recv_data, size_t to_read, size_t * actual_read, size_t * remaining)
{
   uint8_t * ptr = recv_data;
   size_t count = 0;
   
   do
   {
      size_t to_read_count = to_read;
      if(to_read_count > 1460)
         to_read_count = 1460;
      
      int ret = internal_gsm_tcp_read(ptr, to_read_count, actual_read, remaining);
      if(kOK != ret)
      {
         return ret;
      }
      
      ptr += *actual_read;
      count += *actual_read;
      
   } while (*remaining != 0 && count < to_read);
   
   *actual_read = count;
   
   return kOK;
}

int gsm_tcp_wait_recv(uint32_t timeout)
{
   const char  * cmd = "AT+CIPRXGET=4";
   
   AtResp resp = new_resp();
   if(gsm_cmd_resp(cmd, &resp) != kGsmAtRespTcpRecv)
   {
      gsp_print_resp(kLvlError, cmd, &resp);
      DBG(kLvlError, "gsm, TCP query recv size failed %s", &resp.buff[0]);
      return kErrorProtocol;
   }
   
   uint32_t rem;
   
   if(!at_parse_extract_arg(resp.buff, "+CIPRXGET: ", "d,N", NULL, &rem))
   {
      DBG(kLvlError, "gsm, TCP query recv parsing error %s", resp.buff);
      return kErrorProtocol;
   }
   
   // gsp_print_resp(kLvlVerb, cmd, &resp);
   
   get_response(&resp);
   
   if(rem > 0)
      return kOK;
   
   if(get_response_to(&resp, timeout) != kGsmAtRespTcpRecv)
   {
      return kErrorTimeout;
   }
   
   return kOK;
}

int gsm_tcp_disconnect(void)
{
   gsm_cmd_single("AT+CIPCLOSE");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void gsm_service(void)
{
   if(at_rx_error())
   {
      DBG(kLvlError, "gsm, AT RX buffer size error ");
   }
   
   gsm_read_urcs();
}
