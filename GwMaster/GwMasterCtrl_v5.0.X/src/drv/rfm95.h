// RH_RF95.h
//
// Definitions for HopeRF LoRa radios per:
// http://www.hoperf.com/upload/rf/RFM95_96_97_98W.pdf
// http://www.hoperf.cn/upload/rfchip/RF96_97_98.pdf
//
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2014 Mike McCauley
// $Id: RH_RF95.h,v 1.14 2017/01/13 01:29:36 mikem Exp mikem $
// 

#ifndef RH_RF95_h
#define RH_RF95_h

#include "types.h"

#define PROGMEM

// Max number of octets the LORA Rx/Tx FIFO can hold
#define RH_RF95_FIFO_SIZE        255

// This is the maximum number of bytes that can be carried by the LORA.
// We use some for headers, keeping fewer for RadioHead messages
#define RH_RF95_MAX_PAYLOAD_LEN     RH_RF95_FIFO_SIZE


// This is the maximum message length that can be supported by this driver. 
// Can be pre-defined to a smaller size (to save SRAM) prior to including this header
// Here we allow for 1 byte message length, 4 bytes headers, user data and 2 bytes of FCS
#ifndef RH_RF95_MAX_MESSAGE_LEN
 #define RH_RF95_MAX_MESSAGE_LEN (RH_RF95_MAX_PAYLOAD_LEN)
#endif

// The crystal oscillator frequency of the module
#define RH_RF95_FXOSC 32000000.0

// The Frequency Synthesizer step = RH_RF95_FXOSC / 2^^19
#define RH_RF95_FSTEP  (RH_RF95_FXOSC / 524288)


// Register names (LoRa Mode, from table 85)
#define RH_RF95_REG_00_FIFO                                0x00
#define RH_RF95_REG_01_OP_MODE                             0x01
#define RH_RF95_REG_02_RESERVED                            0x02
#define RH_RF95_REG_03_RESERVED                            0x03
#define RH_RF95_REG_04_RESERVED                            0x04
#define RH_RF95_REG_05_RESERVED                            0x05
#define RH_RF95_REG_06_FRF_MSB                             0x06
#define RH_RF95_REG_07_FRF_MID                             0x07
#define RH_RF95_REG_08_FRF_LSB                             0x08
#define RH_RF95_REG_09_PA_CONFIG                           0x09
#define RH_RF95_REG_0A_PA_RAMP                             0x0a
#define RH_RF95_REG_0B_OCP                                 0x0b
#define RH_RF95_REG_0C_LNA                                 0x0c
#define RH_RF95_REG_0D_FIFO_ADDR_PTR                       0x0d
#define RH_RF95_REG_0E_FIFO_TX_BASE_ADDR                   0x0e
#define RH_RF95_REG_0F_FIFO_RX_BASE_ADDR                   0x0f
#define RH_RF95_REG_10_FIFO_RX_CURRENT_ADDR                0x10
#define RH_RF95_REG_11_IRQ_FLAGS_MASK                      0x11
#define RH_RF95_REG_12_IRQ_FLAGS                           0x12
#define RH_RF95_REG_13_RX_NB_BYTES                         0x13
#define RH_RF95_REG_14_RX_HEADER_CNT_VALUE_MSB             0x14
#define RH_RF95_REG_15_RX_HEADER_CNT_VALUE_LSB             0x15
#define RH_RF95_REG_16_RX_PACKET_CNT_VALUE_MSB             0x16
#define RH_RF95_REG_17_RX_PACKET_CNT_VALUE_LSB             0x17
#define RH_RF95_REG_18_MODEM_STAT                          0x18
#define RH_RF95_REG_19_PKT_SNR_VALUE                       0x19
#define RH_RF95_REG_1A_PKT_RSSI_VALUE                      0x1a
#define RH_RF95_REG_1B_RSSI_VALUE                          0x1b
#define RH_RF95_REG_1C_HOP_CHANNEL                         0x1c
#define RH_RF95_REG_1D_MODEM_CONFIG1                       0x1d
#define RH_RF95_REG_1E_MODEM_CONFIG2                       0x1e
#define RH_RF95_REG_1F_SYMB_TIMEOUT_LSB                    0x1f
#define RH_RF95_REG_20_PREAMBLE_MSB                        0x20
#define RH_RF95_REG_21_PREAMBLE_LSB                        0x21
#define RH_RF95_REG_22_PAYLOAD_LENGTH                      0x22
#define RH_RF95_REG_23_MAX_PAYLOAD_LENGTH                  0x23
#define RH_RF95_REG_24_HOP_PERIOD                          0x24
#define RH_RF95_REG_25_FIFO_RX_BYTE_ADDR                   0x25
#define RH_RF95_REG_26_MODEM_CONFIG3                       0x26

#define RH_RF95_REG_40_DIO_MAPPING1                        0x40
#define RH_RF95_REG_41_DIO_MAPPING2                        0x41
#define RH_RF95_REG_42_VERSION                             0x42

#define RH_RF95_REG_4B_TCXO                                0x4b
#define RH_RF95_REG_4D_PA_DAC                              0x4d
#define RH_RF95_REG_5B_FORMER_TEMP                         0x5b
#define RH_RF95_REG_61_AGC_REF                             0x61
#define RH_RF95_REG_62_AGC_THRESH1                         0x62
#define RH_RF95_REG_63_AGC_THRESH2                         0x63
#define RH_RF95_REG_64_AGC_THRESH3                         0x64

// RH_RF95_REG_01_OP_MODE                             0x01
#define RH_RF95_LONG_RANGE_MODE                       0x80
#define RH_RF95_ACCESS_SHARED_REG                     0x40
#define RH_RF95_LOW_FREQUENCY_MODE                    0x08
#define RH_RF95_MODE                                  0x07
#define RH_RF95_MODE_SLEEP                            0x00
#define RH_RF95_MODE_STDBY                            0x01
#define RH_RF95_MODE_FSTX                             0x02
#define RH_RF95_MODE_TX                               0x03
#define RH_RF95_MODE_FSRX                             0x04
#define RH_RF95_MODE_RXCONTINUOUS                     0x05
#define RH_RF95_MODE_RXSINGLE                         0x06
#define RH_RF95_MODE_CAD                              0x07

// RH_RF95_REG_09_PA_CONFIG                           0x09
#define RH_RF95_PA_SELECT                             0x80
#define RH_RF95_MAX_POWER                             0x70
#define RH_RF95_OUTPUT_POWER                          0x0f

// RH_RF95_REG_0A_PA_RAMP                             0x0a
#define RH_RF95_LOW_PN_TX_PLL_OFF                     0x10
#define RH_RF95_PA_RAMP                               0x0f
#define RH_RF95_PA_RAMP_3_4MS                         0x00
#define RH_RF95_PA_RAMP_2MS                           0x01
#define RH_RF95_PA_RAMP_1MS                           0x02
#define RH_RF95_PA_RAMP_500US                         0x03
#define RH_RF95_PA_RAMP_250US                         0x0
#define RH_RF95_PA_RAMP_125US                         0x05
#define RH_RF95_PA_RAMP_100US                         0x06
#define RH_RF95_PA_RAMP_62US                          0x07
#define RH_RF95_PA_RAMP_50US                          0x08
#define RH_RF95_PA_RAMP_40US                          0x09
#define RH_RF95_PA_RAMP_31US                          0x0a
#define RH_RF95_PA_RAMP_25US                          0x0b
#define RH_RF95_PA_RAMP_20US                          0x0c
#define RH_RF95_PA_RAMP_15US                          0x0d
#define RH_RF95_PA_RAMP_12US                          0x0e
#define RH_RF95_PA_RAMP_10US                          0x0f

// RH_RF95_REG_0B_OCP                                 0x0b
#define RH_RF95_OCP_ON                                0x20
#define RH_RF95_OCP_TRIM                              0x1f

// RH_RF95_REG_0C_LNA                                 0x0c
#define RH_RF95_LNA_GAIN                              0xe0
#define RH_RF95_LNA_GAIN_G1                           0x20
#define RH_RF95_LNA_GAIN_G2                           0x40
#define RH_RF95_LNA_GAIN_G3                           0x60                
#define RH_RF95_LNA_GAIN_G4                           0x80
#define RH_RF95_LNA_GAIN_G5                           0xa0
#define RH_RF95_LNA_GAIN_G6                           0xc0
#define RH_RF95_LNA_BOOST_LF                          0x18
#define RH_RF95_LNA_BOOST_LF_DEFAULT                  0x00
#define RH_RF95_LNA_BOOST_HF                          0x03
#define RH_RF95_LNA_BOOST_HF_DEFAULT                  0x00
#define RH_RF95_LNA_BOOST_HF_150PC                    0x11

// RH_RF95_REG_11_IRQ_FLAGS_MASK                      0x11
#define RH_RF95_RX_TIMEOUT_MASK                       0x80
#define RH_RF95_RX_DONE_MASK                          0x40
#define RH_RF95_PAYLOAD_CRC_ERROR_MASK                0x20
#define RH_RF95_VALID_HEADER_MASK                     0x10
#define RH_RF95_TX_DONE_MASK                          0x08
#define RH_RF95_CAD_DONE_MASK                         0x04
#define RH_RF95_FHSS_CHANGE_CHANNEL_MASK              0x02
#define RH_RF95_CAD_DETECTED_MASK                     0x01

// RH_RF95_REG_12_IRQ_FLAGS                           0x12
#define RH_RF95_RX_TIMEOUT                            0x80
#define RH_RF95_RX_DONE                               0x40
#define RH_RF95_PAYLOAD_CRC_ERROR                     0x20
#define RH_RF95_VALID_HEADER                          0x10
#define RH_RF95_TX_DONE                               0x08
#define RH_RF95_CAD_DONE                              0x04
#define RH_RF95_FHSS_CHANGE_CHANNEL                   0x02
#define RH_RF95_CAD_DETECTED                          0x01

// RH_RF95_REG_18_MODEM_STAT                          0x18
#define RH_RF95_RX_CODING_RATE                        0xe0
#define RH_RF95_MODEM_STATUS_CLEAR                    0x10
#define RH_RF95_MODEM_STATUS_HEADER_INFO_VALID        0x08
#define RH_RF95_MODEM_STATUS_RX_ONGOING               0x04
#define RH_RF95_MODEM_STATUS_SIGNAL_SYNCHRONIZED      0x02
#define RH_RF95_MODEM_STATUS_SIGNAL_DETECTED          0x01

// RH_RF95_REG_1C_HOP_CHANNEL                         0x1c
#define RH_RF95_PLL_TIMEOUT                           0x80
#define RH_RF95_RX_PAYLOAD_CRC_IS_ON                  0x40
#define RH_RF95_FHSS_PRESENT_CHANNEL                  0x3f

// RH_RF95_REG_1D_MODEM_CONFIG1                       0x1d
#define RH_RF95_BW                                    0xf0

#define RH_RF95_BW_7_8KHZ                             0x00
#define RH_RF95_BW_10_4KHZ                            0x10
#define RH_RF95_BW_15_6KHZ                            0x20
#define RH_RF95_BW_20_8KHZ                            0x30
#define RH_RF95_BW_31_25KHZ                           0x40
#define RH_RF95_BW_41_7KHZ                            0x50
#define RH_RF95_BW_62_5KHZ                            0x60
#define RH_RF95_BW_125KHZ                             0x70
#define RH_RF95_BW_250KHZ                             0x80
#define RH_RF95_BW_500KHZ                             0x90
#define RH_RF95_CODING_RATE                           0x0e
#define RH_RF95_CODING_RATE_4_5                       0x02
#define RH_RF95_CODING_RATE_4_6                       0x04
#define RH_RF95_CODING_RATE_4_7                       0x06
#define RH_RF95_CODING_RATE_4_8                       0x08
#define RH_RF95_IMPLICIT_HEADER_MODE_ON               0x01

// RH_RF95_REG_1E_MODEM_CONFIG2                       0x1e
#define RH_RF95_SPREADING_FACTOR                      0xf0
#define RH_RF95_SPREADING_FACTOR_64CPS                0x60
#define RH_RF95_SPREADING_FACTOR_128CPS               0x70
#define RH_RF95_SPREADING_FACTOR_256CPS               0x80
#define RH_RF95_SPREADING_FACTOR_512CPS               0x90
#define RH_RF95_SPREADING_FACTOR_1024CPS              0xa0
#define RH_RF95_SPREADING_FACTOR_2048CPS              0xb0
#define RH_RF95_SPREADING_FACTOR_4096CPS              0xc0
#define RH_RF95_TX_CONTINUOUS_MOE                     0x08

#define RH_RF95_PAYLOAD_CRC_ON                        0x04
#define RH_RF95_SYM_TIMEOUT_MSB                       0x03

// RH_RF95_REG_4B_TCXO                                0x4b
#define RH_RF95_TCXO_TCXO_INPUT_ON                    0x10

// RH_RF95_REG_4D_PA_DAC                              0x4d
#define RH_RF95_PA_DAC_DISABLE                        0x04
#define RH_RF95_PA_DAC_ENABLE                         0x07

typedef struct 
{
   volatile uint32_t * volatile ss_reg_set;
   volatile uint32_t * volatile ss_reg_clear;
   volatile uint32_t * volatile int_reg;
   uint32_t ss_mask;
   uint32_t int_mask;
   uint8_t (* spi_xfer)(uint8_t);
   
   void (*on_recv)(const uint8_t * buff, uint32_t size, uint8_t rssi);
   void (*on_recv_to)(void);
   void (*on_recv_crc_err)(void);
   void (*on_sent)(void);
} Rfm95Config;


bool rfm95_init(const Rfm95Config * const config);

/// Initialise the Driver transport hardware and software.
/// Make sure the Driver is properly configured before calling init().
/// \return true if initialisation succeeded.
bool rfm95_start();
void rfm95_int_sig();
bool rfm95_is_valid();

/// Prints the value of all chip registers
/// to the Serial device if RH_HAVE_SERIAL is defined for the current platform
/// For debugging purposes only.
/// \return true on success
bool rfm95_print_registers();

/// Sets all the registered required to configure the data modem in the RF95/96/97/98, including the bandwidth, 
/// spreading factor etc. You can use this to configure the modem with custom configurations if none of the 
/// canned configurations in ModemConfigChoice suit you.
/// \param[in] config A ModemConfig structure containing values for the modem configuration registers.
void rfm95_set_modem_registers(const uint8_t * reg);

/// Tests whether a new message is available
/// from the Driver. 
/// On most drivers, this will also put the Driver into RHModeRx mode until
/// a message is actually received by the transport, when it wil be returned to RHModeIdle.
/// This can be called multiple times in a timeout loop
/// \return true if a new, complete, error-free uncollected message is available to be retreived by recv()
bool rfm95_available();

/// Turns the receiver on if it not already on.
/// If there is a valid message available, copy it to buf and return true
/// else return false.
/// If a message is copied, *len is set to the length (Caution, 0 length messages are permitted).
/// You should be sure to call this function frequently enough to not miss any messages
/// It is recommended that you call it in your main loop.
/// \param[in] buf Location to copy the received message
/// \param[in,out] len Pointer to available space in buf. Set to the actual number of octets copied.
/// \return true if a valid message was copied to buf
bool rfm95_recv(uint8_t* buf, uint8_t* len);

/// Waits until any previous transmit packet is finished being transmitted with waitPacketSent().
/// Then optionally waits for Channel Activity Detection (CAD) 
/// to show the channnel is clear (if the radio supports CAD) by calling waitCAD().
/// Then loads a message into the transmitter and starts the transmitter. Note that a message length
/// of 0 is permitted. 
/// \param[in] data Array of data to be sent
/// \param[in] len Number of bytes of data to send
/// specify the maximum time in ms to wait. If 0 (the default) do not wait for CAD before transmitting.
/// \return true if the message length was valid and it was correctly queued for transmit. Return false
/// if CAD was requested and the CAD timeout timed out before clear channel was detected.
bool rfm95_send(const void * data, uint8_t len);

/// Blocks until the current message (if any) 
/// has been transmitted
/// \return true on success, false if the chip is not in transmit mode or other transmit failure
bool rfm95_wait_packet_sent();

/// Sets the length of the preamble
/// in bytes. 
/// Caution: this should be set to the same 
/// value on all nodes in your network. Default is 8.
/// Sets the message preamble length in RH_RF95_REG_??_PREAMBLE_?SB
/// \param[in] bytes Preamble length in bytes.  
void rfm95_set_preamble_length(uint16_t bytes);

/// Returns the maximum message length 
/// available in this Driver.
/// \return The maximum legal message length
uint8_t rfm95_max_message_length();

/// Sets the transmitter and receiver 
/// centre frequency.
/// \param[in] centre Frequency in MHz. 137.0 to 1020.0. Caution: RFM95/96/97/98 comes in several
/// different frequency ranges, and setting a frequency outside that range of your radio will probably not work
/// \return true if the selected frquency centre is within range
bool rfm95_set_frequency(uint32_t centre);

/// If current mode is Rx or Tx changes it to Idle. If the transmitter or receiver is running, 
/// disables them.
void rfm95_set_mode_idle();

/// If current mode is Tx or Idle, changes it to Rx. 
/// Starts the receiver in the RF95/96/97/98.
void rfm95_set_mode_rx();

/// If current mode is Rx or Idle, changes it to Rx. F
/// Starts the transmitter in the RF95/96/97/98.
void rfm95_set_mode_tx();

/// Sets the transmitter power output level, and configures the transmitter pin.
/// Be a good neighbour and set the lowest power level you need.
/// Some SX1276/77/78/79 and compatible modules (such as RFM95/96/97/98) 
/// use the PA_BOOST transmitter pin for high power output (and optionally the PA_DAC)
/// while some (such as the Modtronix inAir4 and inAir9) 
/// use the RFO transmitter pin for lower power but higher efficiency.
/// You must set the appropriate power level and useRFO argument for your module.
/// Check with your module manufacturer which transmtter pin is used on your module
/// to ensure you are setting useRFO correctly. 
/// Failure to do so will result in very low 
/// transmitter power output.
/// Caution: legal power limits may apply in certain countries.
/// After init(), the power will be set to 13dBm, with useRFO false (ie PA_BOOST enabled).
/// \param[in] power Transmitter power level in dBm. For RFM95/96/97/98 LORA with useRFO false, 
/// valid values are from +5 to +23.
/// For Modtronix inAir4 and inAir9 with useRFO true (ie RFO pins in use), 
/// valid values are from -1 to 14.
/// \param[in] useRFO If true, enables the use of the RFO transmitter pins instead of
/// the PA_BOOST pin (false). Choose the correct setting for your module.
void rfm95_set_tx_power(int8_t power, bool useRFO);

/// Sets the radio into low-power sleep mode.
/// If successful, the transport will stay in sleep mode until woken by 
/// changing mode it idle, transmit or receive (eg by calling send(), recv(), available() etc)
/// Caution: there is a time penalty as the radio takes a finite time to wake from sleep mode.
/// \return true if sleep mode was successfully entered.
bool rfm95_sleep();

// Bent G Christensen (bentor@gmail.com), 08/15/2016
/// Use the radio's Channel Activity Detect (CAD) function to detect channel activity.
/// Sets the RF95 radio into CAD mode and waits until CAD detection is complete.
/// To be used in a listen-before-talk mechanism (Collision Avoidance)
/// with a reasonable time backoff algorithm.
/// This is called automatically by waitCAD().
/// \return true if channel is in use.  
bool rfm95_is_channel_active();

/// Enable TCXO mode
/// Call this immediately after init(), to force your radio to use an external 
/// frequency source, such as a Temperature Compensated Crystal Oscillator (TCXO).
/// See the comments in the main documentation about the sensitivity of this radio to
/// clock frequency especially when using narrow bandwidths.
/// Leaves the module in sleep mode.
/// Caution, this function has not been tested by us.
void rfm95_enable_tcxo();

/// This is a low level function to handle the interrupts for one instance of RH_RF95.
/// Called automatically by isr*()
/// Should not need to be called by user code.
#ifndef RH_RF95_IRQLESS
    void rfm95_handle_interrupt();
#endif

void rfm95_service(bool fast);


#endif
