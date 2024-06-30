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


/**
    Section: Includes
*/
#include <xc.h>
#include <sys/attribs.h>
#include "pin_manager.h"
#include "mcc.h"

__attribute__ ((__weak__)) void ioc_D13_change(void)
{
   
}

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x51B2;
    LATC = 0x0000;
    LATD = 0x112A;
    LATE = 0x0000;
    LATF = 0x2022;
    LATG = 0x0341;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0xC63F;
    TRISB = 0x7D7F;
    TRISC = 0xF01E;
    TRISD = 0x6FD5;
    TRISE = 0x03FC;
    TRISF = 0x110F;
    TRISG = 0x80C2;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0800;
    CNPDE = 0x0000;
    CNPDF = 0x0000;
    CNPDG = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0010;
    CNPUC = 0x001E;
    CNPUD = 0x00C0;
    CNPUE = 0x00FC;
    CNPUF = 0x0001;
    CNPUG = 0x0040;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0600;
    ANSELB = 0x0401;
    ANSELC = 0x0000;
    ANSELD = 0x00C0;
    ANSELE = 0x0314;
    ANSELF = 0x0107;
    ANSELG = 0x8000;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    SYSTEM_RegUnlock(); // unlock PPS
    CFGCONbits.IOLOCK = 0;

    RPB7Rbits.RPB7R = 0x0002;   //RB7->UART4:U4TX;
    RPD15Rbits.RPD15R = 0x0001;   //RD15->UART2:U2TX;
    SDI3Rbits.SDI3R = 0x0000;   //RD2->SPI3:SDI3;
    RPG0Rbits.RPG0R = 0x0003;   //RG0->UART1:U1TX;
    U4RXRbits.U4RXR = 0x0005;   //RB6->UART4:U4RX;
    U2RXRbits.U2RXR = 0x000B;   //RD14->UART2:U2RX;
    U3RXRbits.U3RXR = 0x0001;   //RG7->UART3:U3RX;
    RPG8Rbits.RPG8R = 0x0001;   //RG8->UART3:U3TX;
    U5RXRbits.U5RXR = 0x0003;   //RD0->UART5:U5RX;
    RPD1Rbits.RPD1R = 0x0004;   //RD1->UART5:U5TX;
    RPD3Rbits.RPD3R = 0x000E;   //RD3->SPI3:SDO3;
    U1RXRbits.U1RXR = 0x000C;   //RG1->UART1:U1RX;

    C1RXRbits.C1RXR = 0x09;
    RPB9Rbits.RPB9R = 0x0C;
    U2RXRbits.U2RXR = 0x000B;   //RD14->UART2:U2RX;
    
    CFGCONbits.IOLOCK = 1; // lock   PPS
    SYSTEM_RegLock(); 
}

/* Interrupt service routine for the change notification interrupt. 
void __ISR (_CHANGE_NOTICE_VECTOR, IPL7AUTO) _CHANGE_NOTICE ( void )
{
    if(IFS1bits.CNDIF == 1)
    {
       // Clear the flag
       IFS1bits.CNDIF = 0;
       
       if(CNSTATDbits.CNSTATD13)
       {
          if(PORTD & (1 << 13))
            ioc_D13_change();
       }
    }
}
*/