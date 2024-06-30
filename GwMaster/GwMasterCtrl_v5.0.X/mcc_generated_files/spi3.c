
/**
  SPI3 Generated Driver API Source File

  Company:
    Microchip Technology Inc.

  File Name:
    spi3.c

  @Summary
    This is the generated source file for the SPI3 driver using PIC32MX MCUs

  @Description
    This source file provides APIs for driver for SPI3.
    Generation Information :
        Product Revision  :  PIC32MX MCUs - pic32mx : v1.35
        Device            :  PIC32MX570F512L
        Driver Version    :  0.5
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

#include <xc.h>
#include "spi3.h"

/**
 Section: File specific functions
*/

void SPI3_Exchange( uint8_t *pTransmitData, uint8_t *pReceiveData );
uint16_t SPI3_ExchangeBuffer(uint8_t *pTransmitData, uint16_t byteCount, uint8_t *pReceiveData);

/**
 Section: Driver Interface Function Definitions
*/


void SPI3_Initialize (void)
{
    // FRMERR disabled; 
    SPI3STAT = 0x0;
    // SPI3BRG 3; 
    SPI3BRG = 0x3;
    // AUDMONO disabled; AUDEN disabled; SPITUREN disabled; FRMERREN disabled; IGNROV disabled; SPISGNEXT disabled; SPIROVEN disabled; AUDMOD disabled; IGNTUR disabled; 
    SPI3CON2 = 0x0;
    // MCLKSEL PBCLK; DISSDO disabled; SRXISEL Last Word is Read; CKP Idle:High, Active:Low; FRMEN disabled; FRMSYPW One-Clock; SSEN disabled; FRMCNT 1; MSSEN disabled; MSTEN Master; MODE16 disabled; FRMPOL disabled; SMP Middle; SIDL disabled; FRMSYNC disabled; CKE Idle to Active; MODE32 disabled; SPIFE Frame Sync pulse precedes; STXISEL Complete; DISSDI disabled; ON enabled; ENHBUF enabled; 
    SPI3CON = 0x18060;

}


void SPI3_Exchange( uint8_t *pTransmitData, uint8_t *pReceiveData )
{

    while( SPI3STATbits.SPITBF == true )
    {

    }

    SPI3BUF = *((uint8_t*)pTransmitData);

    while ( SPI3STATbits.SPIRBE == true)
    {
    
    }

    *((uint8_t*)pReceiveData) = SPI3BUF;

}

uint16_t SPI3_ExchangeBuffer(uint8_t *pTransmitData, uint16_t byteCount, uint8_t *pReceiveData)
{

    uint16_t dataSentCount = 0;
    uint16_t count = 0;
    uint32_t dummyDataReceived = 0;
    uint32_t dummyDataTransmit = SPI3_DUMMY_DATA;

    uint8_t  *pSend, *pReceived;


    // set the pointers for transmit and receive operations
    if (pTransmitData == NULL)
    {
        pSend = (uint8_t*)&dummyDataTransmit;
    }
    else
    {
        pSend = (uint8_t*)pTransmitData;
    }
        
    if (pReceiveData == NULL)
    {
       pReceived = (uint8_t*)&dummyDataReceived;
    }
    else
    {
       pReceived = (uint8_t*)pReceiveData;
    }


    while( SPI3STATbits.SPITBF == true )
    {

    }

    while (dataSentCount < byteCount)
    {
        if ((count < ((SPI3_FIFO_FILL_LIMIT)*4)))
        {
            SPI3BUF = *pSend;
            pSend += 1;
            dataSentCount++;
            count++;
        }

        if (SPI3STATbits.SPIRBE == false)
        {
            *pReceived = SPI3BUF;
            pReceived += 1;
            count--;
        }

    }
    while (count)
    {
        if (SPI3STATbits.SPIRBE == false)
        {
            *pReceived = SPI3BUF;
            pReceived += 1;
            count--;
        }
    }

    return dataSentCount;
}



uint8_t SPI3_Exchange8bit( uint8_t data )
{
    uint8_t receiveData;
    
    SPI3_Exchange(&data, &receiveData);

    return (receiveData);
}


uint16_t SPI3_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived)
{
    return (SPI3_ExchangeBuffer(dataTransmitted, byteCount, dataReceived));
}

SPI3_STATUS SPI3_StatusGet()
{
    return(SPI3STAT);
}

/**
 End of File
*/
