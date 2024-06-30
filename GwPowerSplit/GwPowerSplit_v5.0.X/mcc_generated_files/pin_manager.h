/**
  System Interrupts Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.85.0
        Device            :  PIC32MX530F128H
        Version           :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB             :  MPLAB X 3.55

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATBbits.LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATBbits.LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    CMD_MAIN_HOT_SetHigh();
    </code>

*/
#define CMD_MAIN_HOT_SetHigh()          LATBbits.LATB14 = 1
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATBbits.LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATBbits.LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    CMD_MAIN_HOT_SetLow();
    </code>

*/
#define CMD_MAIN_HOT_SetLow()           LATBbits.LATB14 = 0
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATBbits.LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATBbits.LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    CMD_MAIN_HOT_Toggle();
    </code>

*/
#define CMD_MAIN_HOT_Toggle()           LATBbits.LATB14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = CMD_MAIN_HOT_GetValue();
    </code>

*/
#define CMD_MAIN_HOT_GetValue()         PORTBbits.RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    CMD_MAIN_HOT_SetDigitalInput();
    </code>

*/
#define CMD_MAIN_HOT_SetDigitalInput()  TRISBbits.TRISB14 = 1
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    CMD_MAIN_HOT_SetDigitalOutput();
    </code>

*/
#define CMD_MAIN_HOT_SetDigitalOutput() TRISBbits.TRISB14 = 0
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATBbits.LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATBbits.LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    CMD_MAIN_NEUTRAL_SetHigh();
    </code>

*/
#define CMD_MAIN_NEUTRAL_SetHigh()          LATBbits.LATB15 = 1
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATBbits.LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATBbits.LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    CMD_MAIN_NEUTRAL_SetLow();
    </code>

*/
#define CMD_MAIN_NEUTRAL_SetLow()           LATBbits.LATB15 = 0
/**
  @Summary
    Toggles the GPIO pin, RB15, using LATBbits.LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATBbits.LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    CMD_MAIN_NEUTRAL_Toggle();
    </code>

*/
#define CMD_MAIN_NEUTRAL_Toggle()           LATBbits.LATB15 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = CMD_MAIN_NEUTRAL_GetValue();
    </code>

*/
#define CMD_MAIN_NEUTRAL_GetValue()         PORTBbits.RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    CMD_MAIN_NEUTRAL_SetDigitalInput();
    </code>

*/
#define CMD_MAIN_NEUTRAL_SetDigitalInput()  TRISBbits.TRISB15 = 1
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    CMD_MAIN_NEUTRAL_SetDigitalOutput();
    </code>

*/
#define CMD_MAIN_NEUTRAL_SetDigitalOutput() TRISBbits.TRISB15 = 0
/**
  @Summary
    Sets the GPIO pin, RB4, high using LATBbits.LATB4.

  @Description
    Sets the GPIO pin, RB4, high using LATBbits.LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 high (1)
    SIG_SENSE_SetHigh();
    </code>

*/
#define SIG_SENSE_SetHigh()          LATBbits.LATB4 = 1
/**
  @Summary
    Sets the GPIO pin, RB4, low using LATBbits.LATB4.

  @Description
    Sets the GPIO pin, RB4, low using LATBbits.LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 low (0)
    SIG_SENSE_SetLow();
    </code>

*/
#define SIG_SENSE_SetLow()           LATBbits.LATB4 = 0
/**
  @Summary
    Toggles the GPIO pin, RB4, using LATBbits.LATB4.

  @Description
    Toggles the GPIO pin, RB4, using LATBbits.LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB4
    SIG_SENSE_Toggle();
    </code>

*/
#define SIG_SENSE_Toggle()           LATBbits.LATB4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB4.

  @Description
    Reads the value of the GPIO pin, RB4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB4
    postValue = SIG_SENSE_GetValue();
    </code>

*/
#define SIG_SENSE_GetValue()         PORTBbits.RB4
/**
  @Summary
    Configures the GPIO pin, RB4, as an input.

  @Description
    Configures the GPIO pin, RB4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an input
    SIG_SENSE_SetDigitalInput();
    </code>

*/
#define SIG_SENSE_SetDigitalInput()  TRISBbits.TRISB4 = 1
/**
  @Summary
    Configures the GPIO pin, RB4, as an output.

  @Description
    Configures the GPIO pin, RB4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an output
    SIG_SENSE_SetDigitalOutput();
    </code>

*/
#define SIG_SENSE_SetDigitalOutput() TRISBbits.TRISB4 = 0
/**
  @Summary
    Sets the GPIO pin, RD10, high using LATDbits.LATD10.

  @Description
    Sets the GPIO pin, RD10, high using LATDbits.LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD10 high (1)
    CANTX_SetHigh();
    </code>

*/
#define CANTX_SetHigh()          LATDbits.LATD10 = 1
/**
  @Summary
    Sets the GPIO pin, RD10, low using LATDbits.LATD10.

  @Description
    Sets the GPIO pin, RD10, low using LATDbits.LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD10 low (0)
    CANTX_SetLow();
    </code>

*/
#define CANTX_SetLow()           LATDbits.LATD10 = 0
/**
  @Summary
    Toggles the GPIO pin, RD10, using LATDbits.LATD10.

  @Description
    Toggles the GPIO pin, RD10, using LATDbits.LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD10
    CANTX_Toggle();
    </code>

*/
#define CANTX_Toggle()           LATDbits.LATD10 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD10.

  @Description
    Reads the value of the GPIO pin, RD10.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD10
    postValue = CANTX_GetValue();
    </code>

*/
#define CANTX_GetValue()         PORTDbits.RD10
/**
  @Summary
    Configures the GPIO pin, RD10, as an input.

  @Description
    Configures the GPIO pin, RD10, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD10 as an input
    CANTX_SetDigitalInput();
    </code>

*/
#define CANTX_SetDigitalInput()  TRISDbits.TRISD10 = 1
/**
  @Summary
    Configures the GPIO pin, RD10, as an output.

  @Description
    Configures the GPIO pin, RD10, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD10 as an output
    CANTX_SetDigitalOutput();
    </code>

*/
#define CANTX_SetDigitalOutput() TRISDbits.TRISD10 = 0
/**
  @Summary
    Sets the GPIO pin, RD11, high using LATDbits.LATD11.

  @Description
    Sets the GPIO pin, RD11, high using LATDbits.LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD11 high (1)
    CANRX_SetHigh();
    </code>

*/
#define CANRX_SetHigh()          LATDbits.LATD11 = 1
/**
  @Summary
    Sets the GPIO pin, RD11, low using LATDbits.LATD11.

  @Description
    Sets the GPIO pin, RD11, low using LATDbits.LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD11 low (0)
    CANRX_SetLow();
    </code>

*/
#define CANRX_SetLow()           LATDbits.LATD11 = 0
/**
  @Summary
    Toggles the GPIO pin, RD11, using LATDbits.LATD11.

  @Description
    Toggles the GPIO pin, RD11, using LATDbits.LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD11
    CANRX_Toggle();
    </code>

*/
#define CANRX_Toggle()           LATDbits.LATD11 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD11.

  @Description
    Reads the value of the GPIO pin, RD11.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD11
    postValue = CANRX_GetValue();
    </code>

*/
#define CANRX_GetValue()         PORTDbits.RD11
/**
  @Summary
    Configures the GPIO pin, RD11, as an input.

  @Description
    Configures the GPIO pin, RD11, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD11 as an input
    CANRX_SetDigitalInput();
    </code>

*/
#define CANRX_SetDigitalInput()  TRISDbits.TRISD11 = 1
/**
  @Summary
    Configures the GPIO pin, RD11, as an output.

  @Description
    Configures the GPIO pin, RD11, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD11 as an output
    CANRX_SetDigitalOutput();
    </code>

*/
#define CANRX_SetDigitalOutput() TRISDbits.TRISD11 = 0
/**
  @Summary
    Sets the GPIO pin, RE0, high using LATEbits.LATE0.

  @Description
    Sets the GPIO pin, RE0, high using LATEbits.LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE0 high (1)
    ADDR1_SetHigh();
    </code>

*/
#define ADDR1_SetHigh()          LATEbits.LATE0 = 1
/**
  @Summary
    Sets the GPIO pin, RE0, low using LATEbits.LATE0.

  @Description
    Sets the GPIO pin, RE0, low using LATEbits.LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE0 low (0)
    ADDR1_SetLow();
    </code>

*/
#define ADDR1_SetLow()           LATEbits.LATE0 = 0
/**
  @Summary
    Toggles the GPIO pin, RE0, using LATEbits.LATE0.

  @Description
    Toggles the GPIO pin, RE0, using LATEbits.LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE0
    ADDR1_Toggle();
    </code>

*/
#define ADDR1_Toggle()           LATEbits.LATE0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE0.

  @Description
    Reads the value of the GPIO pin, RE0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE0
    postValue = ADDR1_GetValue();
    </code>

*/
#define ADDR1_GetValue()         PORTEbits.RE0
/**
  @Summary
    Configures the GPIO pin, RE0, as an input.

  @Description
    Configures the GPIO pin, RE0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE0 as an input
    ADDR1_SetDigitalInput();
    </code>

*/
#define ADDR1_SetDigitalInput()  TRISEbits.TRISE0 = 1
/**
  @Summary
    Configures the GPIO pin, RE0, as an output.

  @Description
    Configures the GPIO pin, RE0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE0 as an output
    ADDR1_SetDigitalOutput();
    </code>

*/
#define ADDR1_SetDigitalOutput() TRISEbits.TRISE0 = 0
/**
  @Summary
    Sets the GPIO pin, RE1, high using LATEbits.LATE1.

  @Description
    Sets the GPIO pin, RE1, high using LATEbits.LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE1 high (1)
    ADDR2_SetHigh();
    </code>

*/
#define ADDR2_SetHigh()          LATEbits.LATE1 = 1
/**
  @Summary
    Sets the GPIO pin, RE1, low using LATEbits.LATE1.

  @Description
    Sets the GPIO pin, RE1, low using LATEbits.LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE1 low (0)
    ADDR2_SetLow();
    </code>

*/
#define ADDR2_SetLow()           LATEbits.LATE1 = 0
/**
  @Summary
    Toggles the GPIO pin, RE1, using LATEbits.LATE1.

  @Description
    Toggles the GPIO pin, RE1, using LATEbits.LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE1
    ADDR2_Toggle();
    </code>

*/
#define ADDR2_Toggle()           LATEbits.LATE1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE1.

  @Description
    Reads the value of the GPIO pin, RE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE1
    postValue = ADDR2_GetValue();
    </code>

*/
#define ADDR2_GetValue()         PORTEbits.RE1
/**
  @Summary
    Configures the GPIO pin, RE1, as an input.

  @Description
    Configures the GPIO pin, RE1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE1 as an input
    ADDR2_SetDigitalInput();
    </code>

*/
#define ADDR2_SetDigitalInput()  TRISEbits.TRISE1 = 1
/**
  @Summary
    Configures the GPIO pin, RE1, as an output.

  @Description
    Configures the GPIO pin, RE1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE1 as an output
    ADDR2_SetDigitalOutput();
    </code>

*/
#define ADDR2_SetDigitalOutput() TRISEbits.TRISE1 = 0
/**
  @Summary
    Sets the GPIO pin, RE2, high using LATEbits.LATE2.

  @Description
    Sets the GPIO pin, RE2, high using LATEbits.LATE2.

  @Preconditions
    The RE2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE2 high (1)
    ADDR3_SetHigh();
    </code>

*/
#define ADDR3_SetHigh()          LATEbits.LATE2 = 1
/**
  @Summary
    Sets the GPIO pin, RE2, low using LATEbits.LATE2.

  @Description
    Sets the GPIO pin, RE2, low using LATEbits.LATE2.

  @Preconditions
    The RE2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE2 low (0)
    ADDR3_SetLow();
    </code>

*/
#define ADDR3_SetLow()           LATEbits.LATE2 = 0
/**
  @Summary
    Toggles the GPIO pin, RE2, using LATEbits.LATE2.

  @Description
    Toggles the GPIO pin, RE2, using LATEbits.LATE2.

  @Preconditions
    The RE2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE2
    ADDR3_Toggle();
    </code>

*/
#define ADDR3_Toggle()           LATEbits.LATE2 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE2.

  @Description
    Reads the value of the GPIO pin, RE2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE2
    postValue = ADDR3_GetValue();
    </code>

*/
#define ADDR3_GetValue()         PORTEbits.RE2
/**
  @Summary
    Configures the GPIO pin, RE2, as an input.

  @Description
    Configures the GPIO pin, RE2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE2 as an input
    ADDR3_SetDigitalInput();
    </code>

*/
#define ADDR3_SetDigitalInput()  TRISEbits.TRISE2 = 1
/**
  @Summary
    Configures the GPIO pin, RE2, as an output.

  @Description
    Configures the GPIO pin, RE2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE2 as an output
    ADDR3_SetDigitalOutput();
    </code>

*/
#define ADDR3_SetDigitalOutput() TRISEbits.TRISE2 = 0
/**
  @Summary
    Sets the GPIO pin, RE3, high using LATEbits.LATE3.

  @Description
    Sets the GPIO pin, RE3, high using LATEbits.LATE3.

  @Preconditions
    The RE3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE3 high (1)
    LED_ERR_SetHigh();
    </code>

*/
#define LED_ERR_SetHigh()          LATEbits.LATE3 = 1
/**
  @Summary
    Sets the GPIO pin, RE3, low using LATEbits.LATE3.

  @Description
    Sets the GPIO pin, RE3, low using LATEbits.LATE3.

  @Preconditions
    The RE3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE3 low (0)
    LED_ERR_SetLow();
    </code>

*/
#define LED_ERR_SetLow()           LATEbits.LATE3 = 0
/**
  @Summary
    Toggles the GPIO pin, RE3, using LATEbits.LATE3.

  @Description
    Toggles the GPIO pin, RE3, using LATEbits.LATE3.

  @Preconditions
    The RE3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE3
    LED_ERR_Toggle();
    </code>

*/
#define LED_ERR_Toggle()           LATEbits.LATE3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE3.

  @Description
    Reads the value of the GPIO pin, RE3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE3
    postValue = LED_ERR_GetValue();
    </code>

*/
#define LED_ERR_GetValue()         PORTEbits.RE3
/**
  @Summary
    Configures the GPIO pin, RE3, as an input.

  @Description
    Configures the GPIO pin, RE3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE3 as an input
    LED_ERR_SetDigitalInput();
    </code>

*/
#define LED_ERR_SetDigitalInput()  TRISEbits.TRISE3 = 1
/**
  @Summary
    Configures the GPIO pin, RE3, as an output.

  @Description
    Configures the GPIO pin, RE3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE3 as an output
    LED_ERR_SetDigitalOutput();
    </code>

*/
#define LED_ERR_SetDigitalOutput() TRISEbits.TRISE3 = 0
/**
  @Summary
    Sets the GPIO pin, RE4, high using LATEbits.LATE4.

  @Description
    Sets the GPIO pin, RE4, high using LATEbits.LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE4 high (1)
    LED_WARN_SetHigh();
    </code>

*/
#define LED_WARN_SetHigh()          LATEbits.LATE4 = 1
/**
  @Summary
    Sets the GPIO pin, RE4, low using LATEbits.LATE4.

  @Description
    Sets the GPIO pin, RE4, low using LATEbits.LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE4 low (0)
    LED_WARN_SetLow();
    </code>

*/
#define LED_WARN_SetLow()           LATEbits.LATE4 = 0
/**
  @Summary
    Toggles the GPIO pin, RE4, using LATEbits.LATE4.

  @Description
    Toggles the GPIO pin, RE4, using LATEbits.LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE4
    LED_WARN_Toggle();
    </code>

*/
#define LED_WARN_Toggle()           LATEbits.LATE4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE4.

  @Description
    Reads the value of the GPIO pin, RE4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE4
    postValue = LED_WARN_GetValue();
    </code>

*/
#define LED_WARN_GetValue()         PORTEbits.RE4
/**
  @Summary
    Configures the GPIO pin, RE4, as an input.

  @Description
    Configures the GPIO pin, RE4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE4 as an input
    LED_WARN_SetDigitalInput();
    </code>

*/
#define LED_WARN_SetDigitalInput()  TRISEbits.TRISE4 = 1
/**
  @Summary
    Configures the GPIO pin, RE4, as an output.

  @Description
    Configures the GPIO pin, RE4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE4 as an output
    LED_WARN_SetDigitalOutput();
    </code>

*/
#define LED_WARN_SetDigitalOutput() TRISEbits.TRISE4 = 0
/**
  @Summary
    Sets the GPIO pin, RF1, high using LATFbits.LATF1.

  @Description
    Sets the GPIO pin, RF1, high using LATFbits.LATF1.

  @Preconditions
    The RF1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF1 high (1)
    ADDR0_SetHigh();
    </code>

*/
#define ADDR0_SetHigh()          LATFbits.LATF1 = 1
/**
  @Summary
    Sets the GPIO pin, RF1, low using LATFbits.LATF1.

  @Description
    Sets the GPIO pin, RF1, low using LATFbits.LATF1.

  @Preconditions
    The RF1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF1 low (0)
    ADDR0_SetLow();
    </code>

*/
#define ADDR0_SetLow()           LATFbits.LATF1 = 0
/**
  @Summary
    Toggles the GPIO pin, RF1, using LATFbits.LATF1.

  @Description
    Toggles the GPIO pin, RF1, using LATFbits.LATF1.

  @Preconditions
    The RF1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF1
    ADDR0_Toggle();
    </code>

*/
#define ADDR0_Toggle()           LATFbits.LATF1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF1.

  @Description
    Reads the value of the GPIO pin, RF1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF1
    postValue = ADDR0_GetValue();
    </code>

*/
#define ADDR0_GetValue()         PORTFbits.RF1
/**
  @Summary
    Configures the GPIO pin, RF1, as an input.

  @Description
    Configures the GPIO pin, RF1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF1 as an input
    ADDR0_SetDigitalInput();
    </code>

*/
#define ADDR0_SetDigitalInput()  TRISFbits.TRISF1 = 1
/**
  @Summary
    Configures the GPIO pin, RF1, as an output.

  @Description
    Configures the GPIO pin, RF1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF1 as an output
    ADDR0_SetDigitalOutput();
    </code>

*/
#define ADDR0_SetDigitalOutput() TRISFbits.TRISF1 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC32MX530F128H
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize(void);

#endif
