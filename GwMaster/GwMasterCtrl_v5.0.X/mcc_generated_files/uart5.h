/**
  UART5 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    uart5.h

  @Summary
    This is the generated header file for the UART5 driver using PIC32MX MCUs

  @Description
    This header file provides APIs for driver for UART5.
    Generation Information :
        Product Revision  :  PIC32MX MCUs - pic32mx : v1.35
        Device            :  PIC32MX570F512L
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB             :  MPLAB X 3.55
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _UART5_H
#define _UART5_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Types
*/

/** UART5 Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
typedef enum
{
    /* Indicates that Receive buffer has data, at least one more character can be read */
    UART5_RX_DATA_AVAILABLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
    
    /* Indicates that Receive buffer has overflowed */
    UART5_RX_OVERRUN_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that Framing error has been detected for the current character */
    UART5_FRAMING_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that Parity error has been detected for the current character */
    UART5_PARITY_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that Receiver is Idle */
    UART5_RECEIVER_IDLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

    /* Indicates that the last transmission has completed */
    UART5_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

    /* Indicates that Transmit buffer is full */
    UART5_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

}UART5_STATUS;

/**
  Section: Macro Declarations
*/

#define UART5_DataReady  (U5STAbits.URXDA == 1)

/**
  Section: UART5 APIs
*/

/**
  @Summary
    Initialization routine that takes inputs from the UART5 GUI.

  @Description
    This routine initializes the UART5 driver.
    This routine must be called before any other UART5 routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    
*/
void UART5_Initialize(void);

/**
  @Summary
    Read a byte of data from the UART5.

  @Description
    This routine reads a byte of data from the UART5.

  @Preconditions
    UART5_Initialize() function should have been called
    before calling this function. This is a blocking function.
    So the recieve status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t UART5_Read(void);

 /**
  @Summary
    Writes a byte of data to the UART5.

  @Description
    This routine writes a byte of data to the UART5.

  @Preconditions
    UART5_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the UART5

  @Returns
    None
*/
void UART5_Write(uint8_t txData);

/**
  @Summary
    Returns the transmitter and receiver status

  @Description
    This returns the transmitter and receiver status. The returned status may 
    contain a value with more than one of the bits
    specified in the UART5_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART5_Initializer function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART5_STATUS value describing the current status 
    of the transfer.

  @Example
    <code>
        while(!(UART5_StatusGet & UART5_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

UART5_STATUS UART5_StatusGet (void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _UART5_H
/**
 End of File
*/