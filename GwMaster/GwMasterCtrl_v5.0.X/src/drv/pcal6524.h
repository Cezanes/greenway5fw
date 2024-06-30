#ifndef PCAL6525_H
#define PCAL6525_H

#include "types.h"

void pcal6524_init();

bool pcal6524_set_tris(const uint8_t addr, const uint8_t * tris, const size_t count);
bool pcal6524_set_value(const uint8_t addr, const uint8_t * value, const size_t count);

size_t pcal6524_compile_tris(const uint8_t * val, size_t val_count, uint8_t * dest, size_t available);
size_t pcal6524_compile_val(const uint8_t * val, size_t val_count, uint8_t * dest, size_t available);

#endif