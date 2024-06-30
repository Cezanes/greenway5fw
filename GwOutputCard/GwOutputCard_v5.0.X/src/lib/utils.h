/*
 * File:   utils.h
 * Author: cezane
 *
 * Generic utilitary software module.
 */

#ifndef UTILS_H
#define UTILS_H

#include "types.h"

#define CRC_START_CCITT_1D0F        0x1D0F
#define CRC_POLY_CCITT              0x1021

uint8_t utils_crc8(const void *data, const uint16_t size);
uint8_t utils_crc8t(const void *data, const uint16_t size);
uint16_t utils_crc16(const void * data, uint16_t size, uint16_t crc);
uint16_t utils_crc16t(const void * data, uint16_t size, uint16_t crc);

uint32_t utils_random32();
uint32_t utils_rev32(uint32_t val);
uint16_t utils_rev16(uint16_t val);



bool utils_bit_test(uint8_t *bitstr, uint16_t bit);
void utils_bit_set(uint8_t *bitstr, uint16_t bit);
void utils_bit_clear(uint8_t *bitstr, uint16_t bit);

bool utils_str_first_uint32(const char **start, const char *end, uint32_t *value, int baze);

int utils_strncasecmp(const char * s1, const char * s2, size_t count);

uint8_t utils_hex_to_byte(uint8_t const * const hex);

uint8_t utils_bcd_to_hex(uint8_t bcdvalue);
uint8_t utils_hex_to_bcd(uint8_t hexvalue);


#endif