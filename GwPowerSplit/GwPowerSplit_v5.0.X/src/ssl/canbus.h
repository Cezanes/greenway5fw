#ifndef CAN_H
#define CAN_H


typedef struct
{
   uint8_t phaseSeg2Tq;
   uint8_t phaseSeg1Tq;
   uint8_t propagationSegTq;
   bool phaseSeg2TimeSelect;
   bool sample3Time;
   uint8_t syncJumpWidth;
   uint32_t sys_clock;
   uint32_t can_baud;
} CanBusClock;

typedef struct
{
   uint32_t id;
   size_t size;
   uint32_t data[2];
} CanMsg;

typedef struct
{
   CanBusClock clock;
   uint32_t mode_timeout;
   void (*on_recv_msg)(const CanMsg * msg);
} CanBusConfig;


void can_init(const CanBusConfig * config);
bool can_send(uint32_t id, const void * data, size_t size);
bool can_send_msg(const CanMsg * msg);
bool can_send_full(void);
bool can_send_empty(void);
bool can_recv(CanMsg * msg);
bool can_recv_full(void);
bool can_recv_empty(void);
bool can_recv_overflow(void);
void can_service(void);



#endif