#ifndef I2C_H
#define I2C_H

#include "types.h"

void i2c_init(void);
bool i2c_wait_for_idle(void);
bool i2c_start(void);
bool i2c_write(const uint8_t address, const bool wait_ack);
bool i2c_read(uint8_t * value, const bool ack);
bool i2c_stop(void);
void i2c_cleanup(void);
        
#endif