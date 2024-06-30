#ifndef SEM_OBJECTS_H
#define SEM_OBJECTS_H

#include "types.h"


#define SIGNAL_MAX_SCHEDULE_SIZE     (4 * STORAGE_PAGE_SIZE)

enum
{
   kSizePhoneNr      = 16,
   kSizeUserName     = 24,
};

enum
{
   kSigBlinkSolid = 0,
   kSigBlink50,
};

enum
{
   kSchFlagEnabled              = 1 << 0,
   kSchFlagTransIn              = 1 << 1,
   kSchFlagTransOut             = 1 << 2,
   kSchFlagMonitorBurntBulbs    = 1 << 3,
   kSchFlagMallfunctionFallback = 1 << 4,
};

enum
{
   kSchColorRed    = 0,
   kSchColorYellow = 1,
   kSchColorGreen  = 2,
};

enum
{
   kPatFlagTrazit       = 1 << 0,
   kPatFlagMonitorBulb  = 1 << 1,
};

enum
{
   kCtrlFlagMonitorBulbs = 1 << 0,
};

typedef struct __attribute__ ((packed))
{
   uint8_t offs;
   uint8_t count;
   uint8_t blink;
} SignalSpan;

typedef struct __attribute__ ((packed))
{
   uint8_t port;
   uint8_t pin;
} SignalBulb;

typedef struct __attribute__ ((packed))
{
   uint8_t name[8];
} SignalBulbDesc;

typedef struct __attribute__ ((packed))
{
   uint8_t color;
   uint8_t span_count;
   uint8_t bulb_count;
   uint8_t flags;
} SignalPattern;

typedef struct __attribute__ ((packed))
{
   uint16_t id;
   uint16_t size;
   uint8_t flags;
   uint8_t name[24];
   uint32_t time_start;
   uint32_t time_duration;
   uint8_t repeat_days;
   uint8_t period;
   uint8_t pattern_count;
} SignalSchedule;

typedef struct __attribute__ ((packed))
{
   uint16_t crc;
   uint16_t size;
   uint8_t encoding;
   uint8_t name[64];
   uint8_t id;
   uint8_t flags;
   uint8_t port_count;
   uint8_t port_size;
   uint8_t schedule_count;
} SignalController;

typedef struct __attribute__ ((packed))
{
   uint16_t crc;
   uint16_t size;
   uint8_t encoding;
   uint8_t name[64];
   uint8_t id;
   int32_t timezone;
   uint8_t controller_count;
} SignalNetwork;



const SignalController * sem_next_ctrl(const SignalNetwork * netw, const SignalController * ctrl);
const SignalSchedule * sem_next_sch(const SignalController * ctrl, const SignalSchedule * sch);
const SignalPattern * sem_next_pattern(const SignalSchedule * sch, const SignalPattern * pat);
const SignalBulb * sem_next_bulb(const SignalPattern * pat, const SignalBulb * bulb);
const SignalBulbDesc * sem_get_bulb_desc(const SignalController * ctrl, size_t port, size_t id);
void sem_print_sch(const SignalSchedule * sch);
void sem_print_port(const SignalController * ctrl);

#endif