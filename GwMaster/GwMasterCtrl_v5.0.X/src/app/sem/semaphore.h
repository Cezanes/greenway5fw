#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include "sem_objects.h"

enum
{
   kSemStateUnknown = 0,
   kSemStateInit,
   kSemStateNormal,
   kSemStateAlert,
   kSemStateSuspended,
   kSemStateDisabled,
   kSemStateError,
   kSemStateFatal,
};

enum
{
   kSemErrorNone = 0,
   kSemErrorBulbFailure,
   kSemErrorBoardUnpowered,
   kSemErrorBoardDisconnected,
   kSemErrorBoardFailure,
   kSemErrorNoTime,
};

typedef struct
{
   uint32_t unpowered_boards;
   uint32_t disconnected_boards;
   uint32_t failed_boards;
   uint32_t burnt_bulbs_non_critical[16];
   uint32_t burnt_bulbs_critical[16];
   
   bool have_burnt_critical;
   bool have_burnt_non_critical;
   
} SemPowerMetrics;

typedef struct
{
   size_t global;
   size_t error;
   size_t last_state;
   bool just_booted;
   const char * str_global;
   const char * str_error;
   char str_net[FIELD_SIZE(SignalNetwork, name)];
   char str_ctrl[FIELD_SIZE(SignalController, name)];
   char str_sch[FIELD_SIZE(SignalSchedule, name)];
} SemState;


typedef struct
{
   uint8_t * sch_buff;
   size_t sch_buff_size;
   const uint32_t * sms_periods;
   size_t sms_period_count;
} SemConfig;


void sem_init(const SemConfig * sem_config);
void sem_set_program(const SignalController * prog);
void sem_start(void);

void sem_tick(const uint32_t epoch, const uint32_t milli);

uint32_t sem_get_period(const uint32_t time);
const SignalSchedule * sem_get_current_sch(void);
const SemState * sem_get_state(void);
const SemPowerMetrics * sem_get_metrics(void);
const char * sem_get_state_str(void);
const char * sem_get_error_str(void);

void sem_suspend(const bool on);
void sem_suspend_sch_check(const bool on);
void sem_operation_suspend(void);
void sem_operation_resume(void);

void sem_service(void);

#endif