#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jsmn.h"
#include "jparsing.h"

#include "lib/utils.h"
#include "sal/debug.h"

static const char sep = ',';


bool json_parse_tokens(JsonInst * inst, const char *json_str, size_t size)
{
   jsmn_init(&inst->parser);
   inst->token_count = jsmn_parse(&inst->parser, json_str, size, inst->tokens, inst->token_available);
   
   inst->json_str = (char *)json_str;
   
   switch(inst->token_count)
   {
      case JSMN_ERROR_NOMEM:
      {
         DBG(kLvlError, "json, not enough allocated JSON tokens %u", inst->token_available);
         return false;
      }

      case JSMN_ERROR_INVAL:
      {
         DBG(kLvlError, "json, invalid JSON characters \r\n%s", json_str);
         return false;
      }

      case JSMN_ERROR_PART:
      {
         DBG(kLvlError, "json, incomplete JSON %s", json_str);
         return false;
      }
   }
   
   
   /*char buff[32];
   for(size_t i = 0; i < inst->token_count; i++)
   {
      size_t count = inst->tokens[i].end - inst->tokens[i].start;      
      if(count >= sizeof(buff))
         count = sizeof(buff) - 1;
      
      snprintf_ex(buff, sizeof(buff), &inst->json_str[inst->tokens[i].start]);
      buff[count] = 0;
      
      DBG(kLvlVerb, "tok: %s %u %d %u", &buff[0], inst->tokens[i].size, inst->tokens[i].parent, inst->tokens[i].type);
   }*/

   return (inst->token_count >= 0);
}

bool json_parse_is_tag(const JsonInst * inst, const jsmntok_t *tok, const char * tag)
{
   if (tok->type == JSMN_STRING && tok->size == 1 &&
      (int)strlen(tag) == tok->end - tok->start &&
      strncmp(&inst->json_str[tok->start], tag, tok->end - tok->start) == 0)
   {
      return true;
   }
   
   return false;
}

bool json_parse_get_string(const JsonInst * inst, const jsmntok_t *tok, char * buff, size_t size)
{
   if (tok->type != JSMN_STRING || tok->size != 0)
      return false;

   size--;
   
   int count = tok->end - tok->start;
   size = size > count ? count : size;
   
   strncpy(buff, &inst->json_str[tok->start], size);
   buff[size] = 0;
   
   return true;
}

bool json_parse_get_string_ref(const JsonInst * inst, const jsmntok_t *tok, const char ** str, size_t* size)
{
   if (tok->type != JSMN_STRING || tok->size != 0)
      return false;
   
   int count = tok->end - tok->start;
   
   if (size != NULL)
      *size = (size_t) count;
   
   inst->json_str[tok->end] = '\0';
   
   *str = &inst->json_str[tok->start];
   
   return true;
}

bool json_parse_get_int32(const JsonInst * inst, const jsmntok_t *tok, int32_t *value)
{
   if (tok->type != JSMN_PRIMITIVE || tok->size != 0)
      return false;

   *value = strtol(&inst->json_str[tok->start], 0, 10);
   
   return true;
}

bool json_read_uint32(const JsonInst * inst, const jsmntok_t *tok, uint32_t *value)
{
   if (tok->type != JSMN_PRIMITIVE || tok->size != 0)
      return false;

   *value = strtoul(&inst->json_str[tok->start], 0, 10);
   
   return true;
}

bool json_find_uint32(const JsonInst * inst, const jsmntok_t * root, const char * tag, uint32_t *value)
{
   const jsmntok_t * token = json_parse_find_tag(inst, root + 1, tag);
   
   if(NULL != token && token->type == JSMN_STRING)
   {
      return json_read_uint32(inst, &token[1], value);
   }
   
   return false;
}

const jsmntok_t * json_parse_find_tag(const JsonInst * inst, const jsmntok_t *root, const char *tag)
{
   int root_index = 0;
   if (root != NULL)
      root_index = root->index + 1;
         
   for(size_t i = 0; i < inst->token_count; i++)
   {
      if(inst->tokens[i].parent == root_index && json_parse_is_tag(inst, &inst->tokens[i], tag))
      {
         return &inst->tokens[i];
      }
   }
   
   return 0;
}

size_t json_add_uint16(char *json, size_t buff_size, const char *tag, uint16_t value)
{
   return snprintf_ex(json, buff_size, "\"%s\":%u,", tag, value);
}

size_t json_add_int16(char *json, size_t buff_size, const char *tag, int16_t value)
{
   return snprintf_ex(json, buff_size, "\"%s\":%d,", tag, value);
}

size_t json_add_uint32(char *json, size_t buff_size, const char *tag, uint32_t value)
{
   return snprintf_ex(json, buff_size, "\"%s\":%lu,", tag, value);
}

size_t json_add_int32(char *json, size_t buff_size, const char *tag, int32_t value)
{
   return snprintf_ex(json, buff_size, "\"%s\":%ld,", tag, value);
}

size_t json_add_string(char *json, size_t buff_size, const char *tag, const char * value)
{
   size_t size = 0;
   
   //snprintf_ex(json, buff_size, "\"%s\":\"%s\",", tag, value);
   
   size += snprintf_ex(&json[size], buff_size - size, "\"%s\":\"", tag);
   
   const char * str = value;
   char * ptr = &json[size];
   
   for(; (size < buff_size - 1) && (*str != '\0'); str++)
   {
      char c = *str;
      switch(c)
      {
         case 0x08: 
            *ptr++ = '\\'; size++;
            *ptr++ = 'b'; size++;
            break;
         
         case 0x0C:
            *ptr++ = '\\'; size++;
            *ptr++ = 'f'; size++;
            break;
         
         case '\n':
            *ptr++ = '\\'; size++;
            *ptr++ = 'n'; size++;
            break;
         
         case '\r':
            *ptr++ = '\\'; size++;
            *ptr++ = 'r'; size++;
            break;
         
         case '\t':
            *ptr++ = '\\'; size++;
            *ptr++ = 't'; size++;
            break;
            
         case '"':
            *ptr++ = '\\'; size++;
            *ptr++ = '"'; size++;
            break;
            
         case '\\':
            *ptr++ = '\\'; size++;
            *ptr++ = '\\'; size++;
            break;
            
         case '/':
            *ptr++ = '\\'; size++;
            *ptr++ = '/'; size++;
            break;
         
         default:
            if ((unsigned char)c < 0x20)
            {
               if (buff_size - size >= 6)
               {
                  size += snprintf_ex(ptr, buff_size - size, "\\u%04x", c);
                  ptr += size;
               }
            }
            else
            {
               *ptr++ = c; size++;
            }
      }
   }
   
   size += snprintf_ex(&json[size], buff_size - size, "\",");
   
   return size;
}

size_t json_add_bool(char *json, size_t buff_size, const char *tag, bool value)
{
   static const char * str_true = "true";
   static const char * str_false = "false";
   
   return snprintf_ex(json, buff_size, "\"%s\":%s,", tag, value ? str_true : str_false);
}

size_t json_begin_object(char *json, size_t buff_size, const char * tag)
{
   if(tag)
      return snprintf_ex(json, buff_size, "\"%s\":{", tag);
   else return snprintf_ex(json, buff_size, "{");
}

size_t json_next_object(char *json, size_t buff_size)
{
   return snprintf_ex(json, buff_size, ",");
}

size_t json_begin_array(char *json, size_t buff_size, const char * tag)
{
   if(tag == NULL)
   {
      return snprintf_ex(json, buff_size, "[");
   }
   else
   {
      return snprintf_ex(json, buff_size, "\"%s\":[", tag);
   }
}

size_t json_next_array(char *json, size_t buff_size)
{
   return snprintf_ex(json, buff_size, ",");
}

size_t json_end_array(char *json, size_t buff_size)
{
   if(*(json - 1) == ',')
   {
      *(json - 1) = ']';
      return 0;
   }
   
   if(buff_size > 0)
   {
      *json++ = ']';
      *json++ = 0;
      return 1;
   }
   
   return 0;
}

size_t json_end_object(char *json, size_t buff_size)
{
   if(*(json - 1) == ',')
   {
      *(json - 1) = '}';
      return 0;
   }
   
   if(buff_size > 0)
   {
      *json++ = '}';
      *json++ = 0;
      return 1;
   }
   
   return 0;
}

size_t json_add_int16_array(char *json, size_t buff_size, const char *tag, const void * data, size_t count)
{
   size_t size = 0;
   
   size += snprintf_ex(&json[size], buff_size - size, "\"%s\":[", tag);
   
   const uint8_t * ptr = data;
   for(size_t i = 0; i < count; i++, ptr += 2)
   {
      uint16_t value = ((uint16_t)ptr[1] << 8) + ptr[0];
      size += snprintf_ex(&json[size], buff_size - size, "%d,", value);
   }
   
   if(count > 0)
      size += snprintf_ex(&json[size - 1], buff_size - size, "],") - 1;
   else size += snprintf_ex(&json[size], buff_size - size, "],");
      
   if(size == buff_size)
   {
      DBG(kLvlError, "json, json_add_int16_array not enough buff size");
   }
   
   return size;
}

size_t json_add_uint16_array(char *json, size_t buff_size, const char *tag, const void * data, size_t count)
{
   size_t size = 0;
   
   size += snprintf_ex(&json[size], buff_size - size, "\"%s\":[", tag);
   
   const uint8_t * ptr = data;
   for(size_t i = 0; i < count; i++, ptr += 2)
   {
      uint16_t value = ((uint16_t)ptr[1] << 8) + ptr[0];
      size += snprintf_ex(&json[size], buff_size - size, "%u,", value);
   }
   
   if(count > 0)
      size += snprintf_ex(&json[size - 1], buff_size - size, "],") - 1;
   else size += snprintf_ex(&json[size], buff_size - size, "],");
   
   if(size == buff_size)
   {
      DBG(kLvlError, "json, json_add_uint16_array not enough buff size");
   }
   
   return size;
}

size_t json_add_uint32_array(char *json, size_t buff_size, const char *tag, const void * data, size_t count)
{
   size_t size = 0;
   
   size += snprintf_ex(&json[size], buff_size - size, "\"%s\":[", tag);
   
   const uint8_t * ptr = data;
   for(size_t i = 0; i < count; i++, data += sizeof(uint32_t))
   {
      uint32_t value = ((uint32_t)ptr[3] << 24) + ((uint32_t)ptr[2] << 16) + ((uint32_t)ptr[1] << 8) + ptr[0];
      size += snprintf_ex(&json[size], buff_size - size, "%lu,", value);
   }
   
   if(count > 0)
      size += snprintf_ex(&json[size - 1], buff_size - size, "],") - 1;
   else size += snprintf_ex(&json[size], buff_size - size, "],");
   
   if(size == buff_size)
   {
      DBG(kLvlError, "json, json_add_uint32_array not enough buff size");
   }
   
   return size;
}