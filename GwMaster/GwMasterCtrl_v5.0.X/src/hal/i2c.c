#include "i2c.h"


void i2c_init(void)
{
   // initialize the hardware
   // Baud Rate Generator Value: I2CBRG 26;   
   I2C1BRG = 0x1A;
   // ACKEN disabled; STRICT disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW enabled; SBCDE disabled; SIDL disabled; BOEN disabled; ACKDT Sends ACK; SCIE disabled; PCIE disabled; SCLREL Holds; RSEN disabled; SDAHT disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; ON enabled; 
   I2C1CON = 0x8000;
   // BCL disabled; P disabled; S disabled; I2COV disabled; IWCOL disabled; 
   I2C1STAT = 0x00;
   
   /* I2C 1 Master */
   // clear the master interrupt flag
   IFS2bits.I2C1MIF = 0;
   // disdenable the master interrupt
   IEC2bits.I2C1MIE = 0;
}


void delay_ms(uint32_t ms)
{
   uint32_t start = _CP0_GET_COUNT();
   uint32_t duration = ms * 12000;
   
   while(_CP0_GET_COUNT() - start < duration);
}

void delay_us(uint32_t us)
{
   uint32_t start = _CP0_GET_COUNT();
   uint32_t duration = us * 12;
   
   while(_CP0_GET_COUNT() - start < duration);
}

bool i2c_wait_for_idle(void)
{
   uint32_t timeout = 1000;
   
   while((I2C1CON & 0x1F) > 0 && timeout > 0)
   {
      // Acknowledge sequence not in progress
      // Receive sequence not in progress
      // Stop condition not in progress
      // Repeated Start condition not in progress
      // Start condition not in progress
      timeout--;
      delay_us(10);
   }
   
   if (timeout == 0)
      return false;
   
   timeout = 1000;
   
   while(I2C1STATbits.TRSTAT && timeout)
   {
      // Bit = 0 ? Master transmit is not in progress
      timeout--;
      delay_us(10);
   }
   
   return timeout > 0;
}

bool i2c_start(void)
{
   I2C1CONbits.ON = 1;
   
   I2C1STATCLR = _I2C1STAT_IWCOL_MASK;
   I2C1STATCLR = _I2C1STAT_ACKSTAT_MASK;
   I2C1STATCLR = _I2C1STAT_BCL_MASK;
   I2C1STATCLR = _I2C1STAT_TBF_MASK;
      
   if(!i2c_wait_for_idle())
      return false;
   
   I2C1CONbits.SEN = 1;
   
   uint32_t timeout = 1000;
   
   while(I2C1CONbits.SEN && timeout)
   {
      // Bit = 0 ? Master transmit is not in progress
      timeout--;
      delay_us(1);
   }
   
   return timeout > 0;
}

bool i2c_stop(void)
{
   if(!i2c_wait_for_idle())
     return false;
    
   I2C1CONbits.PEN = 1;
   
   uint32_t timeout = 1000;
   
   while(I2C1CONbits.PEN && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   if (timeout == 0)
      return false;
   
   I2C1CONbits.ON = 0;
   
   return true;
}

bool i2c_restart(void)
{
   if(!i2c_wait_for_idle())
     return false;
   
   I2C1CONbits.RSEN = 1;
   
   uint32_t timeout = 1000;
   
   while(I2C1CONbits.RSEN && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   return timeout > 0;
}

bool i2c_ack(void)
{
   if(!i2c_wait_for_idle())
      return false;

   I2C1CONbits.ACKDT = 0; // Set hardware to send ACK bit
   I2C1CONbits.ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
      
   uint32_t timeout = 1000;
   while(I2C1CONbits.ACKEN && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   return timeout > 0;
}

bool i2c_nack(void) // Acknowledge Data bit
{
   if(!i2c_wait_for_idle())
     return false;
         
   I2C1CONbits.ACKDT = 1; // Set hardware to send NACK bit
   I2C1CONbits.ACKEN = 1; // Send NACK bit, will be automatically cleared by hardware when sent  
    
   uint32_t timeout = 1000;
   while(I2C1CONbits.ACKEN && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   return timeout > 0;
}

bool i2c_write(const uint8_t address, const bool wait_ack)
{
   I2C1TRN = address | 0;
   
   uint32_t timeout = 1000;
   while(I2C1STATbits.TBF && timeout)
   {
      if(I2C1STATbits.IWCOL)
         return false;
      
      timeout--;
      delay_us(1);
   }
   
   if (timeout == 0)
      return false;
   
   if(!i2c_wait_for_idle())
      return false;
   
   if (wait_ack)
   {
      uint32_t timeout = 1000;
      while(I2C1STATbits.ACKSTAT && timeout)
      {
         timeout--;
         delay_us(1);
      }
      
      return timeout > 0;
   }
   
   return true;
}

bool i2c_read(uint8_t * value, const bool ack)
{
   I2C1CONbits.RCEN = 1;				// Receive enable
   
   uint32_t timeout = 1000;
   while(I2C1CONbits.RCEN && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   if (timeout == 0)
      return false;
   
   timeout = 1000;
   while(!I2C1STATbits.RBF && timeout)
   {
      timeout--;
      delay_us(1);
   }
   
   if (timeout == 0)
      return false;
   
   *value = I2C1RCV;
    
   return ack ? i2c_ack() : i2c_nack();
}

void i2c_cleanup(void)
{
   I2C1CONbits.ON = 0;
}