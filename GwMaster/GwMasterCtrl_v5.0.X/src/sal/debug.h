/*
 * File:   debug.h
 * Author: cezane
 *
 * Generic UART debug mechanism. It supports multiple debug levels with
 * console colors.
 */

#ifndef DEBUG_H
#define DEBUG_H

#include "types.h"
#include "hal/uart32mx.h"

#define kLvlDbg                     0
#define kLvlVerb                    1
#define kLvlInfo                    2
#define kLvlWarn                    3
#define kLvlError                   4

#define DBG_USE_COLORS              1
#define DBG_USE_TIMESTAMP           1

#ifndef DBG_LEVEL
   #define DBG_LEVEL          kLvlVerb
#endif


typedef struct
{
   UartDev * uart;
   uint8_t * buff;
   size_t buff_size;
   uint32_t clock_src;
   uint32_t baud;
   size_t level;
} DebugConfig;


size_t dbg_get_level();
void dbg_set_level(size_t lvl);
void dbg_init(const DebugConfig * config);
void dbg_print(int lvl, const char *fmt, ...);
void dbg_print_hdr(int lvl, const char *fmt, ...);
void dbg_print_foot(int lvl, const char *fmt, ...);
void dbg_println(int lvl);
void dbg_hex(int lvl, const char *text, const void *data, size_t size);
void dbg_print_raw(int lvl, const char *fmt, ...);
void dbg_print_data(int lvl, const void *data, size_t size);

#define DBG_PRINT(lvl, fmt, ...) dbg_print(lvl, fmt, ##__VA_ARGS__)
#define DBG_PRINT_LN(lvl) dbg_println(lvl)
#define DBG_PRINT_HEX(lvl, txt, vec, size) dbg_hex(lvl, txt, vec, size)
#define DBG_PRINT_HDR(lvl, fmt, ...) dbg_print_hdr(lvl, fmt, ##__VA_ARGS__)
#define DBG_PRINT_FOOT(lvl, fmt, ...) dbg_print_foot(lvl, fmt, ##__VA_ARGS__)
#define DBG_PRINT_RAW(lvl, fmt, ...) dbg_print_raw(lvl, fmt, ##__VA_ARGS__)
#define DBG_PRINT_DATA(lvl, data, size) dbg_print_data(lvl, data, size)

#define DBG(LVL, ...)      DBG##LVL(LVL, ##__VA_ARGS__)
#define DBGHEX(LVL, ...)   DBGHEX##LVL(LVL, ##__VA_ARGS__)
#define DBGLN(LVL)         DBGLN##LVL(LVL)
#define DBGHDR(LVL, ...)   DBGHDR##LVL(LVL, ##__VA_ARGS__)
#define DBGFOOT(LVL, ...)  DBGFOOT##LVL(LVL, ##__VA_ARGS__)
#define DBGRAW(LVL, ...)   DBGRAW##LVL(LVL, ##__VA_ARGS__)
#define DBGDATA(LVL, ...)  DBGDATA##LVL(LVL, ##__VA_ARGS__)


#if (DBG_LEVEL <= kLvlDbg)
   #define DBGkLvlDbg     DBG_PRINT
   #define DBGHEXkLvlDbg  DBG_PRINT_HEX
   #define DBGLNkLvlDbg   DBG_PRINT_LN
   #define DBGHDRkLvlDbg  DBG_PRINT_HDR
   #define DBGFOOTkLvlDbg DBG_PRINT_FOOT
   #define DBGRAWkLvlDbg  DBG_PRINT_RAW
   #define DBGDATAkLvlDbg DBG_PRINT_DATA
#else
   #define DBGkLvlDbg(...) do{}while(false);
   #define DBGHEXkLvlDbg(...) do{}while(false);
   #define DBGLNkLvlDbg(...) do{}while(false);
   #define DBGHDRkLvlDbg(...) do{}while(false);
   #define DBGFOOTkLvlDbg(...) do{}while(false);
   #define DBGRAWkLvlDbg(...) do{}while(false);
   #define DBGDATAkLvlDbg(...) do{}while(false);
#endif

#if (DBG_LEVEL <= kLvlVerb)
   #define DBGkLvlVerb     DBG_PRINT
   #define DBGHEXkLvlVerb  DBG_PRINT_HEX
   #define DBGLNkLvlVerb   DBG_PRINT_LN
   #define DBGHDRkLvlVerb  DBG_PRINT_HDR
   #define DBGFOOTkLvlVerb DBG_PRINT_FOOT
   #define DBGRAWkLvlVerb  DBG_PRINT_RAW
   #define DBGDATAkLvlVerb DBG_PRINT_DATA
#else
   #define DBGkLvlVerb(...) do{}while(false);
   #define DBGHEXkLvlVerb(...) do{}while(false);
   #define DBGLNkLvlVerb(...) do{}while(false);
   #define DBGHDRkLvlVerb(...) do{}while(false);
   #define DBGFOOTkLvlVerb(...) do{}while(false);
   #define DBGRAWkLvlVerb(...) do{}while(false);
   #define DBGDATAkLvlVerb(...) do{}while(false);
#endif

#if (DBG_LEVEL <= kLvlInfo)
   #define DBGkLvlInfo     DBG_PRINT
   #define DBGHEXkLvlInfo  DBG_PRINT_HEX
   #define DBGLNkLvlInfo   DBG_PRINT_LN
   #define DBGHDRkLvlInfo  DBG_PRINT_HDR
   #define DBGFOOTkLvlInfo DBG_PRINT_FOOT
   #define DBGRAWkLvlInfo  DBG_PRINT_RAW
   #define DBGDATAkLvlInfo DBG_PRINT_DATA
#else
   #define DBGkLvlInfo(...) do{}while(false);
   #define DBGHEXkLvlInfo(...) do{}while(false);
   #define DBGLNkLvlInfo(...) do{}while(false);
   #define DBGHDRkLvlInfo(...) do{}while(false);
   #define DBGFOOTkLvlInfo(...) do{}while(false);
   #define DBGRAWkLvlInfo(...) do{}while(false);
   #define DBGDATAkLvlInfo(...) do{}while(false);
#endif

#if (DBG_LEVEL <= kLvlWarn)
   #define DBGkLvlWarn     DBG_PRINT
   #define DBGHEXkLvlWarn  DBG_PRINT_HEX
   #define DBGLNkLvlWarn   DBG_PRINT_LN
   #define DBGHDRkLvlWarn  DBG_PRINT_HDR
   #define DBGFOOTkLvlWarn DBG_PRINT_FOOT
   #define DBGRAWkLvlWarn  DBG_PRINT_RAW
   #define DBGDATAkLvlWarn DBG_PRINT_DATA
#else
   #define DBGkLvlWarn(...) do{}while(false);
   #define DBGHEXkLvlWarn(...) do{}while(false);
   #define DBGLNkLvlWarn(...) do{}while(false);
   #define DBGHDRkLvlWarn(...) do{}while(false);
   #define DBGFOOTkLvlWarn(...) do{}while(false);
   #define DBGRAWkLvlWarn(...) do{}while(false);
   #define DBGDATAkLvlWarn(...) do{}while(false);
#endif


#if (DBG_LEVEL <= kLvlError)
   #define DBGkLvlError     DBG_PRINT
   #define DBGHEXkLvlError  DBG_PRINT_HEX
   #define DBGLNkLvlError   DBG_PRINT_LN
   #define DBGHDRkLvlError  DBG_PRINT_HDR
   #define DBGFOOTkLvlError DBG_PRINT_FOOT
   #define DBGRAWkLvlError  DBG_PRINT_RAW
   #define DBGDATAkLvlError DBG_PRINT_DATA
#else
   #define DBGkLvlError(...) do{}while(false);
   #define DBGHEXkLvlError(...) do{}while(false);
   #define DBGLNkLvlError(...) do{}while(false);
   #define DBGHDRkLvlError(...) do{}while(false);
   #define DBGFOOTkLvlError(...) do{}while(false);
   #define DBGRAWkLvlError(...) do{}while(false);
   #define DBGDATAkLvlError(...) do{}while(false);
#endif


#include <stdarg.h>

void tfp_printf(const char *fmt, ...);
size_t tfp_sprintf(char * s, const char *fmt, ...);
size_t tfp_snprintf(char* s, size_t size, const char *fmt, ...);

#endif