#include <sys/attribs.h>

#include "server.h"
#include "slink.h"

#include "sal/debug.h"
#include "hal/sys.h"
#include "hal/uart32mx.h"

#include "mcc_generated_files/uart2.h"

enum
{
   kSrvErrorBufferAlreadyTaken    = 1 << 0,
   kSrvErrorBufferReleaseUnknown  = 1 << 1,
   kSrvErrorBufferReleaseMismatch = 1 << 2,
   kSrvErrorRboe                  = 1 << 3,
   
   kSrvInfoBufferTaken            = 1 << 10,
   kSrvInfoBufferReleased         = 1 << 11,
};


typedef struct
{
   size_t id;
   size_t endp;
   SeMsgCallback cb;
   size_t itf;
} MsgHandler;

static struct
{
   ServerConfig config;
   size_t handler_count;
   MsgHandler handlers[SERVER_CALLBACKS_MAX];   

   size_t errors;
   const SlinkInstance * buff_own_inst;

} srv;


static SlinkInstance slink_inst[2];


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void server_send_byte(void* user, uint8_t b);
static void server_recv_byte(void* user, uint8_t b);
static void server_uart_rboe(void* user);
static void server_enable_int(void);
static void server_disable_int(void);
static bool server_req_buffer(void* user);
static void server_rel_buffer(void* user);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void server_init(const ServerConfig * config)
{
   srv.config = *config;
   
   if (COUNT(slink_inst) < srv.config.socket_count)
   {
      DBG(kLvlError, "server, not enough sockets slots.");
      return;
   }
   
   for(size_t i = 0; i < srv.config.socket_count; i++)
   {
      slink_inst[i] = (SlinkInstance) {
         .user = (void*)&srv.config.sockets[i],
         .own_buff = srv.config.sockets[i].own_buff,
         .rx_buff = srv.config.sockets[i].rx_buff,
         .rx_size = srv.config.sockets[i].rx_buff_size,
         .send_byte = &server_send_byte,
         .enable_int = &server_enable_int,
         .disable_int = &server_disable_int,
         .req_buffer = &server_req_buffer,
         .rel_buffer = &server_rel_buffer,
      };
   
      srv.config.sockets[i].uart->init(srv.config.sockets[i].uart->lcb, &slink_inst[i], srv.config.sockets[i].clock_src, srv.config.sockets[i].baud);
      srv.config.sockets[i].uart->set_isr(srv.config.sockets[i].uart->lcb, &server_recv_byte);
      srv.config.sockets[i].uart->set_rboe(srv.config.sockets[i].uart->lcb, &server_uart_rboe);
      srv.config.sockets[i].uart->enable_isr(srv.config.sockets[i].uart->lcb, true);
      
      
      slink_init(&slink_inst[i]);
   }
}

static void server_recv_byte(void* user, uint8_t b)
{
   SlinkInstance * inst = user;
   slink_recv_byte(inst, b);
}

static void server_uart_rboe(void* user)
{
   srv.errors |= kSrvErrorRboe;
}

static bool server_req_buffer(void* user)
{
   SlinkInstance * inst = user;
   
   if (inst->own_buff)
      return true;
   
   if (srv.buff_own_inst == NULL || srv.buff_own_inst == inst)
   {
      srv.errors |= kSrvInfoBufferTaken;
      srv.buff_own_inst = inst;
      inst->rx_buff = srv.config.shared_rx_buff;
      inst->rx_size = srv.config.shared_rx_buff_size;
      return true;
   }
   
   srv.errors |= kSrvErrorBufferAlreadyTaken;
   
   return false;
}

static void server_rel_buffer(void* user)
{
   SlinkInstance * inst = user;
   
   if (inst->own_buff)
      return;
   
   inst->rx_buff = NULL;
   inst->rx_size = 0;
   
   if (srv.buff_own_inst == NULL)
   {
      srv.errors |= kSrvErrorBufferReleaseUnknown;
   }
   else if (srv.buff_own_inst != inst)
   {
      srv.errors |= kSrvErrorBufferReleaseMismatch;
   }
   else
   {
      srv.errors |= kSrvInfoBufferReleased;
      srv.buff_own_inst = NULL;
   }
}

size_t server_rx_buff_size(void)
{
   return srv.config.shared_rx_buff_size;
}

void server_start(void)
{
   for(size_t i = 0; i < srv.config.socket_count; i++)
   {
      slink_start(&slink_inst[i]);
   }
}

static void server_send_byte(void* user, uint8_t b)
{
   const SocketConfig * socket = user;
   socket->uart->write(socket->uart->lcb, b);
}

static void server_enable_int(void)
{
   sys_enable_ints();
}

static void server_disable_int(void)
{
   sys_disable_ints();
}

void server_add_handler(size_t itf, size_t id, size_t endp, SeMsgCallback cb)
{
   if(srv.handler_count >= SERVER_CALLBACKS_MAX)
   {
      DBG(kLvlError, "server, unable to add new message handlers.");
      return;
   }
   
   srv.handlers[srv.handler_count] = (MsgHandler) {
      .id = id, 
      .endp = endp,
      .cb = cb, 
      .itf = itf
   };
   
   srv.handler_count++;
}

void server_send_msg(size_t itf, SeMsgHead * msg)
{
   if (itf == 0)
      itf = -1;
   
   size_t mask = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, mask <<= 1)
   {
      if (mask & itf)
      {
         slink_send_msg(&slink_inst[i], msg);
      }
   }
}

void server_send(size_t itf, const void* msg, size_t size, size_t id, size_t endp)
{
   if (itf == 0)
      itf = -1;
   
   size_t mask = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, mask <<= 1)
   {
      if (mask & itf)
      {
         slink_send(&slink_inst[i], msg, size, id, endp);
      }
   }
}

void server_begin_send_msg(size_t itf, SeMsgHead *header, size_t size)
{
   if (itf == 0)
      itf = -1;
   
   size_t mask = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, mask <<= 1)
   {
      if (mask & itf)
      {
         srv.config.data_crc_per_itf[i] = slink_begin_send_msg(&slink_inst[i], header, size);
      }
   }
}

void server_continue_data_msg(size_t itf, const void * ptr, size_t size)
{
   if (itf == 0)
      itf = -1;
 
   size_t mask = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, mask <<= 1)
   {
      if (mask & itf)
      {
         srv.config.data_crc_per_itf[i] = slink_continue_data_msg(&slink_inst[i], ptr, size, srv.config.data_crc_per_itf[i]);
      }
   }
}

void server_finalize_msg(size_t itf)
{
   if (itf == 0)
      itf = -1;
   
   size_t mask = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, mask <<= 1)
   {
      if (mask & itf)
      {
         slink_finalize_msg(&slink_inst[i], srv.config.data_crc_per_itf[i]);
      }
   }
}

static void send_unknown(size_t itf, const uint16_t type)
{
   SeMsgUnknown msg = {
      .head = {
         .id = kMsgSlinkNotSupported,
         .size = sizeof(SeMsgUnknown),
      },
      .unknown_msg = type,
   };
   
   server_send_msg(itf, &msg.head);
}

static void server_dispatch(size_t itf, SlinkInstance * inst, const SeMsgHead * msg)
{
   bool found = false;
   
   for(size_t i = 0; i < srv.handler_count; i++)
   {
      size_t this_itf = srv.handlers[i].itf;
      if (this_itf == 0)
         this_itf = -1;
         
      if ((this_itf & itf) > 0 && (srv.handlers[i].endp == msg->endp) && (srv.handlers[i].id == msg->id))
      {
         DBG(kLvlVerb, "server, handling message %4X, ep %u", msg->id, msg->endp);
         (*srv.handlers[i].cb)(itf, msg + 1, msg->size - sizeof(SeMsgHead));
         found = true;
         break;
      }
   }

   slink_discard(inst); 
   
   if (!found)
   {
      DBG(kLvlWarn, "server, unknown message type %4X, ep %u", msg->id, msg->endp);
      send_unknown(itf, msg->id);
   }
}

void server_service(void)
{
   size_t itf = 1;
   for(size_t i = 0; i < srv.config.socket_count; i++, itf <<= 1)
   {
      if(slink_have_msg(&slink_inst[i]))
      {
         const SeMsgHead * msg = slink_receive(&slink_inst[i]);
         server_dispatch(itf, &slink_inst[i], msg);
      }
      
      slink_service(&slink_inst[i]);
   }
   
   if (srv.errors)
   {
      if (srv.errors & kSrvErrorBufferAlreadyTaken)
      {
         srv.errors -= kSrvErrorBufferAlreadyTaken;
         DBG(kLvlWarn, "server, shared buffer already taken");
      }
      if (srv.errors & kSrvErrorBufferReleaseUnknown)
      {
         srv.errors -= kSrvErrorBufferReleaseUnknown;
         DBG(kLvlWarn, "server, shared buffer invalid release, no prev ownership");
      }
      if (srv.errors & kSrvErrorBufferReleaseMismatch)
      {
         srv.errors -= kSrvErrorBufferReleaseMismatch;
         DBG(kLvlWarn, "server, shared buffer mismatch release");
      }
      if (srv.errors & kSrvInfoBufferTaken)
      {
         srv.errors -= kSrvInfoBufferTaken;
         //DBG(kLvlWarn, "server, shared buffer taken");
      }
      if (srv.errors & kSrvInfoBufferReleased)
      {
         srv.errors -= kSrvInfoBufferReleased;
         //DBG(kLvlWarn, "server, shared buffer released");
      }
      if (srv.errors & kSrvErrorRboe)
      {
         srv.errors -= kSrvErrorRboe;
         DBG(kLvlWarn, "server, uart receive buffer overrun error");
      }
   }
}
