#include "rfm95.h"
#include "sal/debug.h"
#include "sal/timer.h"

#define RFM95_SPI_WRITE_MASK        0x80

#define RFM95_DELAY_MS(x)  timer_delay_ms(x + 1)
#define ATOMIC_BLOCK_START
#define ATOMIC_BLOCK_END
#define RH_HAVE_SERIAL 

static struct 
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   volatile uint32_t * volatile int_reg;
   
   uint32_t ss_mask;
   uint32_t int_mask;
   
   bool int_sig;

   uint8_t (* spi_xfer)(uint8_t);
   void (*on_recv)(const uint8_t *, uint32_t size, uint8_t rssi);
   void (*on_recv_to)(void);
   void (*on_recv_crc_err)(void);
   void (*on_sent)(void);
} rfm;

typedef enum
{
   RHModeSleep = 0,        ///< Transport hardware is in low power sleep mode (if supported)
   RHModeIdle,             ///< Transport is idle.
   RHModeFsTx,
   RHModeTx,               ///< Transport is in the process of transmitting a message.
   RHModeFsRx,
   RHModeRx,               ///< Transport is in the process of receiving a message.
   RHModeRxSingle,
   RHModeCad               ///< Transport is in the process of detecting channel activity (if supported)
} RHMode;

const char * mode_str[] = 
{
   "Sleep", "Idle", "FsTx", "Tx", "FsRx", "Rx", "RxSingle", "Cad",
};

volatile RHMode     _mode;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

static uint8_t rfm95_read_reg(uint8_t reg);
static void rfm95_write_reg(uint8_t reg, uint8_t val);

////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool rfm95_init(const Rfm95Config * const config)
{
   rfm.ss_reg_set = config->ss_reg_set;
   rfm.ss_reg_clear = config->ss_reg_clear;
   rfm.int_reg = config->int_reg;
   rfm.ss_mask = config->ss_mask;
   rfm.int_mask = config->int_mask;
   rfm.spi_xfer = config->spi_xfer;
      
   rfm.on_recv = config->on_recv;
   rfm.on_recv_to = config->on_recv_to;
   rfm.on_recv_crc_err = config->on_recv_crc_err;
   rfm.on_sent = config->on_sent;
   
   *rfm.ss_reg_set = rfm.ss_mask;

   return true;
}

static uint8_t rfm95_read_reg(uint8_t reg)
{
   *rfm.ss_reg_clear = rfm.ss_mask;
   
   (*rfm.spi_xfer)(reg &~ RFM95_SPI_WRITE_MASK);
   uint8_t res = (*rfm.spi_xfer)(0);
   
   *rfm.ss_reg_set = rfm.ss_mask;
   
   return res;
}

static void rfm95_write_reg(uint8_t reg, uint8_t val)
{
   *rfm.ss_reg_clear = rfm.ss_mask;
   
   (*rfm.spi_xfer)(reg | RFM95_SPI_WRITE_MASK);
   (*rfm.spi_xfer)(val);
   
   *rfm.ss_reg_set = rfm.ss_mask;
}

static uint8_t rfm95_read_many(uint8_t reg, uint8_t * dest, size_t len)
{
   *rfm.ss_reg_clear = rfm.ss_mask;
   
   uint8_t status = (*rfm.spi_xfer)(reg &~ RFM95_SPI_WRITE_MASK);
   
   while(len--)
   {
      *dest++ = (*rfm.spi_xfer)(0);
   }
   
   *rfm.ss_reg_set = rfm.ss_mask;
   
   return status;
}

static uint8_t rfm95_write_many(uint8_t reg, const uint8_t * src, size_t len)
{
   *rfm.ss_reg_clear = rfm.ss_mask;
   
   uint8_t status = (*rfm.spi_xfer)(reg | RFM95_SPI_WRITE_MASK);
   
   while(len--)
   {
      (*rfm.spi_xfer)(*src++);
   }
   
   *rfm.ss_reg_set = rfm.ss_mask;
   
   return status;
}

static RHMode rfm95_get_mode()
{
   return rfm95_read_reg(RH_RF95_REG_01_OP_MODE) & RH_RF95_MODE;
}

bool rfm95_is_valid()
{
   // Get the device type and check it
   // This also tests whether we are really connected to a device
   // My test devices return 0x83
   uint8_t rev = rfm95_read_reg(RH_RF95_REG_42_VERSION);
   
   return (rev == 0x12);
}

bool rfm95_start()
{
   if (!rfm95_is_valid())
      return false;

   // Set sleep mode, so we can also set LORA mode:
   rfm95_write_reg(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_SLEEP | RH_RF95_LONG_RANGE_MODE);
   
   RFM95_DELAY_MS(10); // Wait for sleep mode to take over from say, CAD
   
   // Check we are in sleep mode, with LORA set
   if (rfm95_read_reg(RH_RF95_REG_01_OP_MODE) != (RH_RF95_MODE_SLEEP | RH_RF95_LONG_RANGE_MODE))
   {
      return false;
   }

   // Set up FIFO
   // We configure so that we can use the entire 256 byte FIFO for either receive
   // or transmit, but not both at the same time
   rfm95_write_reg(RH_RF95_REG_0E_FIFO_TX_BASE_ADDR, 0);
   rfm95_write_reg(RH_RF95_REG_0F_FIFO_RX_BASE_ADDR, 0);
   
   rfm95_set_preamble_length(8);
    
   uint32_t frf = (868 * 1000000.0) / RH_RF95_FSTEP;
   rfm95_set_frequency(frf);
   
   rfm95_set_mode_idle();
   
   return true;
}

void rfm95_int_sig()
{
   rfm.int_sig = true;
}

void rfm95_service(bool fast)
{
   if((*rfm.int_reg & rfm.int_mask) == 0)
      return;

   /*rfm.int_sig = false;
   
   static uint32_t last_check = 0;
   uint32_t now = timer_tick();
   
   if (!fast && last_check - now < TM_MLS_T0_TICK(100))
      return;
   
   last_check = now;*/
      
   // Read the interrupt register
   uint8_t irq_flags = rfm95_read_reg(RH_RF95_REG_12_IRQ_FLAGS);
   
   if(irq_flags == 0)
   {
      //DBG(kLvlError, "rfm95, got interrupt but no IRQ flags set");
      //rfm95_write_reg(RH_RF95_REG_12_IRQ_FLAGS, 0xFF);
      return;
   }
   
   DBG(kLvlDbg, "rfm95, ISR %02X, %u, %u", irq_flags, (*rfm.int_reg & rfm.int_mask) > 0, _mode);
   
   rfm95_write_reg(RH_RF95_REG_12_IRQ_FLAGS, 0xFF);
   
   if(irq_flags & RH_RF95_RX_TIMEOUT)
   {      
      if(_mode != RHModeRx)
      {
         DBG(kLvlError, "rfm95, IRQ RX timeout but not in RX mode");
      }
      else
      {
         DBG(kLvlDbg, "rfm95, IRQ RX timeout");
         if(rfm.on_recv_to)
            (*rfm.on_recv_to)();
      }
   }
   
   if(irq_flags & RH_RF95_PAYLOAD_CRC_ERROR)
   {      
      if(_mode != RHModeRx)
      {
         DBG(kLvlError, "rfm95, IRQ CRC error but not in RX mode");
      }
      else
      {
         // DBG(kLvlDbg, "rfm95, IRQ CRC error");
         
         irq_flags &= ~RH_RF95_RX_DONE;
         
         if(rfm.on_recv_crc_err)
            (*rfm.on_recv_crc_err)();
      }
   }
   
   if(irq_flags & RH_RF95_RX_DONE)
   {      
      if(_mode != RHModeRx)
      {
         DBG(kLvlError, "rfm95, IRQ RX done but not in RX mode");
      }
      else
      {
         //DBG(kLvlDbg, "rfm95, IRQ RX done");
         
         uint8_t buff[256];
         uint8_t len = rfm95_read_reg(RH_RF95_REG_13_RX_NB_BYTES);

         // Reset the fifo read ptr to the beginning of the packet
         rfm95_write_reg(RH_RF95_REG_0D_FIFO_ADDR_PTR, rfm95_read_reg(RH_RF95_REG_10_FIFO_RX_CURRENT_ADDR));
         rfm95_read_many(RH_RF95_REG_00_FIFO, buff, len);

         uint8_t rssi = rfm95_read_reg(RH_RF95_REG_1A_PKT_RSSI_VALUE) - 137;
                  
         if(rfm.on_recv)
            (*rfm.on_recv)(buff, len, rssi);
      }
   }
   
   if(irq_flags & RH_RF95_VALID_HEADER)
   {      
      if(_mode != RHModeRx)
      {
         DBG(kLvlError, "rfm95, IRQ valid header but not in RX mode");
      }
      else
      {
         // DBG(kLvlDbg, "rfm95, RX valid header");
      }
   }
   
   if(irq_flags & RH_RF95_TX_DONE)
   {      
      if(_mode != RHModeTx)
      {
         DBG(kLvlError, "rfm95, IRQ TX done but not in TX mode");
      }
      else
      {
         //DBG(kLvlDbg, "rfm95, IRQ TX done");
         
         if(rfm.on_sent)
            (*rfm.on_sent)();
      }
   }
   
   uint8_t flags_unhandled = RH_RF95_CAD_DONE | RH_RF95_FHSS_CHANGE_CHANNEL | RH_RF95_CAD_DETECTED;
   if (irq_flags & flags_unhandled)
   {
      DBG(kLvlWarn, "rfm95, IRQ unhandled %2X", (irq_flags & flags_unhandled));
   }
}

bool rfm95_send(const void * data, uint8_t len)
{
   if (len > RH_RF95_MAX_MESSAGE_LEN)
      return false;

   // Make sure we dont interrupt an outgoing message
   rfm95_wait_packet_sent(); 

   rfm95_set_mode_idle();
   
   //if (!rfm95_wait_cad()) 
   //   return false;  // Check channel activity

   // Position at the beginning of the FIFO
   rfm95_write_reg(RH_RF95_REG_0D_FIFO_ADDR_PTR, 0);

   // The message data
   rfm95_write_many(RH_RF95_REG_00_FIFO, (const uint8_t *)data, len);
   rfm95_write_reg(RH_RF95_REG_22_PAYLOAD_LENGTH, len);

   rfm95_set_mode_tx(); // Start the transmitter

   // when Tx is done, interruptHandler will fire and radio mode will return to STANDBY
   return true;
}

// Since we have no interrupts, we need to implement our own 
// waitPacketSent for the driver by reading RF69 internal register
bool rfm95_wait_packet_sent()
{
   while(_mode == RHModeTx || _mode == RHModeFsTx)
   {
      rfm95_service(true);
   }
   
   return true;

   /*
   // If we are not currently in transmit mode, there is no packet to wait for
   if (_mode != RHModeTx)
      return true;
   
   uint8_t active_mode = rfm95_get_mode();
   while ((active_mode == RHModeTx || active_mode == RHModeFsTx))
   {
      active_mode = rfm95_get_mode();
      if(!rfm95_is_valid())
         return false;
   }
   */   
   
   return true;
}

bool rfm95_print_registers()
{
#ifdef RH_HAVE_SERIAL
   
   const uint8_t registers[] = 
   { 
      0x01, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 
      0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x014, 0x15, 0x16, 
      0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
      0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
   };

   for (size_t i = 0; i < COUNT(registers); i++)
   {
      DBG(kLvlDbg, "reg %02X: %02X", registers[i], rfm95_read_reg(registers[i]));
   }
   
#endif
   
   return true;
}

uint8_t rfm95_max_message_length()
{
    return RH_RF95_MAX_MESSAGE_LEN;
}

bool rfm95_set_frequency(uint32_t frf)
{
   rfm95_write_reg(RH_RF95_REG_06_FRF_MSB, (frf >> 16) & 0xff);
   rfm95_write_reg(RH_RF95_REG_07_FRF_MID, (frf >> 8) & 0xff);
   rfm95_write_reg(RH_RF95_REG_08_FRF_LSB, frf & 0xff);
   return true;
}

static void set_mode(RHMode mode)
{
   _mode = mode;
   // DBG(kLvlVerb, "rfm95, mode %s", mode_str[mode]);
}

void rfm95_set_mode_idle()
{
   if (_mode != RHModeIdle)
   {
      rfm95_write_reg(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_STDBY);
   }
   
   set_mode(RHModeIdle);
}

bool rfm95_sleep()
{
   if (_mode != RHModeSleep)
   {
      rfm95_write_reg(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_SLEEP);
   }
   
   set_mode(RHModeSleep);
   
   return true;
}

void rfm95_set_mode_rx()
{
   if (_mode != RHModeRx)
   {
      rfm95_write_reg(RH_RF95_REG_40_DIO_MAPPING1, 0x00); // Interrupt on RxDone
      rfm95_write_reg(RH_RF95_REG_12_IRQ_FLAGS, 0xFF);
      rfm95_write_reg(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_RXCONTINUOUS);
   }
   
   set_mode(RHModeRx);
}

void rfm95_set_mode_tx()
{
   if (_mode != RHModeTx)
   {
      rfm95_write_reg(RH_RF95_REG_40_DIO_MAPPING1, 0x40); // Interrupt on TxDone
      rfm95_write_reg(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_TX);
   }
   
   set_mode(RHModeTx);
}

void rfm95_set_tx_power(int8_t power, bool useRFO)
{
   // Sigh, different behaviours depending on whther the module use PA_BOOST or the RFO pin
   // for the transmitter output
   if (useRFO)
   {
      if (power > 14)
          power = 14;
      
      if (power < -1)
          power = -1;
      
      rfm95_write_reg(RH_RF95_REG_09_PA_CONFIG, RH_RF95_MAX_POWER | (power + 1));
   }
   else
   {
      if (power > 23)
          power = 23;
      if (power < 5)
          power = 5;

      // For RH_RF95_PA_DAC_ENABLE, manual says '+20dBm on PA_BOOST when OutputPower=0xf'
      // RH_RF95_PA_DAC_ENABLE actually adds about 3dBm to all power levels. We will us it
      // for 21, 22 and 23dBm
      if (power > 20)
      {
          rfm95_write_reg(RH_RF95_REG_4D_PA_DAC, RH_RF95_PA_DAC_ENABLE);
          power -= 3;
      }
      else
      {
          rfm95_write_reg(RH_RF95_REG_4D_PA_DAC, RH_RF95_PA_DAC_DISABLE);
      }

      // RFM95/96/97/98 does not have RFO pins connected to anything. Only PA_BOOST
      // pin is connected, so must use PA_BOOST
      // Pout = 2 + OutputPower.
      // The documentation is pretty confusing on this topic: PaSelect says the max power is 20dBm,
      // but OutputPower claims it would be 17dBm.
      // My measurements show 20dBm is correct
      rfm95_write_reg(RH_RF95_REG_09_PA_CONFIG, RH_RF95_PA_SELECT | (power-5));
   }
}

// Sets registers from a canned modem configuration structure
void rfm95_set_modem_registers(const uint8_t * reg)
{
   rfm95_set_mode_idle();
   rfm95_write_reg(RH_RF95_REG_1D_MODEM_CONFIG1, reg[0]);
   rfm95_write_reg(RH_RF95_REG_1E_MODEM_CONFIG2, reg[1]);
   rfm95_write_reg(RH_RF95_REG_26_MODEM_CONFIG3, reg[2]);
}

void rfm95_set_preamble_length(uint16_t bytes)
{
   rfm95_write_reg(RH_RF95_REG_20_PREAMBLE_MSB, bytes >> 8);
   rfm95_write_reg(RH_RF95_REG_21_PREAMBLE_LSB, bytes & 0xff);
}

void rfm95_enable_tcxo()
{
   while ((rfm95_read_reg(RH_RF95_REG_4B_TCXO) & RH_RF95_TCXO_TCXO_INPUT_ON) != RH_RF95_TCXO_TCXO_INPUT_ON)
   {
      rfm95_sleep();
      rfm95_write_reg(RH_RF95_REG_4B_TCXO, (rfm95_read_reg(RH_RF95_REG_4B_TCXO) | RH_RF95_TCXO_TCXO_INPUT_ON));
   } 
}