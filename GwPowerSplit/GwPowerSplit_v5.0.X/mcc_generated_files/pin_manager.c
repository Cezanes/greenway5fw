/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

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


/**
    Section: Includes
*/
#include <xc.h>
#include <sys/attribs.h>
#include "pin_manager.h"
#include "mcc.h"

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0400;
    LATE = 0x0000;
    LATF = 0x0000;
    LATG = 0x0080;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISB = 0x3FFF;
    TRISC = 0xF000;
    TRISD = 0x0BFF;
    TRISE = 0x00E7;
    TRISF = 0x003B;
    TRISG = 0x0340;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPDE = 0x0000;
    CNPDF = 0x0000;
    CNPDG = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;
    CNPUD = 0x0300;
    CNPUE = 0x0007;
    CNPUF = 0x003A;
    CNPUG = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELB = 0x0003;
    ANSELD = 0x0000;
    ANSELE = 0x0000;
    ANSELG = 0x0000;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    SYSTEM_RegUnlock(); // unlock PPS
    CFGCONbits.IOLOCK = 0;

    U1RXRbits.U1RXR = 0x0001;   //RG8->UART1:U1RX;
    RPG7Rbits.RPG7R = 0x0003;   //RG7->UART1:U1TX;

    CFGCONbits.IOLOCK = 1; // lock   PPS
    SYSTEM_RegLock(); 

    IEC1bits.CNBIE = 1; // Enable CNBI interrupt 
    
}
