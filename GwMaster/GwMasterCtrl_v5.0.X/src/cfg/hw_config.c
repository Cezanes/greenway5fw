#include "hw_config.h"

#include "hal/uart32mx.h"
#include "sal/pulse.h"
#include "sas/sim800c.h"
#include "app/net/cellular.h"

#include "mcc_generated_files/spi3.h"
#include "mcc_generated_files/mcc.h"
#include "app/net/serial.h"


///////////////////////////////////////////////////////////////////////////////


#define STORAGE_END_ADDR        (0x9D080000UL - 4096)
#define STORAGE_APP_CFG_ADDR    (STORAGE_END_ADDR     - 1 * STORAGE_PAGE_SIZE)
#define STORAGE_SEM_PROG_ADDR   (STORAGE_APP_CFG_ADDR - SIGNAL_MAX_SCHEDULE_SIZE)
//#define STORAGE_FW_IMG          (0x9D018000)

const uint8_t __attribute((space(prog), section(".app_config"), address(STORAGE_APP_CFG_ADDR))) sect_app_cfg[STORAGE_PAGE_SIZE];// = { [0 ...(sizeof(sect_app_cfg))-1] = 0x55 };
const uint8_t __attribute((space(prog), section(".sem_prog"), address(STORAGE_SEM_PROG_ADDR))) sect_sem_prog[SIGNAL_MAX_SCHEDULE_SIZE];// = { [0 ...(sizeof(sect_sem_prog))-1] = 0xFF };
//const uint8_t __attribute((space(prog), section(".fwupd"), noload, address(STORAGE_FW_IMG))) sect_fw_img[128 * 1024];

static const StorageSector nvm[] = 
{
   {.ptr = sect_app_cfg,  .size = sizeof(sect_app_cfg)}, 
   {.ptr = sect_sem_prog, .size = sizeof(sect_sem_prog)}, 
};

static const BtnEntry btn_entries[] = 
{
   {.port = &PORTE, .port_mask = 1 << 3},
};

#if 1

static const Pin pin_addr[] = 
{
   PIN_DEF(C, 1),
   PIN_DEF(E, 7),
   PIN_DEF(E, 6),
   PIN_DEF(E, 5),
};

static const Pin pin_net[] = 
{
   PIN_DEF(C, 4),
   PIN_DEF(C, 3),
   PIN_DEF(C, 2),
};

//static const Pin pin_have_modem = PIN_DEF(G, 6);
static const Pin pin_have_modem = PIN_DEF(C, 2);

#else

static const Pin pin_addr[] = 
{
   PIN_DEF(C, 1),
   PIN_DEF(E, 7),
   PIN_DEF(E, 6),
   PIN_DEF(E, 5),
};

static const Pin pin_net[] = 
{
};

static const Pin pin_have_modem = PIN_DEF(C, 2);

#endif


static uint8_t network_buff[16 * 1024];

static const PulseInstance pu_inst[] = 
{
   {
      .period_on = 250,  // Green
      .period_off = 250,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 6,
      .pin_port_set = &LATASET,
      .pin_port_clr = &LATACLR,
   },
   
   {
      .flags = kPulseStartActive,
      .period_on = 50,  // Blue
      .period_off = 10,
      .total_pulses = 2,
      .pin_mask = 1 << 12,
      .pin_port_set = &LATGSET,
      .pin_port_clr = &LATGCLR,
   },
   
   {
      .period_on = 5000,  // GPS lock
      .period_off = 50,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 7,
      .pin_port_set = &LATASET,
      .pin_port_clr = &LATACLR,
   },

   {
      .period_on = 1000, // Red?
      .period_off = 1000,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 0,
      .pin_port_set = &LATESET,
      .pin_port_clr = &LATECLR,
   },
   
   {
      .period_on = 100,  // Yellow, booting
      .period_off = 100,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 7,
      .pin_port_set = &LATASET,
      .pin_port_clr = &LATACLR,
   },
   
   {
      .period_on = 150,  // Green, No Time
      .period_off = 150,
      .total_pulses = kPulseInfinite,
      .pin_mask = 1 << 7,
      .pin_port_set = &LATBSET,
      .pin_port_clr = &LATBCLR,
   },
};

static const GsmNetworkAPN gsm_network_apns[] = 
{
   {"default",      "internetzzzz", "", ""},
   {"Vodafone RO",  "live.vodafone.com", "", ""},
   {"Digi.Mobil",   "internet", "" , ""},
   {"Orange RO",    "internet", "", ""},
   {"orange",       "internet", "", ""},
   {"TELEKOM.RO",   "3gnet", "", ""},
   {"1nce.net",     "iot.1nce.net", "", ""},
};

static const uint32_t sem_sms_periods[] = 
{
              0, 
        60 * 60, 
    6 * 60 * 60, 
   24 * 60 * 60,
};

static const SocketConfig sockets[] = 
{
   {
      .baud = 500000,
      .clock_src = _XTAL_FREQ,
      .uart = &Uart[0],
      .rx_buff = network_buff,
      .rx_buff_size = sizeof(network_buff),
   },
   {
      .baud = 115200,
      .clock_src = _XTAL_FREQ,
      .uart = &Uart[2],
      .rx_buff = network_buff,
      .rx_buff_size = sizeof(network_buff),
   },
};

const HwConfig hw_config = 
{
   .boot = {
      .addr = {
         .list = pin_addr,
         .count = COUNT(pin_addr),
      },
      .net = {
         .list = pin_net,
         .count = COUNT(pin_net),
      },
      .modem_present = pin_have_modem,
   },
   
   .debug = {
      .buff = (uint8_t[1024]){},
      .buff_size = 1024,
      .baud = 500000,
      .clock_src = _XTAL_FREQ,
      .uart = &Uart[0],
   },
   
   .shabuff = {
      .ptr = (uint8_t[8 * 1024]){},
      .size = 8 * 1024,
      .chunk_count = 4,
   },
      
   .storage = {
      .sector_count = COUNT(nvm),
      .sectors = nvm,
   },
   
   .buttons = {
      .entries = btn_entries,
      .count = COUNT(btn_entries),
   },
   
   .radio = {
      .ss_reg_set = &LATDSET,
      .ss_reg_clear = &LATDCLR,
      .ss_mask = 1 << 5,
      .int_reg = &PORTD,
      .int_mask = 1 << 13,
      .spi_xfer = &SPI3_Exchange8bit, 
      .rx_buff = network_buff,
      .rx_buff_size = sizeof(network_buff),
   },
   
   .rtc = {
      .ss_reg_set = &LATDSET,
      .ss_reg_clear = &LATDCLR,
      .ss_mask = (1 << 12),
      .spi_xfer = &SPI3_Exchange8bit,
   },
   
   .sem = {
      .sch_buff = (uint8_t[2048]){},
      .sch_buff_size = 2048,
      .sms_periods = sem_sms_periods,
      .sms_period_count = COUNT(sem_sms_periods),
   },
   
   .pulse = {
      .inst = pu_inst,
      .count = COUNT(pu_inst),
   },
   
   .com = {
      .cell = {
         .sms_buff = (uint8_t[256]){},
         .sms_buff_size = 256,
         
         .ext_modem = true,
         .ext_modem_itf = kSlinkItfEdge,
         
         .gsm = {
            .baud = 115200,
            .clock_src = _XTAL_FREQ,
            .uart_dev = &Uart[1],
            .uart_rx_buff = (uint8_t[64]){},
            .uart_rx_buff_size = 64,
            .response_buff = (uint8_t[128]){},
            .response_buff_size = 128,
            .pin_key = PIN_DEF(F, 5),
            .pin_ring = PIN_DEF(B, 15),
            .pin_power = PIN_DEF(F, 4),

            .apn = gsm_network_apns,
            .apn_size = COUNT(gsm_network_apns),
         },
      },
   },
   
   .gps = {
      .baud = 9600,
      .clock_src = _XTAL_FREQ,
      .uart = &Uart[4],
      .rx_buff = (uint8_t[256]){},
      .rx_buff_size = 256,
      .pulse_led_id = kPulseGps,
   },
   
   .srv = {
      .sockets = sockets,
      .socket_count = COUNT(sockets),
      .data_crc_per_itf = (uint16_t[COUNT(sockets)]){},
      .shared_rx_buff  = network_buff,
      .shared_rx_buff_size = sizeof(network_buff),
   },
   
   .pctrl = {
      .can = {
         .clock = {
            .phaseSeg1Tq = 3,
            .phaseSeg2Tq = 3,
            .propagationSegTq = 3,
            .phaseSeg2TimeSelect = true,
            .sample3Time = true,
            .syncJumpWidth = 2,
            .can_baud = 125000,
            .sys_clock = _XTAL_FREQ,
         },
         
         .use_rx_interrupt = false,
         .mode_timeout = 1000,
      },
   },
};


void hw_config_init(void)
{
   SYSTEM_RegUnlock(); // unlock PPS
   CFGCONbits.IOLOCK = 0;

   C1RXRbits.C1RXR = 0x09;
   RPB9Rbits.RPB9R = 0x0C;
   U2RXRbits.U2RXR = 0x000B;   //RD14->UART2:U2RX;

   CFGCONbits.IOLOCK = 1; // lock   PPS
   SYSTEM_RegLock(); 
}