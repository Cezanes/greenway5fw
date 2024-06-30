/*
 * File:   parsing.h
 * Author: cezane
 *
 * This software item handles the JSON parsing. It generates and also it
 * reads JSON encoding and converts it in native data types.
 */

#ifndef JPARSING_H
#define JPARSING_H

#include "types.h"
#include "jsmn.h"

typedef struct
{
   jsmn_parser parser;
   jsmntok_t * tokens;
   size_t token_available;
   int token_count;
   const char *json_str;
} JsonInst;


bool json_parse_tokens(JsonInst * inst, const char *json_str, size_t size);
bool json_parse_is_tag(const JsonInst * inst, const jsmntok_t *tok, const char * tag);
bool json_parse_get_string(const JsonInst * inst, const jsmntok_t *tok, char * buff, size_t size);
bool json_parse_get_int32(const JsonInst * inst, const jsmntok_t *tok, int32_t *value);
bool json_read_uint32(const JsonInst * inst, const jsmntok_t *tok, uint32_t *value);
bool json_find_uint32(const JsonInst * inst, int root, const char * tag, uint32_t *value);
const jsmntok_t * json_parse_find_tag(const JsonInst * inst, int root, const char *tag);

size_t json_begin_object(char *json, size_t buff_size, const char * tag);
size_t json_end_object(char *json, size_t buff_size);
size_t json_begin_array(char *json, size_t buff_size, const char * tag);
size_t json_next_array(char *json, size_t buff_size);
size_t json_end_array(char *json, size_t buff_size);

size_t json_add_uint16(char *json, size_t buff_size, const char *tag, uint16_t value);
size_t json_add_int16(char *json, size_t buff_size, const char *tag, int16_t value);
size_t json_add_uint32(char *json, size_t buff_size, const char *tag, uint32_t value);
size_t json_add_int32(char *json, size_t buff_size, const char *tag, int32_t value);
size_t json_add_string(char *json, size_t buff_size, const char *tag, const char * value);
size_t json_add_bool(char *json, size_t buff_size, const char *tag, bool value);


size_t json_add_int16_array(char *json, size_t buff_size, const char *tag, const void * values, size_t count);
size_t json_add_uint16_array(char *json, size_t buff_size, const char *tag, const void * values, size_t count);
size_t json_add_uint32_array(char *json, size_t buff_size, const char *tag, const void * values, size_t count);



#endif