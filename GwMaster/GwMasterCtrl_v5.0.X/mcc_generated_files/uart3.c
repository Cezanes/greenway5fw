/**
  UART3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart3.c

  @Summary
    This is the generated driver implementation file for the UART3 driver using PIC32MX MCUs

  @Description
    This header file provides implementations for driver APIs for UART3.
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

/**
  Section: Included Files
*/
#include "uart3.h"

/**
  Section: UART3 APIs
*/

void UART3_Initialize(void)
{
    // Set the UART3 module to the options selected in the user interface.

    // STSEL 1S; IREN disabled; PDSEL 8N; RTSMD disabled; RXINV disabled; SIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; UEN TX_RX; ON enabled; 
    U3MODE = 0x8008;

    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; URXEN disabled; OERR disabled; ADM_EN disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U3STA = 0x0;

    // BaudRate = 115200; Frequency = 32000000 Hz; BRG 68; 
    U3BRG = 0x44;

    U3STAbits.UTXEN = 1;
    U3STAbits.URXEN = 1;

}


uint8_t UART3_Read(void)
{
    while(!(U3STAbits.URXDA == 1))
    {
        
    }

    if ((U3STAbits.OERR == 1))
    {
        U3STAbits.OERR = 0;
    }

    

    return U3RXREG;
}

void UART3_Write(uint8_t txData)
{
    while(U3STAbits.UTXBF == 1)
    {
        
    }

    U3TXREG = txData;    // Write the data byte to the USART.
}

UART3_STATUS UART3_StatusGet (void)
{
    return U3STA;
}


/**
  End of File
*/
