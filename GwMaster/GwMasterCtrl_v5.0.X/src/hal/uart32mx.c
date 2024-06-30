#include "uart32mx.h"
#include "types.h"

#include "sal/debug.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct
{
   __U1MODEbits_t mode;
   uint32_t mode_clr;
   uint32_t mode_set;
   uint32_t mode_inv;
   
   __U1STAbits_t sta;
   uint32_t sta_clr;
   uint32_t sta_set;
   uint32_t sta_inv;
   
   uint32_t txreg;
   uint32_t txreg_clr;
   uint32_t txreg_set;
   uint32_t txreg_inv;
   
   uint32_t rxreg;
   uint32_t rxreg_clr;
   uint32_t rxreg_set;
   uint32_t rxreg_inv;
   
   uint32_t brg;
   uint32_t brg_clr;
   uint32_t brg_set;
   uint32_t brg_inv;
   
} Pic32MxUartRegType;


typedef struct
{
   void *user;
   void(*on_rx)(void*, uint8_t);
   void(*on_rboe)(void*);
   volatile Pic32MxUartRegType * uart_reg;
} UartInstance;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void uart_init(void * lcb, void * user, uint32_t clock_src, uint32_t baud);
static uint8_t uart_read(void * lcb);
static void uart_write(void * lcb, uint8_t b);
static void uart_set_isr(void * lcb, void(*on_rx)(void*, uint8_t));
static void uart_set_rboe(void * lcb, void(*on_rboe)(void *));
static bool uart_available(void * lcb);
static void uart_enable_isr(void * lcb, bool on);
static void uart_close(void * lcb);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


static UartInstance uart_config[] = 
{
   {.uart_reg = (Pic32MxUartRegType*)&U1MODE},
   {.uart_reg = (Pic32MxUartRegType*)&U2MODE},
   {.uart_reg = (Pic32MxUartRegType*)&U3MODE},
   {.uart_reg = (Pic32MxUartRegType*)&U4MODE},
   {.uart_reg = (Pic32MxUartRegType*)&U5MODE},
};


UartDev Uart[5] = 
{
   {
      .lcb = &uart_config[0],
      .init = uart_init,
      .read = uart_read,
      .write = uart_write,
      .available = uart_available,
      .enable_isr = uart_enable_isr,
      .set_isr = uart_set_isr,
      .set_rboe = uart_set_rboe,
      .close = uart_close,
   },
   {
      .lcb = &uart_config[1],
      .init = uart_init,
      .read = uart_read,
      .write = uart_write,
      .available = uart_available,
      .enable_isr = uart_enable_isr,
      .set_isr = uart_set_isr,
      .set_rboe = uart_set_rboe,
      .close = uart_close,
   },
   {
      .lcb = &uart_config[2],
      .init = uart_init,
      .read = uart_read,
      .write = uart_write,
      .available = uart_available,
      .enable_isr = uart_enable_isr,
      .set_isr = uart_set_isr,
      .set_rboe = uart_set_rboe,
      .close = uart_close,
   },
   {
      .lcb = &uart_config[3],
      .init = uart_init,
      .read = uart_read,
      .write = uart_write,
      .available = uart_available,
      .enable_isr = uart_enable_isr,
      .set_isr = uart_set_isr,
      .set_rboe = uart_set_rboe,
      .close = uart_close,
   },
   {
      .lcb = &uart_config[4],
      .init = uart_init,
      .read = uart_read,
      .write = uart_write,
      .available = uart_available,
      .enable_isr = uart_enable_isr,
      .set_isr = uart_set_isr,
      .set_rboe = uart_set_rboe,
      .close = uart_close,
   },
};


//////////////////////////////////////////////////////////////////////////////////////////////////


static void uart_init(void * lcb, void * user, uint32_t clock_src, uint32_t baud)
{
   UartInstance * uart = lcb;
   uart->user = user;
   
   uart->uart_reg->mode.UARTEN = 1;
   uart->uart_reg->sta.URXEN = 1;
   uart->uart_reg->sta.UTXEN = 1;
   uart->uart_reg->mode.BRGH = 1;
   
   uart->uart_reg->brg = clock_src / 4 / baud - 1;
};

static uint8_t uart_read(void * lcb)
{
   const UartInstance * uart = lcb;
   
   while(!(uart->uart_reg->sta.URXDA == 1))
   {

   }

   if ((uart->uart_reg->sta.OERR == 1))
   {
       uart->uart_reg->sta.OERR = 0;
       if(uart->on_rboe)
          uart->on_rboe(uart->user);
   }

   return uart->uart_reg->rxreg;
}

static void uart_write(void * lcb, uint8_t b)
{
   const UartInstance * uart = lcb;
   
   while(uart->uart_reg->sta.UTXBF > 0);
   uart->uart_reg->txreg = b;
}

static bool uart_available(void * lcb)
{
   const UartInstance * uart = lcb;
   return uart->uart_reg->sta.URXDA > 1;
}

static void uart_enable_isr(void * lcb, bool on)
{
   const UartInstance * uart = lcb;
   int set = on ? 1 : 0;
   
   if(uart->uart_reg == uart_config[0].uart_reg)
   {
      IPC7bits.U1IP = 6;
      IPC7bits.U1IS = 0;
      IEC1bits.U1RXIE = set;
   }
   else if(uart->uart_reg == uart_config[1].uart_reg)
   {
      IPC9bits.U2IP = 6;
      IPC9bits.U2IS = 0;
      IEC1bits.U2RXIE = set;
   }
   else if(uart->uart_reg == uart_config[2].uart_reg)
   {
      IPC9bits.U3IP = 6;
      IPC9bits.U3IS = 0;
      IEC1bits.U3RXIE = set;
   }
   else if(uart->uart_reg == uart_config[3].uart_reg)
   {
      IPC9bits.U4IP = 6;
      IPC9bits.U4IS = 0;
      IEC2bits.U4RXIE = set;
   }
   else if(uart->uart_reg == uart_config[4].uart_reg)
   {
      IPC10bits.U5IP = 6;
      IPC10bits.U5IS = 0;
      IEC2bits.U5RXIE = set;
   }
}

static void uart_set_isr(void * lcb, void(*on_rx)(void*, uint8_t))
{
   UartInstance * uart = lcb;
   uart->on_rx = on_rx;
}

static void uart_set_rboe(void * lcb, void(*on_rboe)(void*))
{
   UartInstance * uart = lcb;
   uart->on_rboe = on_rboe;
}

static void uart_close(void * lcb)
{
   UartInstance * uart = lcb;
   uart_enable_isr(lcb, false);
   uart->uart_reg->sta.URXEN = 0;
   uart->uart_reg->sta.UTXEN = 0;
   uart->uart_reg->mode.UARTEN = 0;
}

void __ISR(_UART_1_VECTOR, IPL6AUTO) _UART_1 ( void )
{ 
   if(IFS1bits.U1RXIF)
   {
      while((U1STAbits.URXDA == 1))
      {
           uint8_t b = U1RXREG;
           if (uart_config[0].on_rx)
               uart_config[0].on_rx(uart_config[0].user, b);
      }

      IFS1CLR = 1 << _IFS1_U1RXIF_POSITION;
   }
   else if (IFS1bits.U1TXIF)
   {
      IFS1CLR = 1 << _IFS1_U1TXIF_POSITION;
   }
   
   if ((U1STAbits.OERR == 1))
   {
      U1STAbits.OERR = 0;
      if(uart_config[0].on_rboe)
         uart_config[0].on_rboe(uart_config[0].user);
   }

   IFS1CLR = 1 << _IFS1_U1EIF_POSITION;
}

void __ISR(_UART_2_VECTOR, IPL6AUTO) _UART_2 ( void )
{ 
   if(IFS1bits.U2RXIF)
   {
      while((U2STAbits.URXDA == 1))
      {
           uint8_t b = U2RXREG;
           
           uart_config[1].uart_reg->txreg = b;
           
           if (uart_config[1].on_rx)
               uart_config[1].on_rx(uart_config[1].user, b);
      }

      IFS1CLR = 1 << _IFS1_U2RXIF_POSITION;
   }
   else if (IFS1bits.U2TXIF)
   {
      IFS1CLR = 1 << _IFS1_U2TXIF_POSITION;
   }
   
   if ((U2STAbits.OERR == 1))
   {
      U2STAbits.OERR = 0;
      if(uart_config[1].on_rboe)
         uart_config[1].on_rboe(uart_config[1].user);
   }

   IFS1CLR = 1 << _IFS1_U2EIF_POSITION;
}

void __ISR(_UART_3_VECTOR, IPL6AUTO) _UART_3 ( void )
{ 
   if(IFS1bits.U3RXIF)
   {
      while((U3STAbits.URXDA == 1))
      {
           uint8_t b = U3RXREG;
           if (uart_config[2].on_rx)
               uart_config[2].on_rx(uart_config[2].user, b);
      }

      IFS1CLR = 1 << _IFS1_U3RXIF_POSITION;
   }
   else if (IFS2bits.U3TXIF)
   {
      IFS2CLR = 1 << _IFS2_U3TXIF_POSITION;
   }
   
   if ((U3STAbits.OERR == 1))
   {
      U3STAbits.OERR = 0;
      if(uart_config[2].on_rboe)
         uart_config[2].on_rboe(uart_config[2].user);
   }

   IFS1CLR = 1 << _IFS1_U3EIF_POSITION;
}

void __ISR(_UART_4_VECTOR, IPL6AUTO) _UART_4 ( void )
{ 
   if(IFS2bits.U4RXIF)
   {
      while((U4STAbits.URXDA == 1))
      {
           uint8_t b = U4RXREG;
           if (uart_config[3].on_rx)
               uart_config[3].on_rx(uart_config[3].user, b);
      }

      IFS2CLR = 1 << _IFS2_U4RXIF_POSITION;
   }
   else if (IFS2bits.U4TXIF)
   {
      IFS2CLR = 1 << _IFS2_U4TXIF_POSITION;
   }
   
   if ((U4STAbits.OERR == 1))
   {
      U4STAbits.OERR = 0;
      if(uart_config[3].on_rboe)
         uart_config[3].on_rboe(uart_config[3].user);
   }

   IFS2CLR = 1 << _IFS2_U4EIF_POSITION;
}


void __ISR(_UART_5_VECTOR, IPL6AUTO) _UART_5 ( void )
{ 
   if(IFS2bits.U5RXIF)
   {
      while((U5STAbits.URXDA == 1))
      {
           uint8_t b = U5RXREG;
           if (uart_config[4].on_rx)
               uart_config[4].on_rx(uart_config[4].user, b);
      }

      IFS2CLR = 1 << _IFS2_U5RXIF_POSITION;
   }
   else if (IFS2bits.U5TXIF)
   {
      IFS2CLR = 1 << _IFS2_U5TXIF_POSITION;
   }
   
   if ((U5STAbits.OERR == 1))
   {
      U5STAbits.OERR = 0;
      if(uart_config[4].on_rboe)
         uart_config[4].on_rboe(uart_config[4].user);
   }

   IFS2CLR = 1 << _IFS2_U5EIF_POSITION;
}