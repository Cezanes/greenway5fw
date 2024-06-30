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
        Device            :  PIC32MX570F512L
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
    Sets the GPIO pin, RA6, high using LATAbits.LATA6.

  @Description
    Sets the GPIO pin, RA6, high using LATAbits.LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA6 high (1)
    LED_RED_SetHigh();
    </code>

*/
#define LED_RED_SetHigh()          LATAbits.LATA6 = 1
/**
  @Summary
    Sets the GPIO pin, RA6, low using LATAbits.LATA6.

  @Description
    Sets the GPIO pin, RA6, low using LATAbits.LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA6 low (0)
    LED_RED_SetLow();
    </code>

*/
#define LED_RED_SetLow()           LATAbits.LATA6 = 0
/**
  @Summary
    Toggles the GPIO pin, RA6, using LATAbits.LATA6.

  @Description
    Toggles the GPIO pin, RA6, using LATAbits.LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA6
    LED_RED_Toggle();
    </code>

*/
#define LED_RED_Toggle()           LATAbits.LATA6 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA6.

  @Description
    Reads the value of the GPIO pin, RA6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA6
    postValue = LED_RED_GetValue();
    </code>

*/
#define LED_RED_GetValue()         PORTAbits.RA6
/**
  @Summary
    Configures the GPIO pin, RA6, as an input.

  @Description
    Configures the GPIO pin, RA6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA6 as an input
    LED_RED_SetDigitalInput();
    </code>

*/
#define LED_RED_SetDigitalInput()  TRISAbits.TRISA6 = 1
/**
  @Summary
    Configures the GPIO pin, RA6, as an output.

  @Description
    Configures the GPIO pin, RA6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA6 as an output
    LED_RED_SetDigitalOutput();
    </code>

*/
#define LED_RED_SetDigitalOutput() TRISAbits.TRISA6 = 0
/**
  @Summary
    Sets the GPIO pin, RA7, high using LATAbits.LATA7.

  @Description
    Sets the GPIO pin, RA7, high using LATAbits.LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA7 high (1)
    LED_YELLOW_SetHigh();
    </code>

*/
#define LED_YELLOW_SetHigh()          LATAbits.LATA7 = 1
/**
  @Summary
    Sets the GPIO pin, RA7, low using LATAbits.LATA7.

  @Description
    Sets the GPIO pin, RA7, low using LATAbits.LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA7 low (0)
    LED_YELLOW_SetLow();
    </code>

*/
#define LED_YELLOW_SetLow()           LATAbits.LATA7 = 0
/**
  @Summary
    Toggles the GPIO pin, RA7, using LATAbits.LATA7.

  @Description
    Toggles the GPIO pin, RA7, using LATAbits.LATA7.

  @Preconditions
    The RA7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA7
    LED_YELLOW_Toggle();
    </code>

*/
#define LED_YELLOW_Toggle()           LATAbits.LATA7 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA7.

  @Description
    Reads the value of the GPIO pin, RA7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA7
    postValue = LED_YELLOW_GetValue();
    </code>

*/
#define LED_YELLOW_GetValue()         PORTAbits.RA7
/**
  @Summary
    Configures the GPIO pin, RA7, as an input.

  @Description
    Configures the GPIO pin, RA7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA7 as an input
    LED_YELLOW_SetDigitalInput();
    </code>

*/
#define LED_YELLOW_SetDigitalInput()  TRISAbits.TRISA7 = 1
/**
  @Summary
    Configures the GPIO pin, RA7, as an output.

  @Description
    Configures the GPIO pin, RA7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA7 as an output
    LED_YELLOW_SetDigitalOutput();
    </code>

*/
#define LED_YELLOW_SetDigitalOutput() TRISAbits.TRISA7 = 0
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
    IO_RB15_SetHigh();
    </code>

*/
#define IO_RB15_SetHigh()          LATBbits.LATB15 = 1
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
    IO_RB15_SetLow();
    </code>

*/
#define IO_RB15_SetLow()           LATBbits.LATB15 = 0
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
    IO_RB15_Toggle();
    </code>

*/
#define IO_RB15_Toggle()           LATBbits.LATB15 ^= 1
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
    postValue = IO_RB15_GetValue();
    </code>

*/
#define IO_RB15_GetValue()         PORTBbits.RB15
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
    IO_RB15_SetDigitalInput();
    </code>

*/
#define IO_RB15_SetDigitalInput()  TRISBbits.TRISB15 = 1
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
    IO_RB15_SetDigitalOutput();
    </code>

*/
#define IO_RB15_SetDigitalOutput() TRISBbits.TRISB15 = 0
/**
  @Summary
    Sets the GPIO pin, RB9, high using LATBbits.LATB9.

  @Description
    Sets the GPIO pin, RB9, high using LATBbits.LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB9 high (1)
    CANTX_SetHigh();
    </code>

*/
#define CANTX_SetHigh()          LATBbits.LATB9 = 1
/**
  @Summary
    Sets the GPIO pin, RB9, low using LATBbits.LATB9.

  @Description
    Sets the GPIO pin, RB9, low using LATBbits.LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB9 low (0)
    CANTX_SetLow();
    </code>

*/
#define CANTX_SetLow()           LATBbits.LATB9 = 0
/**
  @Summary
    Toggles the GPIO pin, RB9, using LATBbits.LATB9.

  @Description
    Toggles the GPIO pin, RB9, using LATBbits.LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB9
    CANTX_Toggle();
    </code>

*/
#define CANTX_Toggle()           LATBbits.LATB9 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB9.

  @Description
    Reads the value of the GPIO pin, RB9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB9
    postValue = CANTX_GetValue();
    </code>

*/
#define CANTX_GetValue()         PORTBbits.RB9
/**
  @Summary
    Configures the GPIO pin, RB9, as an input.

  @Description
    Configures the GPIO pin, RB9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB9 as an input
    CANTX_SetDigitalInput();
    </code>

*/
#define CANTX_SetDigitalInput()  TRISBbits.TRISB9 = 1
/**
  @Summary
    Configures the GPIO pin, RB9, as an output.

  @Description
    Configures the GPIO pin, RB9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB9 as an output
    CANTX_SetDigitalOutput();
    </code>

*/
#define CANTX_SetDigitalOutput() TRISBbits.TRISB9 = 0
/**
  @Summary
    Sets the GPIO pin, RC1, high using LATCbits.LATC1.

  @Description
    Sets the GPIO pin, RC1, high using LATCbits.LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC1 high (1)
    CFG4_SetHigh();
    </code>

*/
#define CFG4_SetHigh()          LATCbits.LATC1 = 1
/**
  @Summary
    Sets the GPIO pin, RC1, low using LATCbits.LATC1.

  @Description
    Sets the GPIO pin, RC1, low using LATCbits.LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC1 low (0)
    CFG4_SetLow();
    </code>

*/
#define CFG4_SetLow()           LATCbits.LATC1 = 0
/**
  @Summary
    Toggles the GPIO pin, RC1, using LATCbits.LATC1.

  @Description
    Toggles the GPIO pin, RC1, using LATCbits.LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC1
    CFG4_Toggle();
    </code>

*/
#define CFG4_Toggle()           LATCbits.LATC1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC1.

  @Description
    Reads the value of the GPIO pin, RC1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC1
    postValue = CFG4_GetValue();
    </code>

*/
#define CFG4_GetValue()         PORTCbits.RC1
/**
  @Summary
    Configures the GPIO pin, RC1, as an input.

  @Description
    Configures the GPIO pin, RC1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC1 as an input
    CFG4_SetDigitalInput();
    </code>

*/
#define CFG4_SetDigitalInput()  TRISCbits.TRISC1 = 1
/**
  @Summary
    Configures the GPIO pin, RC1, as an output.

  @Description
    Configures the GPIO pin, RC1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC1 as an output
    CFG4_SetDigitalOutput();
    </code>

*/
#define CFG4_SetDigitalOutput() TRISCbits.TRISC1 = 0
/**
  @Summary
    Sets the GPIO pin, RC2, high using LATCbits.LATC2.

  @Description
    Sets the GPIO pin, RC2, high using LATCbits.LATC2.

  @Preconditions
    The RC2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC2 high (1)
    CFG3_SetHigh();
    </code>

*/
#define CFG3_SetHigh()          LATCbits.LATC2 = 1
/**
  @Summary
    Sets the GPIO pin, RC2, low using LATCbits.LATC2.

  @Description
    Sets the GPIO pin, RC2, low using LATCbits.LATC2.

  @Preconditions
    The RC2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC2 low (0)
    CFG3_SetLow();
    </code>

*/
#define CFG3_SetLow()           LATCbits.LATC2 = 0
/**
  @Summary
    Toggles the GPIO pin, RC2, using LATCbits.LATC2.

  @Description
    Toggles the GPIO pin, RC2, using LATCbits.LATC2.

  @Preconditions
    The RC2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC2
    CFG3_Toggle();
    </code>

*/
#define CFG3_Toggle()           LATCbits.LATC2 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC2.

  @Description
    Reads the value of the GPIO pin, RC2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC2
    postValue = CFG3_GetValue();
    </code>

*/
#define CFG3_GetValue()         PORTCbits.RC2
/**
  @Summary
    Configures the GPIO pin, RC2, as an input.

  @Description
    Configures the GPIO pin, RC2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC2 as an input
    CFG3_SetDigitalInput();
    </code>

*/
#define CFG3_SetDigitalInput()  TRISCbits.TRISC2 = 1
/**
  @Summary
    Configures the GPIO pin, RC2, as an output.

  @Description
    Configures the GPIO pin, RC2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC2 as an output
    CFG3_SetDigitalOutput();
    </code>

*/
#define CFG3_SetDigitalOutput() TRISCbits.TRISC2 = 0
/**
  @Summary
    Sets the GPIO pin, RC3, high using LATCbits.LATC3.

  @Description
    Sets the GPIO pin, RC3, high using LATCbits.LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC3 high (1)
    CFG2_SetHigh();
    </code>

*/
#define CFG2_SetHigh()          LATCbits.LATC3 = 1
/**
  @Summary
    Sets the GPIO pin, RC3, low using LATCbits.LATC3.

  @Description
    Sets the GPIO pin, RC3, low using LATCbits.LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC3 low (0)
    CFG2_SetLow();
    </code>

*/
#define CFG2_SetLow()           LATCbits.LATC3 = 0
/**
  @Summary
    Toggles the GPIO pin, RC3, using LATCbits.LATC3.

  @Description
    Toggles the GPIO pin, RC3, using LATCbits.LATC3.

  @Preconditions
    The RC3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC3
    CFG2_Toggle();
    </code>

*/
#define CFG2_Toggle()           LATCbits.LATC3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC3.

  @Description
    Reads the value of the GPIO pin, RC3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC3
    postValue = CFG2_GetValue();
    </code>

*/
#define CFG2_GetValue()         PORTCbits.RC3
/**
  @Summary
    Configures the GPIO pin, RC3, as an input.

  @Description
    Configures the GPIO pin, RC3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC3 as an input
    CFG2_SetDigitalInput();
    </code>

*/
#define CFG2_SetDigitalInput()  TRISCbits.TRISC3 = 1
/**
  @Summary
    Configures the GPIO pin, RC3, as an output.

  @Description
    Configures the GPIO pin, RC3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC3 as an output
    CFG2_SetDigitalOutput();
    </code>

*/
#define CFG2_SetDigitalOutput() TRISCbits.TRISC3 = 0
/**
  @Summary
    Sets the GPIO pin, RC4, high using LATCbits.LATC4.

  @Description
    Sets the GPIO pin, RC4, high using LATCbits.LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC4 high (1)
    CFG1_SetHigh();
    </code>

*/
#define CFG1_SetHigh()          LATCbits.LATC4 = 1
/**
  @Summary
    Sets the GPIO pin, RC4, low using LATCbits.LATC4.

  @Description
    Sets the GPIO pin, RC4, low using LATCbits.LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC4 low (0)
    CFG1_SetLow();
    </code>

*/
#define CFG1_SetLow()           LATCbits.LATC4 = 0
/**
  @Summary
    Toggles the GPIO pin, RC4, using LATCbits.LATC4.

  @Description
    Toggles the GPIO pin, RC4, using LATCbits.LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC4
    CFG1_Toggle();
    </code>

*/
#define CFG1_Toggle()           LATCbits.LATC4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC4.

  @Description
    Reads the value of the GPIO pin, RC4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC4
    postValue = CFG1_GetValue();
    </code>

*/
#define CFG1_GetValue()         PORTCbits.RC4
/**
  @Summary
    Configures the GPIO pin, RC4, as an input.

  @Description
    Configures the GPIO pin, RC4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC4 as an input
    CFG1_SetDigitalInput();
    </code>

*/
#define CFG1_SetDigitalInput()  TRISCbits.TRISC4 = 1
/**
  @Summary
    Configures the GPIO pin, RC4, as an output.

  @Description
    Configures the GPIO pin, RC4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC4 as an output
    CFG1_SetDigitalOutput();
    </code>

*/
#define CFG1_SetDigitalOutput() TRISCbits.TRISC4 = 0
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
    IO_RD10_SetHigh();
    </code>

*/
#define IO_RD10_SetHigh()          LATDbits.LATD10 = 1
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
    IO_RD10_SetLow();
    </code>

*/
#define IO_RD10_SetLow()           LATDbits.LATD10 = 0
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
    IO_RD10_Toggle();
    </code>

*/
#define IO_RD10_Toggle()           LATDbits.LATD10 ^= 1
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
    postValue = IO_RD10_GetValue();
    </code>

*/
#define IO_RD10_GetValue()         PORTDbits.RD10
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
    IO_RD10_SetDigitalInput();
    </code>

*/
#define IO_RD10_SetDigitalInput()  TRISDbits.TRISD10 = 1
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
    IO_RD10_SetDigitalOutput();
    </code>

*/
#define IO_RD10_SetDigitalOutput() TRISDbits.TRISD10 = 0
/**
  @Summary
    Sets the GPIO pin, RD12, high using LATDbits.LATD12.

  @Description
    Sets the GPIO pin, RD12, high using LATDbits.LATD12.

  @Preconditions
    The RD12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD12 high (1)
    RTC_CS_SetHigh();
    </code>

*/
#define RTC_CS_SetHigh()          LATDbits.LATD12 = 1
/**
  @Summary
    Sets the GPIO pin, RD12, low using LATDbits.LATD12.

  @Description
    Sets the GPIO pin, RD12, low using LATDbits.LATD12.

  @Preconditions
    The RD12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD12 low (0)
    RTC_CS_SetLow();
    </code>

*/
#define RTC_CS_SetLow()           LATDbits.LATD12 = 0
/**
  @Summary
    Toggles the GPIO pin, RD12, using LATDbits.LATD12.

  @Description
    Toggles the GPIO pin, RD12, using LATDbits.LATD12.

  @Preconditions
    The RD12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD12
    RTC_CS_Toggle();
    </code>

*/
#define RTC_CS_Toggle()           LATDbits.LATD12 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD12.

  @Description
    Reads the value of the GPIO pin, RD12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD12
    postValue = RTC_CS_GetValue();
    </code>

*/
#define RTC_CS_GetValue()         PORTDbits.RD12
/**
  @Summary
    Configures the GPIO pin, RD12, as an input.

  @Description
    Configures the GPIO pin, RD12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD12 as an input
    RTC_CS_SetDigitalInput();
    </code>

*/
#define RTC_CS_SetDigitalInput()  TRISDbits.TRISD12 = 1
/**
  @Summary
    Configures the GPIO pin, RD12, as an output.

  @Description
    Configures the GPIO pin, RD12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD12 as an output
    RTC_CS_SetDigitalOutput();
    </code>

*/
#define RTC_CS_SetDigitalOutput() TRISDbits.TRISD12 = 0
/**
  @Summary
    Sets the GPIO pin, RD13, high using LATDbits.LATD13.

  @Description
    Sets the GPIO pin, RD13, high using LATDbits.LATD13.

  @Preconditions
    The RD13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD13 high (1)
    RFM_INT_SetHigh();
    </code>

*/
#define RFM_INT_SetHigh()          LATDbits.LATD13 = 1
/**
  @Summary
    Sets the GPIO pin, RD13, low using LATDbits.LATD13.

  @Description
    Sets the GPIO pin, RD13, low using LATDbits.LATD13.

  @Preconditions
    The RD13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD13 low (0)
    RFM_INT_SetLow();
    </code>

*/
#define RFM_INT_SetLow()           LATDbits.LATD13 = 0
/**
  @Summary
    Toggles the GPIO pin, RD13, using LATDbits.LATD13.

  @Description
    Toggles the GPIO pin, RD13, using LATDbits.LATD13.

  @Preconditions
    The RD13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD13
    RFM_INT_Toggle();
    </code>

*/
#define RFM_INT_Toggle()           LATDbits.LATD13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD13.

  @Description
    Reads the value of the GPIO pin, RD13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD13
    postValue = RFM_INT_GetValue();
    </code>

*/
#define RFM_INT_GetValue()         PORTDbits.RD13
/**
  @Summary
    Configures the GPIO pin, RD13, as an input.

  @Description
    Configures the GPIO pin, RD13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD13 as an input
    RFM_INT_SetDigitalInput();
    </code>

*/
#define RFM_INT_SetDigitalInput()  TRISDbits.TRISD13 = 1
/**
  @Summary
    Configures the GPIO pin, RD13, as an output.

  @Description
    Configures the GPIO pin, RD13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD13 as an output
    RFM_INT_SetDigitalOutput();
    </code>

*/
#define RFM_INT_SetDigitalOutput() TRISDbits.TRISD13 = 0
/**
  @Summary
    Sets the GPIO pin, RD2, high using LATDbits.LATD2.

  @Description
    Sets the GPIO pin, RD2, high using LATDbits.LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 high (1)
    SDI3_SetHigh();
    </code>

*/
#define SDI3_SetHigh()          LATDbits.LATD2 = 1
/**
  @Summary
    Sets the GPIO pin, RD2, low using LATDbits.LATD2.

  @Description
    Sets the GPIO pin, RD2, low using LATDbits.LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 low (0)
    SDI3_SetLow();
    </code>

*/
#define SDI3_SetLow()           LATDbits.LATD2 = 0
/**
  @Summary
    Toggles the GPIO pin, RD2, using LATDbits.LATD2.

  @Description
    Toggles the GPIO pin, RD2, using LATDbits.LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD2
    SDI3_Toggle();
    </code>

*/
#define SDI3_Toggle()           LATDbits.LATD2 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD2.

  @Description
    Reads the value of the GPIO pin, RD2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD2
    postValue = SDI3_GetValue();
    </code>

*/
#define SDI3_GetValue()         PORTDbits.RD2
/**
  @Summary
    Configures the GPIO pin, RD2, as an input.

  @Description
    Configures the GPIO pin, RD2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an input
    SDI3_SetDigitalInput();
    </code>

*/
#define SDI3_SetDigitalInput()  TRISDbits.TRISD2 = 1
/**
  @Summary
    Configures the GPIO pin, RD2, as an output.

  @Description
    Configures the GPIO pin, RD2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an output
    SDI3_SetDigitalOutput();
    </code>

*/
#define SDI3_SetDigitalOutput() TRISDbits.TRISD2 = 0
/**
  @Summary
    Sets the GPIO pin, RD3, high using LATDbits.LATD3.

  @Description
    Sets the GPIO pin, RD3, high using LATDbits.LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 high (1)
    SDO3_SetHigh();
    </code>

*/
#define SDO3_SetHigh()          LATDbits.LATD3 = 1
/**
  @Summary
    Sets the GPIO pin, RD3, low using LATDbits.LATD3.

  @Description
    Sets the GPIO pin, RD3, low using LATDbits.LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 low (0)
    SDO3_SetLow();
    </code>

*/
#define SDO3_SetLow()           LATDbits.LATD3 = 0
/**
  @Summary
    Toggles the GPIO pin, RD3, using LATDbits.LATD3.

  @Description
    Toggles the GPIO pin, RD3, using LATDbits.LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD3
    SDO3_Toggle();
    </code>

*/
#define SDO3_Toggle()           LATDbits.LATD3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD3.

  @Description
    Reads the value of the GPIO pin, RD3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD3
    postValue = SDO3_GetValue();
    </code>

*/
#define SDO3_GetValue()         PORTDbits.RD3
/**
  @Summary
    Configures the GPIO pin, RD3, as an input.

  @Description
    Configures the GPIO pin, RD3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an input
    SDO3_SetDigitalInput();
    </code>

*/
#define SDO3_SetDigitalInput()  TRISDbits.TRISD3 = 1
/**
  @Summary
    Configures the GPIO pin, RD3, as an output.

  @Description
    Configures the GPIO pin, RD3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an output
    SDO3_SetDigitalOutput();
    </code>

*/
#define SDO3_SetDigitalOutput() TRISDbits.TRISD3 = 0
/**
  @Summary
    Sets the GPIO pin, RD5, high using LATDbits.LATD5.

  @Description
    Sets the GPIO pin, RD5, high using LATDbits.LATD5.

  @Preconditions
    The RD5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD5 high (1)
    RFM_CS_SetHigh();
    </code>

*/
#define RFM_CS_SetHigh()          LATDbits.LATD5 = 1
/**
  @Summary
    Sets the GPIO pin, RD5, low using LATDbits.LATD5.

  @Description
    Sets the GPIO pin, RD5, low using LATDbits.LATD5.

  @Preconditions
    The RD5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD5 low (0)
    RFM_CS_SetLow();
    </code>

*/
#define RFM_CS_SetLow()           LATDbits.LATD5 = 0
/**
  @Summary
    Toggles the GPIO pin, RD5, using LATDbits.LATD5.

  @Description
    Toggles the GPIO pin, RD5, using LATDbits.LATD5.

  @Preconditions
    The RD5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD5
    RFM_CS_Toggle();
    </code>

*/
#define RFM_CS_Toggle()           LATDbits.LATD5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD5.

  @Description
    Reads the value of the GPIO pin, RD5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD5
    postValue = RFM_CS_GetValue();
    </code>

*/
#define RFM_CS_GetValue()         PORTDbits.RD5
/**
  @Summary
    Configures the GPIO pin, RD5, as an input.

  @Description
    Configures the GPIO pin, RD5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD5 as an input
    RFM_CS_SetDigitalInput();
    </code>

*/
#define RFM_CS_SetDigitalInput()  TRISDbits.TRISD5 = 1
/**
  @Summary
    Configures the GPIO pin, RD5, as an output.

  @Description
    Configures the GPIO pin, RD5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD5 as an output
    RFM_CS_SetDigitalOutput();
    </code>

*/
#define RFM_CS_SetDigitalOutput() TRISDbits.TRISD5 = 0
/**
  @Summary
    Sets the GPIO pin, RD9, high using LATDbits.LATD9.

  @Description
    Sets the GPIO pin, RD9, high using LATDbits.LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD9 high (1)
    IO_RD9_SetHigh();
    </code>

*/
#define IO_RD9_SetHigh()          LATDbits.LATD9 = 1
/**
  @Summary
    Sets the GPIO pin, RD9, low using LATDbits.LATD9.

  @Description
    Sets the GPIO pin, RD9, low using LATDbits.LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD9 low (0)
    IO_RD9_SetLow();
    </code>

*/
#define IO_RD9_SetLow()           LATDbits.LATD9 = 0
/**
  @Summary
    Toggles the GPIO pin, RD9, using LATDbits.LATD9.

  @Description
    Toggles the GPIO pin, RD9, using LATDbits.LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD9
    IO_RD9_Toggle();
    </code>

*/
#define IO_RD9_Toggle()           LATDbits.LATD9 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD9.

  @Description
    Reads the value of the GPIO pin, RD9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD9
    postValue = IO_RD9_GetValue();
    </code>

*/
#define IO_RD9_GetValue()         PORTDbits.RD9
/**
  @Summary
    Configures the GPIO pin, RD9, as an input.

  @Description
    Configures the GPIO pin, RD9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD9 as an input
    IO_RD9_SetDigitalInput();
    </code>

*/
#define IO_RD9_SetDigitalInput()  TRISDbits.TRISD9 = 1
/**
  @Summary
    Configures the GPIO pin, RD9, as an output.

  @Description
    Configures the GPIO pin, RD9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD9 as an output
    IO_RD9_SetDigitalOutput();
    </code>

*/
#define IO_RD9_SetDigitalOutput() TRISDbits.TRISD9 = 0
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
    IO_RE0_SetHigh();
    </code>

*/
#define IO_RE0_SetHigh()          LATEbits.LATE0 = 1
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
    IO_RE0_SetLow();
    </code>

*/
#define IO_RE0_SetLow()           LATEbits.LATE0 = 0
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
    IO_RE0_Toggle();
    </code>

*/
#define IO_RE0_Toggle()           LATEbits.LATE0 ^= 1
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
    postValue = IO_RE0_GetValue();
    </code>

*/
#define IO_RE0_GetValue()         PORTEbits.RE0
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
    IO_RE0_SetDigitalInput();
    </code>

*/
#define IO_RE0_SetDigitalInput()  TRISEbits.TRISE0 = 1
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
    IO_RE0_SetDigitalOutput();
    </code>

*/
#define IO_RE0_SetDigitalOutput() TRISEbits.TRISE0 = 0
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
    LED_GPS_SetHigh();
    </code>

*/
#define LED_GPS_SetHigh()          LATEbits.LATE1 = 1
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
    LED_GPS_SetLow();
    </code>

*/
#define LED_GPS_SetLow()           LATEbits.LATE1 = 0
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
    LED_GPS_Toggle();
    </code>

*/
#define LED_GPS_Toggle()           LATEbits.LATE1 ^= 1
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
    postValue = LED_GPS_GetValue();
    </code>

*/
#define LED_GPS_GetValue()         PORTEbits.RE1
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
    LED_GPS_SetDigitalInput();
    </code>

*/
#define LED_GPS_SetDigitalInput()  TRISEbits.TRISE1 = 1
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
    LED_GPS_SetDigitalOutput();
    </code>

*/
#define LED_GPS_SetDigitalOutput() TRISEbits.TRISE1 = 0
/**
  @Summary
    Sets the GPIO pin, RE5, high using LATEbits.LATE5.

  @Description
    Sets the GPIO pin, RE5, high using LATEbits.LATE5.

  @Preconditions
    The RE5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE5 high (1)
    CFG7_SetHigh();
    </code>

*/
#define CFG7_SetHigh()          LATEbits.LATE5 = 1
/**
  @Summary
    Sets the GPIO pin, RE5, low using LATEbits.LATE5.

  @Description
    Sets the GPIO pin, RE5, low using LATEbits.LATE5.

  @Preconditions
    The RE5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE5 low (0)
    CFG7_SetLow();
    </code>

*/
#define CFG7_SetLow()           LATEbits.LATE5 = 0
/**
  @Summary
    Toggles the GPIO pin, RE5, using LATEbits.LATE5.

  @Description
    Toggles the GPIO pin, RE5, using LATEbits.LATE5.

  @Preconditions
    The RE5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE5
    CFG7_Toggle();
    </code>

*/
#define CFG7_Toggle()           LATEbits.LATE5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE5.

  @Description
    Reads the value of the GPIO pin, RE5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE5
    postValue = CFG7_GetValue();
    </code>

*/
#define CFG7_GetValue()         PORTEbits.RE5
/**
  @Summary
    Configures the GPIO pin, RE5, as an input.

  @Description
    Configures the GPIO pin, RE5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE5 as an input
    CFG7_SetDigitalInput();
    </code>

*/
#define CFG7_SetDigitalInput()  TRISEbits.TRISE5 = 1
/**
  @Summary
    Configures the GPIO pin, RE5, as an output.

  @Description
    Configures the GPIO pin, RE5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE5 as an output
    CFG7_SetDigitalOutput();
    </code>

*/
#define CFG7_SetDigitalOutput() TRISEbits.TRISE5 = 0
/**
  @Summary
    Sets the GPIO pin, RE6, high using LATEbits.LATE6.

  @Description
    Sets the GPIO pin, RE6, high using LATEbits.LATE6.

  @Preconditions
    The RE6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE6 high (1)
    CFG6_SetHigh();
    </code>

*/
#define CFG6_SetHigh()          LATEbits.LATE6 = 1
/**
  @Summary
    Sets the GPIO pin, RE6, low using LATEbits.LATE6.

  @Description
    Sets the GPIO pin, RE6, low using LATEbits.LATE6.

  @Preconditions
    The RE6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE6 low (0)
    CFG6_SetLow();
    </code>

*/
#define CFG6_SetLow()           LATEbits.LATE6 = 0
/**
  @Summary
    Toggles the GPIO pin, RE6, using LATEbits.LATE6.

  @Description
    Toggles the GPIO pin, RE6, using LATEbits.LATE6.

  @Preconditions
    The RE6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE6
    CFG6_Toggle();
    </code>

*/
#define CFG6_Toggle()           LATEbits.LATE6 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE6.

  @Description
    Reads the value of the GPIO pin, RE6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE6
    postValue = CFG6_GetValue();
    </code>

*/
#define CFG6_GetValue()         PORTEbits.RE6
/**
  @Summary
    Configures the GPIO pin, RE6, as an input.

  @Description
    Configures the GPIO pin, RE6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE6 as an input
    CFG6_SetDigitalInput();
    </code>

*/
#define CFG6_SetDigitalInput()  TRISEbits.TRISE6 = 1
/**
  @Summary
    Configures the GPIO pin, RE6, as an output.

  @Description
    Configures the GPIO pin, RE6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE6 as an output
    CFG6_SetDigitalOutput();
    </code>

*/
#define CFG6_SetDigitalOutput() TRISEbits.TRISE6 = 0
/**
  @Summary
    Sets the GPIO pin, RE7, high using LATEbits.LATE7.

  @Description
    Sets the GPIO pin, RE7, high using LATEbits.LATE7.

  @Preconditions
    The RE7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE7 high (1)
    CFG5_SetHigh();
    </code>

*/
#define CFG5_SetHigh()          LATEbits.LATE7 = 1
/**
  @Summary
    Sets the GPIO pin, RE7, low using LATEbits.LATE7.

  @Description
    Sets the GPIO pin, RE7, low using LATEbits.LATE7.

  @Preconditions
    The RE7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE7 low (0)
    CFG5_SetLow();
    </code>

*/
#define CFG5_SetLow()           LATEbits.LATE7 = 0
/**
  @Summary
    Toggles the GPIO pin, RE7, using LATEbits.LATE7.

  @Description
    Toggles the GPIO pin, RE7, using LATEbits.LATE7.

  @Preconditions
    The RE7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE7
    CFG5_Toggle();
    </code>

*/
#define CFG5_Toggle()           LATEbits.LATE7 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RE7.

  @Description
    Reads the value of the GPIO pin, RE7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE7
    postValue = CFG5_GetValue();
    </code>

*/
#define CFG5_GetValue()         PORTEbits.RE7
/**
  @Summary
    Configures the GPIO pin, RE7, as an input.

  @Description
    Configures the GPIO pin, RE7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE7 as an input
    CFG5_SetDigitalInput();
    </code>

*/
#define CFG5_SetDigitalInput()  TRISEbits.TRISE7 = 1
/**
  @Summary
    Configures the GPIO pin, RE7, as an output.

  @Description
    Configures the GPIO pin, RE7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE7 as an output
    CFG5_SetDigitalOutput();
    </code>

*/
#define CFG5_SetDigitalOutput() TRISEbits.TRISE7 = 0
/**
  @Summary
    Sets the GPIO pin, RF12, high using LATFbits.LATF12.

  @Description
    Sets the GPIO pin, RF12, high using LATFbits.LATF12.

  @Preconditions
    The RF12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF12 high (1)
    CANRX_SetHigh();
    </code>

*/
#define CANRX_SetHigh()          LATFbits.LATF12 = 1
/**
  @Summary
    Sets the GPIO pin, RF12, low using LATFbits.LATF12.

  @Description
    Sets the GPIO pin, RF12, low using LATFbits.LATF12.

  @Preconditions
    The RF12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF12 low (0)
    CANRX_SetLow();
    </code>

*/
#define CANRX_SetLow()           LATFbits.LATF12 = 0
/**
  @Summary
    Toggles the GPIO pin, RF12, using LATFbits.LATF12.

  @Description
    Toggles the GPIO pin, RF12, using LATFbits.LATF12.

  @Preconditions
    The RF12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF12
    CANRX_Toggle();
    </code>

*/
#define CANRX_Toggle()           LATFbits.LATF12 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF12.

  @Description
    Reads the value of the GPIO pin, RF12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF12
    postValue = CANRX_GetValue();
    </code>

*/
#define CANRX_GetValue()         PORTFbits.RF12
/**
  @Summary
    Configures the GPIO pin, RF12, as an input.

  @Description
    Configures the GPIO pin, RF12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF12 as an input
    CANRX_SetDigitalInput();
    </code>

*/
#define CANRX_SetDigitalInput()  TRISFbits.TRISF12 = 1
/**
  @Summary
    Configures the GPIO pin, RF12, as an output.

  @Description
    Configures the GPIO pin, RF12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF12 as an output
    CANRX_SetDigitalOutput();
    </code>

*/
#define CANRX_SetDigitalOutput() TRISFbits.TRISF12 = 0
/**
  @Summary
    Sets the GPIO pin, RF13, high using LATFbits.LATF13.

  @Description
    Sets the GPIO pin, RF13, high using LATFbits.LATF13.

  @Preconditions
    The RF13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF13 high (1)
    SCK3_SetHigh();
    </code>

*/
#define SCK3_SetHigh()          LATFbits.LATF13 = 1
/**
  @Summary
    Sets the GPIO pin, RF13, low using LATFbits.LATF13.

  @Description
    Sets the GPIO pin, RF13, low using LATFbits.LATF13.

  @Preconditions
    The RF13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF13 low (0)
    SCK3_SetLow();
    </code>

*/
#define SCK3_SetLow()           LATFbits.LATF13 = 0
/**
  @Summary
    Toggles the GPIO pin, RF13, using LATFbits.LATF13.

  @Description
    Toggles the GPIO pin, RF13, using LATFbits.LATF13.

  @Preconditions
    The RF13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF13
    SCK3_Toggle();
    </code>

*/
#define SCK3_Toggle()           LATFbits.LATF13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF13.

  @Description
    Reads the value of the GPIO pin, RF13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF13
    postValue = SCK3_GetValue();
    </code>

*/
#define SCK3_GetValue()         PORTFbits.RF13
/**
  @Summary
    Configures the GPIO pin, RF13, as an input.

  @Description
    Configures the GPIO pin, RF13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF13 as an input
    SCK3_SetDigitalInput();
    </code>

*/
#define SCK3_SetDigitalInput()  TRISFbits.TRISF13 = 1
/**
  @Summary
    Configures the GPIO pin, RF13, as an output.

  @Description
    Configures the GPIO pin, RF13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF13 as an output
    SCK3_SetDigitalOutput();
    </code>

*/
#define SCK3_SetDigitalOutput() TRISFbits.TRISF13 = 0
/**
  @Summary
    Sets the GPIO pin, RF4, high using LATFbits.LATF4.

  @Description
    Sets the GPIO pin, RF4, high using LATFbits.LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF4 high (1)
    IO_RF4_SetHigh();
    </code>

*/
#define IO_RF4_SetHigh()          LATFbits.LATF4 = 1
/**
  @Summary
    Sets the GPIO pin, RF4, low using LATFbits.LATF4.

  @Description
    Sets the GPIO pin, RF4, low using LATFbits.LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF4 low (0)
    IO_RF4_SetLow();
    </code>

*/
#define IO_RF4_SetLow()           LATFbits.LATF4 = 0
/**
  @Summary
    Toggles the GPIO pin, RF4, using LATFbits.LATF4.

  @Description
    Toggles the GPIO pin, RF4, using LATFbits.LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF4
    IO_RF4_Toggle();
    </code>

*/
#define IO_RF4_Toggle()           LATFbits.LATF4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF4.

  @Description
    Reads the value of the GPIO pin, RF4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF4
    postValue = IO_RF4_GetValue();
    </code>

*/
#define IO_RF4_GetValue()         PORTFbits.RF4
/**
  @Summary
    Configures the GPIO pin, RF4, as an input.

  @Description
    Configures the GPIO pin, RF4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF4 as an input
    IO_RF4_SetDigitalInput();
    </code>

*/
#define IO_RF4_SetDigitalInput()  TRISFbits.TRISF4 = 1
/**
  @Summary
    Configures the GPIO pin, RF4, as an output.

  @Description
    Configures the GPIO pin, RF4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF4 as an output
    IO_RF4_SetDigitalOutput();
    </code>

*/
#define IO_RF4_SetDigitalOutput() TRISFbits.TRISF4 = 0
/**
  @Summary
    Sets the GPIO pin, RF5, high using LATFbits.LATF5.

  @Description
    Sets the GPIO pin, RF5, high using LATFbits.LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF5 high (1)
    IO_RF5_SetHigh();
    </code>

*/
#define IO_RF5_SetHigh()          LATFbits.LATF5 = 1
/**
  @Summary
    Sets the GPIO pin, RF5, low using LATFbits.LATF5.

  @Description
    Sets the GPIO pin, RF5, low using LATFbits.LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF5 low (0)
    IO_RF5_SetLow();
    </code>

*/
#define IO_RF5_SetLow()           LATFbits.LATF5 = 0
/**
  @Summary
    Toggles the GPIO pin, RF5, using LATFbits.LATF5.

  @Description
    Toggles the GPIO pin, RF5, using LATFbits.LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF5
    IO_RF5_Toggle();
    </code>

*/
#define IO_RF5_Toggle()           LATFbits.LATF5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF5.

  @Description
    Reads the value of the GPIO pin, RF5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF5
    postValue = IO_RF5_GetValue();
    </code>

*/
#define IO_RF5_GetValue()         PORTFbits.RF5
/**
  @Summary
    Configures the GPIO pin, RF5, as an input.

  @Description
    Configures the GPIO pin, RF5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF5 as an input
    IO_RF5_SetDigitalInput();
    </code>

*/
#define IO_RF5_SetDigitalInput()  TRISFbits.TRISF5 = 1
/**
  @Summary
    Configures the GPIO pin, RF5, as an output.

  @Description
    Configures the GPIO pin, RF5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF5 as an output
    IO_RF5_SetDigitalOutput();
    </code>

*/
#define IO_RF5_SetDigitalOutput() TRISFbits.TRISF5 = 0
/**
  @Summary
    Sets the GPIO pin, RG12, high using LATGbits.LATG12.

  @Description
    Sets the GPIO pin, RG12, high using LATGbits.LATG12.

  @Preconditions
    The RG12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG12 high (1)
    LED_LORA_SetHigh();
    </code>

*/
#define LED_LORA_SetHigh()          LATGbits.LATG12 = 1
/**
  @Summary
    Sets the GPIO pin, RG12, low using LATGbits.LATG12.

  @Description
    Sets the GPIO pin, RG12, low using LATGbits.LATG12.

  @Preconditions
    The RG12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG12 low (0)
    LED_LORA_SetLow();
    </code>

*/
#define LED_LORA_SetLow()           LATGbits.LATG12 = 0
/**
  @Summary
    Toggles the GPIO pin, RG12, using LATGbits.LATG12.

  @Description
    Toggles the GPIO pin, RG12, using LATGbits.LATG12.

  @Preconditions
    The RG12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG12
    LED_LORA_Toggle();
    </code>

*/
#define LED_LORA_Toggle()           LATGbits.LATG12 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG12.

  @Description
    Reads the value of the GPIO pin, RG12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG12
    postValue = LED_LORA_GetValue();
    </code>

*/
#define LED_LORA_GetValue()         PORTGbits.RG12
/**
  @Summary
    Configures the GPIO pin, RG12, as an input.

  @Description
    Configures the GPIO pin, RG12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG12 as an input
    LED_LORA_SetDigitalInput();
    </code>

*/
#define LED_LORA_SetDigitalInput()  TRISGbits.TRISG12 = 1
/**
  @Summary
    Configures the GPIO pin, RG12, as an output.

  @Description
    Configures the GPIO pin, RG12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG12 as an output
    LED_LORA_SetDigitalOutput();
    </code>

*/
#define LED_LORA_SetDigitalOutput() TRISGbits.TRISG12 = 0
/**
  @Summary
    Sets the GPIO pin, RG13, high using LATGbits.LATG13.

  @Description
    Sets the GPIO pin, RG13, high using LATGbits.LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG13 high (1)
    LED_SERVER_SetHigh();
    </code>

*/
#define LED_SERVER_SetHigh()          LATGbits.LATG13 = 1
/**
  @Summary
    Sets the GPIO pin, RG13, low using LATGbits.LATG13.

  @Description
    Sets the GPIO pin, RG13, low using LATGbits.LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG13 low (0)
    LED_SERVER_SetLow();
    </code>

*/
#define LED_SERVER_SetLow()           LATGbits.LATG13 = 0
/**
  @Summary
    Toggles the GPIO pin, RG13, using LATGbits.LATG13.

  @Description
    Toggles the GPIO pin, RG13, using LATGbits.LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG13
    LED_SERVER_Toggle();
    </code>

*/
#define LED_SERVER_Toggle()           LATGbits.LATG13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG13.

  @Description
    Reads the value of the GPIO pin, RG13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG13
    postValue = LED_SERVER_GetValue();
    </code>

*/
#define LED_SERVER_GetValue()         PORTGbits.RG13
/**
  @Summary
    Configures the GPIO pin, RG13, as an input.

  @Description
    Configures the GPIO pin, RG13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG13 as an input
    LED_SERVER_SetDigitalInput();
    </code>

*/
#define LED_SERVER_SetDigitalInput()  TRISGbits.TRISG13 = 1
/**
  @Summary
    Configures the GPIO pin, RG13, as an output.

  @Description
    Configures the GPIO pin, RG13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG13 as an output
    LED_SERVER_SetDigitalOutput();
    </code>

*/
#define LED_SERVER_SetDigitalOutput() TRISGbits.TRISG13 = 0
/**
  @Summary
    Sets the GPIO pin, RG14, high using LATGbits.LATG14.

  @Description
    Sets the GPIO pin, RG14, high using LATGbits.LATG14.

  @Preconditions
    The RG14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG14 high (1)
    LED_GSM_SetHigh();
    </code>

*/
#define LED_GSM_SetHigh()          LATGbits.LATG14 = 1
/**
  @Summary
    Sets the GPIO pin, RG14, low using LATGbits.LATG14.

  @Description
    Sets the GPIO pin, RG14, low using LATGbits.LATG14.

  @Preconditions
    The RG14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG14 low (0)
    LED_GSM_SetLow();
    </code>

*/
#define LED_GSM_SetLow()           LATGbits.LATG14 = 0
/**
  @Summary
    Toggles the GPIO pin, RG14, using LATGbits.LATG14.

  @Description
    Toggles the GPIO pin, RG14, using LATGbits.LATG14.

  @Preconditions
    The RG14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG14
    LED_GSM_Toggle();
    </code>

*/
#define LED_GSM_Toggle()           LATGbits.LATG14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG14.

  @Description
    Reads the value of the GPIO pin, RG14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG14
    postValue = LED_GSM_GetValue();
    </code>

*/
#define LED_GSM_GetValue()         PORTGbits.RG14
/**
  @Summary
    Configures the GPIO pin, RG14, as an input.

  @Description
    Configures the GPIO pin, RG14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG14 as an input
    LED_GSM_SetDigitalInput();
    </code>

*/
#define LED_GSM_SetDigitalInput()  TRISGbits.TRISG14 = 1
/**
  @Summary
    Configures the GPIO pin, RG14, as an output.

  @Description
    Configures the GPIO pin, RG14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG14 as an output
    LED_GSM_SetDigitalOutput();
    </code>

*/
#define LED_GSM_SetDigitalOutput() TRISGbits.TRISG14 = 0
/**
  @Summary
    Sets the GPIO pin, RG6, high using LATGbits.LATG6.

  @Description
    Sets the GPIO pin, RG6, high using LATGbits.LATG6.

  @Preconditions
    The RG6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG6 high (1)
    CFG0_SetHigh();
    </code>

*/
#define CFG0_SetHigh()          LATGbits.LATG6 = 1
/**
  @Summary
    Sets the GPIO pin, RG6, low using LATGbits.LATG6.

  @Description
    Sets the GPIO pin, RG6, low using LATGbits.LATG6.

  @Preconditions
    The RG6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG6 low (0)
    CFG0_SetLow();
    </code>

*/
#define CFG0_SetLow()           LATGbits.LATG6 = 0
/**
  @Summary
    Toggles the GPIO pin, RG6, using LATGbits.LATG6.

  @Description
    Toggles the GPIO pin, RG6, using LATGbits.LATG6.

  @Preconditions
    The RG6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG6
    CFG0_Toggle();
    </code>

*/
#define CFG0_Toggle()           LATGbits.LATG6 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG6.

  @Description
    Reads the value of the GPIO pin, RG6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG6
    postValue = CFG0_GetValue();
    </code>

*/
#define CFG0_GetValue()         PORTGbits.RG6
/**
  @Summary
    Configures the GPIO pin, RG6, as an input.

  @Description
    Configures the GPIO pin, RG6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG6 as an input
    CFG0_SetDigitalInput();
    </code>

*/
#define CFG0_SetDigitalInput()  TRISGbits.TRISG6 = 1
/**
  @Summary
    Configures the GPIO pin, RG6, as an output.

  @Description
    Configures the GPIO pin, RG6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG6 as an output
    CFG0_SetDigitalOutput();
    </code>

*/
#define CFG0_SetDigitalOutput() TRISGbits.TRISG6 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC32MX570F512L
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
