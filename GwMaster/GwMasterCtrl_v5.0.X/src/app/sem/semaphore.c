#include "semaphore.h"

#include "sal/timer.h"
#include "sal/debug.h"

#include "lib/datetime.h"

#include "app/logic/logic.h"
#include "app/sem/chronos.h"
#include "app/out/power_ctrl.h"
#include "sal/pulse.h"
#include "cfg/hw_config.h"



static const char * sem_state_str[] = 
{
   "unknown",
   "init",
   "normal",
   "alert",
   "suspended",
   "suspended_manually",
   "disabled",
   "error",
   "fatal",
};

static const char * sem_error_str[] = 
{
   "none", 
   "bulb_failure", 
   "board_unpowered", 
   "board_disconnected",
   "board_failure",
   "rtc_invalid",
};

static const char * sem_state_friendly_str[] = 
{
   "Unknown",
   "Init",
   "Normal",
   "Alert", 
   "Supended", 
   "Supended Manually", 
   "Disabled", 
   "Error",
   "Fatal",
};


static const char * sem_error_friendly_str[] = 
{
   "None",
   "Bulb Failure", 
   "Board Unpowered", 
   "Board Disconnected",
   "Board Failure",
};

typedef struct 
{
   SemState state;
   SemPowerMetrics metrics;
   SemConfig config;
   
   bool disable_sem_update;
   bool suspended_sch_check;
   
   bool req_manual_suspend;
   bool req_manual_disable;
   bool req_manual_normal;
   
   bool req_state_changed;
   bool req_sch_changed;
   
   bool full_second;
   
   bool transition_in;
   bool transition_out;
   size_t tranzition_safety;
   
   const SignalNetwork * netw;
   const SignalController * ctrl;
   const SignalSchedule * curr_sch;
   
} SemInternal;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct __attribute__ ((packed))
{
   SignalController ctrl;
   SignalSchedule schedule1;
   
   struct {
      SignalPattern pattern;
      SignalSpan span;
      SignalBulb bulb[12];
   } patt1[2];
   
   SignalSchedule schedule2;
   
   struct {
      SignalPattern pattern;
      SignalSpan span;
      SignalBulb bulb[12];
   } patt2[2];
   
} SemDemoProg;

static const SemDemoProg sem_demo_prog = 
{
   .ctrl = 
   {
      .encoding = 1,
      .name = "test",
      .size = 150,
      .schedule_count = 2,
      .port_count = 1,
   },
   
   .schedule1 = 
   {
      .name = "test_sch_1",
      .flags = kSchFlagEnabled,
      .time_start = 0,
      .time_duration = CA_SECONDS_PER_WEEK,
      .pattern_count = 1,
      .period = 2,
      .size = sizeof(SemDemoProg) - sizeof(SignalController),
      .id = 25,
   },
   
   .patt1 = 
   {
      {
         .pattern = {.color = kSchColorRed, .span_count = 1, .bulb_count = 12, .flags = 0},
         .span = {.offs = 0, .count = 1, .blink = kSigBlinkSolid},
         .bulb = {
            {.port = 1, .pin = 1},  {.port = 1, .pin = 2},   {.port = 1, .pin = 3},
            {.port = 1, .pin = 4},  {.port = 1, .pin = 5},   {.port = 1, .pin = 6},
            {.port = 1, .pin = 7},  {.port = 1, .pin = 8},   {.port = 1, .pin = 9},
            {.port = 1, .pin = 10}, {.port = 1, .pin = 11},  {.port = 1, .pin = 12},
         },
      },
      /*{
         .pattern = {.color = kSchColorGreen, .span_count = 1, .bulb_count = 12, .flags = 0},
         .span = {.offs = 0, .count = 1, .blink = kSigBlinkSolid},
         .bulb = {
            {.port = 2, .pin = 1},  {.port = 2, .pin = 2},  {.port = 2, .pin = 3},
            {.port = 2, .pin = 4},  {.port = 2, .pin = 5},  {.port = 2, .pin = 6},
            {.port = 2, .pin = 7},  {.port = 2, .pin = 8},  {.port = 2, .pin = 9},
            {.port = 2, .pin = 10}, {.port = 2, .pin = 11}, {.port = 2, .pin = 12},
         },
      },*/
   },
   
   .schedule2 = 
   {
      .name = "test_sch_2",
      .flags = kSchFlagEnabled,
      .time_start = 0,
      .time_duration = CA_SECONDS_PER_WEEK,
      .pattern_count = 1,
      .period = 2,
      .size = sizeof(SemDemoProg) - sizeof(SignalController),
      .id = 30,
   },
   
   .patt2 = 
   {
      {
         .pattern = {.color = 1, .span_count = 1, .bulb_count = 12, .flags = 0},
         .span = {.offs = 0, .count = 1, .blink = kSigBlinkSolid},
         .bulb = {
            {.port = 1, .pin = 1},  {.port = 1, .pin = 2},   {.port = 1, .pin = 3},
            {.port = 1, .pin = 4},  {.port = 1, .pin = 5},   {.port = 1, .pin = 6},
            {.port = 1, .pin = 7},  {.port = 1, .pin = 8},   {.port = 1, .pin = 9},
            {.port = 1, .pin = 10}, {.port = 1, .pin = 11},  {.port = 1, .pin = 12},
         },
      },
      /*{
         .pattern = {.color = 1, .span_count = 1, .bulb_count = 12, .flags = 0},
         .span = {.offs = 0, .count = 1, .blink = kSigBlinkSolid},
         .bulb = {
            {.port = 2, .pin = 1},  {.port = 2, .pin = 2},  {.port = 2, .pin = 3},
            {.port = 2, .pin = 4},  {.port = 2, .pin = 5},  {.port = 2, .pin = 6},
            {.port = 2, .pin = 7},  {.port = 2, .pin = 8},  {.port = 2, .pin = 9},
            {.port = 2, .pin = 10}, {.port = 2, .pin = 11}, {.port = 2, .pin = 12},
         },
      },*/
   },
};



/////////////////////////////////////////////////////////////////////////////////////////////////


static SemInternal sem;


/////////////////////////////////////////////////////////////////////////////////////////////////

static void change_state(size_t state, size_t error)
{
   if (sem.state.global == state && sem.state.error == error)
      return;
   
   if (app_config.sem.disabled_manually && state >= kSemStateNormal)
   {
      if (state < kSemStateDisabled)
      {
         state = kSemStateDisabled;
         error = kSemErrorNone;
      }
   }
   else if (app_config.sem.suspended_manually && state >= kSemStateNormal)
   {
      if (state < kSemStateSuspendedManually)
      {
         state = kSemStateSuspendedManually;
         error = kSemErrorNone;
      }
   }
   
   sem.state.just_booted = state == kSemStateNormal && sem.state.global == kSemStateInit;
   
   if (sem.state.global != state && state == kSemStateFatal)
      pctrl_pswitch_set(false);
   
   sem.state.last_state = sem.state.global;
   sem.state.global = state;
   sem.state.error = error;
   
   sem.state.str_global = sem_get_state_str(false);
   sem.state.str_error = sem_get_error_str();
   
   sem.req_state_changed = true;
   
   DBG(kLvlWarn, "state changed to '%s', error '%s'", sem.state.str_global, sem.state.str_error);
}

static void check_power_board_error_resume(void)
{
   sem.metrics.unpowered_boards = pctrl_get_unpowered();
   sem.metrics.disconnected_boards = pctrl_get_disconnected();
   sem.metrics.failed_boards = pctrl_get_failed();

   if(sem.metrics.failed_boards > 0)
   {
      change_state(kSemStateFatal, kSemErrorBoardFailure);
   }
   else if(sem.metrics.disconnected_boards > 0)
   {
      change_state(kSemStateFatal, kSemErrorBoardDisconnected);
   }
   else if(sem.metrics.unpowered_boards > 0)
   {
      if (kSemStateFatal != sem.state.global)
         change_state(kSemStateError, kSemErrorBoardUnpowered);
   }
   else if(sem.state.global == kSemStateError)
   {
      // Resume from unpowered to normal
      if(sem.state.error == kSemErrorBoardUnpowered)
      {
         if(sem.metrics.unpowered_boards == 0)
            change_state(kSemStateNormal, kSemErrorNone);
      }
   }
}

static bool output_bulb(const SignalBulb * bulb, bool value)
{
   if(value)
   {
      return pctrl_set(bulb->port, bulb->pin);
   }
   
   return true;
}

static void output_signal(const SignalPattern * pat, bool value)
{
   const uint8_t * ptr = (const uint8_t *) (pat + 1);
   ptr += pat->span_count * sizeof(SignalSpan);
   
   const SignalBulb * bulb = (const SignalBulb *) ptr;
   
   for(size_t i = 0; i < pat->bulb_count; i++, bulb++)
   {
      bool lit = output_bulb(bulb, value);
      if(!lit && (sem.state.global == kSemStateNormal || sem.state.global == kSemStateAlert))
      {
         uint32_t mask = 1UL << (bulb->pin - 1);
         
         if(pat->flags & kPatFlagMonitorBulb)
         {
            sem.metrics.burnt_bulbs_critical[bulb->port - 1] |= mask;
         }
         else
         {
            sem.metrics.burnt_bulbs_non_critical[bulb->port - 1] |= mask;
         }
      }
   }
}

static bool is_in_schedule(uint32_t week_sec, const SignalSchedule * sch)
{
   size_t repeat = 0;

   if ((sch->flags & kSchFlagEnabled) == 0)
      return false;

   uint32_t start = sch->time_start; 
   uint32_t duration = sch->time_duration;
   
   //DBG(kLvlVerb, "sch %s %u %u %u", sch->name, sch->repeat_days, start, duration);
   
   while(repeat <= sch->repeat_days)
   {
      //DBG(kLvlVerb, "%u %u %u", start, week_sec, start + duration);
      
      uint32_t end = start + duration;
      
      if (week_sec >= start && week_sec < end)
         return true;
      
      uint32_t passed = end % CA_SECONDS_PER_WEEK;
      
      if (passed > 0 && passed < start)
         return true;
      
      repeat++;
      start += CA_SECONDS_PER_DAY;
   }
   
   //DBG(kLvlVerb, "skip\n\n");
   
   return false;
}

static void mark_signal(const uint32_t milli, const SignalPattern * pat, const SignalSpan * span, bool on)
{
   uint8_t blink = kSigBlinkSolid;
   
   if(span != NULL)
      blink = span->blink;
   
   uint32_t mil = milli;
   if (mil >= 1000)
      mil %= 1000;
   
   bool q1 = mil < 250;
   bool q2 = mil >= 250 && mil < 500;
   bool q3 = mil >= 500 && mil < 750;
   bool q4 = mil >= 750;
   
   bool h1 = mil < 500;
      
   switch(blink)
   {
      case kSigBlinkSolid:
      {
         output_signal(pat, on);
         break;
      }
      
      case kSigBlink50:
      {
         output_signal(pat, h1 && on);
         break;
      }
   }
}

static void check_signal(const uint32_t tick, const uint32_t milli, const uint32_t period, const SignalPattern * cpat)
{
   const SignalSpan * span = (const SignalSpan *)(cpat + 1);
   
   bool inside = false;
   
   for(size_t i = 0; i < cpat->span_count; i++, span++)
   {
      uint32_t start = span->offs;
      uint32_t stop = span->offs + span->count;
      
      inside = tick >= start && tick < stop;
      
      if (!inside && stop >= period)
      {
         stop -= period;
         inside = tick < stop;
      }
      
      if(inside)
         break;
   }
   
   if(!inside)
      span = NULL;
   
   if (!sem.transition_in && !sem.transition_out)
   {
      mark_signal(milli, cpat, span, inside);
      return;
   }
   
   SignalPattern * pat = (SignalPattern *) cpat;
   
   bool set = inside;
   
   if(sem.transition_out)
   {
      if(pat->color == kSchColorRed)
      {
         if(set == true)
            pat->flags |= kPatFlagTrazit;
         else set = (pat->flags & kPatFlagTrazit) > 0;
      }
      else if(pat->color == kSchColorGreen)
      {
         if(set == false)
            pat->flags |= kPatFlagTrazit;
         else set = (pat->flags & kPatFlagTrazit) == 0;
      }
      else
      {
         pat->flags |= kPatFlagTrazit;
      }
   }
   else if(sem.transition_in)
   {
      if(pat->color == kSchColorRed)
      {
         if(set == true)
            pat->flags &= ~kPatFlagTrazit;
         else set = (pat->flags & kPatFlagTrazit) > 0;
      }
      else if(pat->color == kSchColorGreen)
      {
         if(set == false)
            pat->flags &= ~kPatFlagTrazit;
         else set = (pat->flags & kPatFlagTrazit) == 0;
      }
      else
      {
         pat->flags &= ~kPatFlagTrazit;
      }
   }
   
   mark_signal(milli, pat, span, set);
}

static void run_schedule(const uint32_t week_sec, const uint32_t milli, const SignalSchedule * sch)
{
   uint32_t tick = week_sec % sch->period;
  
   const SignalPattern * pat = sem_next_pattern(sch, NULL);
      
   while(pat != NULL)
   {
      check_signal(tick, milli, sch->period, pat);
      pat = sem_next_pattern(sch, pat);
   }
}

static void sem_tick_config(bool full_second)
{
   sem.full_second = full_second;
   pulse_set_isr(kPulseSem, full_second);
}

static void sem_clear(void)
{
   pctrl_clear_outs();
}

static void sem_commit(void)
{
   pctrl_commit(sem.full_second);
}

static bool sem_adopt_sch(const SignalSchedule * new_sch, bool reset_metrics)
{
   if(new_sch == NULL)
      return false;
   
   if(new_sch->size > sem.config.sch_buff_size)
   {
      DBG(kLvlError, "sem, schedule size too large %u vs %u", new_sch->size, sem.config.sch_buff_size);
      return false;
   }
   
   memcpy(sem.config.sch_buff, new_sch, new_sch->size);
   sem.curr_sch = (const SignalSchedule *) sem.config.sch_buff;
   
   if(reset_metrics)
   {
      sem.metrics = (SemPowerMetrics) {0};
      change_state(kSemStateNormal, kSemErrorNone);
      pctrl_clear_status();
   }
   
   sem_print_sch(sem.curr_sch);
   
   sem.req_sch_changed = true;
   
   return true;
}


//////////////////////////////////////////////////      Opration       //////////////////////////////////////////////////


static bool switch_to_fallback(const uint32_t week_sec)
{
   const SignalSchedule * sch_fail = NULL;

   sch_fail = sem_next_sch(sem.ctrl, NULL);

   while(sch_fail != NULL)
   {
      if (is_in_schedule(week_sec, sch_fail) && (sch_fail->flags & kSchFlagMallfunctionFallback))
         break;

      sch_fail = sem_next_sch(sem.ctrl, sch_fail);
   }

   if(sch_fail == NULL)
   {
      sem.curr_sch = NULL;
      sem_commit();
      DBG(kLvlVerb, "sem, no fallback sch");
      return false;
   }

   sem.transition_out = false;
   sem.transition_in = false;
   sem_adopt_sch(sch_fail, false);
   
   return true;
}

void sem_operation_suspend(void)
{
   sem.req_manual_suspend = true;
   app_config.sem.suspended_manually = true;
   app_config.sem.disabled_manually = false;
   app_config_write();
}

void sem_operation_disable(void)
{
   sem.req_manual_disable = true;
   app_config.sem.suspended_manually = false;
   app_config.sem.disabled_manually = true;
   app_config_write();
}

void sem_operation_resume(void)
{
   sem.req_manual_normal = true;
   app_config.sem.suspended_manually = false;
   app_config.sem.disabled_manually = false;
   app_config_write();
}


//////////////////////////////////////////////////////////    Transition    //////////////////////////////////////////////////


static size_t count_active_span(const SignalPattern * pat)
{
   size_t count = 0;
   const SignalSpan * span = (const SignalSpan *)(pat + 1);
   
   for(size_t i = 0; i < pat->span_count; i++, span++)
   {
      count += span->count;
   }
   
   return count;
}

static void clear_transition(const SignalSchedule * sch)
{
   const SignalPattern * pat = sem_next_pattern(sch, NULL);
   
   while(pat != NULL)
   {
      SignalPattern * mod_pat = (SignalPattern *) pat;
      mod_pat->flags &= ~kPatFlagTrazit;
      
      pat = sem_next_pattern(sch, pat);
   }
}

static void set_transition(const SignalSchedule * sch)
{
   const SignalPattern * pat = sem_next_pattern(sch, NULL);
   
   while(pat != NULL)
   {
      SignalPattern * mod_pat = (SignalPattern *) pat;
      
      if(pat->span_count > 0 && count_active_span(pat) != sch->period)
         mod_pat->flags |= kPatFlagTrazit;
      
      pat = sem_next_pattern(sch, pat);
   }
}

static bool transition_done(const SignalSchedule * sch, bool out)
{
   const SignalPattern * pat = sem_next_pattern(sch, NULL);
   
   while(pat != NULL)
   {
      if(pat->span_count > 0 && count_active_span(pat) != sch->period)
      {
         if(out && (pat->flags & kPatFlagTrazit) == 0)
            return false;

         if(!out && (pat->flags & kPatFlagTrazit) > 0)
            return false;
      }
      
      pat = sem_next_pattern(sch, pat);
   }
   
   return true;
}


static void print_transition(const SignalSchedule * sch)
{
   const SignalPattern * pat = sem_next_pattern(sch, NULL);
   
   DBGHDR(kLvlVerb, "trans: (%3u)  ", (chronos_get_time() % sch->period) + 1);
   while(pat != NULL)
   {
      SignalPattern * mod_pat = (SignalPattern *) pat;
      size_t set = (mod_pat->flags & kPatFlagTrazit) > 0;
      DBGRAW(kLvlVerb, "%u ", set);
      pat = sem_next_pattern(sch, pat);
   }
   
   DBGLN(kLvlVerb);
}

static size_t str_fill_board_map(char * buff, size_t buff_size, uint32_t map)
{
   size_t size = 0;

   uint32_t mask = 1;
   for(size_t i = 0; map; i++, mask <<= 1)
   {
      if(mask & map)
      {
         size += snprintf(&buff[size], buff_size - size, "P%u\n", i + 1);
         map -= mask;
      }
   }
   
   return size;
}

static void sem_sch_changed(void)
{
   sem.state.str_net[0] = 0;
   sem.state.str_ctrl[0] = 0;
   sem.state.str_sch[0] = 0;
      
   if(sem.netw != NULL)
   {
      snprintf(sem.state.str_net, sizeof(sem.state.str_net), "%s", sem.netw->name);
   }
   
   if(sem.ctrl != NULL)
   {
      snprintf(sem.state.str_ctrl, sizeof(sem.state.str_ctrl), sem.ctrl->name);
   }
   
   if(sem.curr_sch != NULL)
   {
      snprintf(sem.state.str_sch, sizeof(sem.state.str_sch), sem.curr_sch->name);
   }
   
   sem.req_sch_changed = true;
}

/*
static void report_mallfunction(bool start)
{
   static uint32_t last_report = 0;
   static size_t period_id = 0;
   
   uint32_t epoch = timer_epoch();
   
   if(start)
   {
      period_id = 0;
   }
   
   if(!start && (epoch - last_report < sem.config.sms_periods[period_id]))
   {
      return;
   }
   
   last_report = epoch;
   if(period_id < sem.config.sms_period_count - 1)
      period_id++;
   
   switch(sem.state.global)
   {
      case kSemStateNormal:
      {
         com_report_normal_operation();
         break;
      }

      case kSemStateBoardDisconnected:
      {
         com_report_board_disconnected(sem.metrics.disconnected_boards);
         break;
      }
      
      case kSemStateBoardUnpowered:
      {
         com_report_board_unpowered(sem.metrics.unpowered_boards);
         break;
      }
      
      case kSemStateBoardFailure:
      {
         com_report_board_failed(sem.metrics.failed_boards);
         break;
      }
      
      case kSemStateEmergency:
      {
         com_report_emergency();
         break;
      }
      
      case kSemStateBulbAlert:
      case kSemStateBulbFailure:
      {
         com_report_burnt_bulbs(
            sem.metrics.burnt_bulbs_critical, 
            sem.metrics.burnt_bulbs_non_critical, 
            COUNT(sem.metrics.burnt_bulbs_critical),
            sem.metrics.have_burnt_critical);
         
         break;
      }
   };
   
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////


void sem_init(const SemConfig * sem_config)
{
   sem = (SemInternal) {
     .config = *sem_config,
     .state = {
        .global = kSemStateInit,
        .error = kSemErrorNone,
     },
   };
}

void sem_start(void)
{
   const SignalController * ctrl = &sem_demo_prog.ctrl;
   
   sem.netw = logic_slink_get_prog();
   if(sem.netw != NULL)
      ctrl = (const SignalController *)(sem.netw + 1);
   
   sem_set_program(ctrl);
}

uint32_t sem_get_period(const uint32_t time)
{
   if (sem.curr_sch == NULL)
      return 0;
   
   return sem.curr_sch->period;
}

const SignalSchedule * sem_get_current_sch(void)
{
   if (sem.curr_sch == NULL)
      return NULL;
   
   return sem.curr_sch;
}

const char * sem_get_state_str(bool friendly)
{
   if (!friendly)
   {
      if(sem.state.global >= COUNT(sem_state_str))
      {
         DBG(kLvlError, "sem, invalid state value %u", sem.state.global);
         return "undefined";
      }
      
      return sem_state_str[sem.state.global];
   }
   else
   {
      if(sem.state.global >= COUNT(sem_state_friendly_str))
      {
         DBG(kLvlError, "sem, invalid state value %u", sem.state.global);
         return "undefined";
      }
      
      return sem_state_friendly_str[sem.state.global];
   }
}

const char * sem_get_error_str(void)
{
   if(sem.state.error >= COUNT(sem_error_str))
   {
      DBG(kLvlError, "sem, invalid error value %u", sem.state.error);
      return "undefined";
   }
   
   return sem_error_str[sem.state.error];
}

const SemState * sem_get_state(void)
{
   return &sem.state;
}

const SemPowerMetrics * sem_get_metrics(void)
{
   return &sem.metrics;
}

void sem_set_program(const SignalController * prog)
{
   if (!prog)
      sem.ctrl = &sem_demo_prog.ctrl;
   else sem.ctrl = prog;
   
   const PCtrlSetup port = {
      .pctrl_count = sem.ctrl->port_count,
   };

   sem.metrics = (SemPowerMetrics) {0};
   change_state(kSemStateNormal, kSemErrorNone);
   pctrl_setup(&port);
}

void sem_hang(const bool susp)
{
   sem_clear();
   sem_commit();
   
   sem.disable_sem_update = susp;
}

void sem_suspend_sch_check(const bool on)
{
   sem.suspended_sch_check = on;
}

void sem_service(void)
{
   if(sem.req_state_changed)
   {
      size_t state;
      size_t error;
      
      do
      {
         sem.req_state_changed = false;
         state = sem.state.global;
         error = 0;
      } while(sem.req_state_changed);
      
      sem_update_state_details();
      state_sem_update();
   }
   
   if(sem.req_sch_changed)
   {
      sem.req_sch_changed = false;
      sem_update_state_details();
      state_sem_new_sch();
   }
}

static void safely_run_schedule(const uint32_t time, const uint32_t week_sec, const uint32_t milli, const SignalSchedule * sch)
{
   bool failsafe_error = false;
   sem.metrics.have_burnt_critical = false;
   sem.metrics.have_burnt_non_critical = false;

   run_schedule(week_sec, milli, sch);

   for(size_t i = 0; i < sem.ctrl->port_count; i++)
   {
      uint32_t burnt = pctrl_get_burnt(i + 1);

      sem.metrics.burnt_bulbs_critical[i] &= burnt;
      sem.metrics.burnt_bulbs_non_critical[i] &= burnt;

      if(sem.metrics.burnt_bulbs_critical[i])
         sem.metrics.have_burnt_critical = true;

      if(sem.metrics.burnt_bulbs_non_critical[i])
         sem.metrics.have_burnt_non_critical = true;
   }

   if(sem.ctrl->flags & kCtrlFlagMonitorBulbs)
   {
      if(sem.metrics.have_burnt_critical)
      {
         if(sch->flags & kSchFlagMonitorBurntBulbs)
         {
            if(!(sch->flags & kSchFlagMallfunctionFallback))
            {
               failsafe_error = true;
            }
         }
      }
      else if (sem.metrics.have_burnt_non_critical)
      {
         change_state(kSemStateAlert, kSemErrorBulbFailure);
      }
   }
   
   // Resume from Alert?
   if(sem.state.global == kSemStateAlert && !sem.metrics.have_burnt_non_critical)
   {
      change_state(kSemStateNormal, kSemErrorNone);
   }
   
   if(failsafe_error)
   {
      //switch_to_fallback(week_sec);
      change_state(kSemStateError, kSemErrorBulbFailure);
   }
   
   sem_commit();
}

void sem_tick(const uint32_t time, const uint32_t milli)
{
   if(sem.disable_sem_update)
      return;
   
   sem_clear();
   sem_tick_config(milli < 500);
   
   if (sem.ctrl == NULL)
      return;
   
   uint32_t week_sec = dte_epoch_seconds_from_monday(time);
   const SignalSchedule * sch = NULL;
   
   // Get the power board metrics
   pctrl_compile_metrics();
   
   // Check if power boards are healthy now
   // This will also update the state, if required
   check_power_board_error_resume();
   
   
   // Do we need to manually suspend?
   if(sem.req_manual_suspend)
   {
      sem.req_manual_suspend = false;
      
      // Already suspended?
      if (sem.state.global == kSemStateNormal || 
          sem.state.global == kSemStateAlert ||
          sem.state.global == kSemStateSuspended ||
          sem.state.global == kSemStateDisabled)
      {
         //switch_to_fallback(week_sec);
         change_state(kSemStateSuspendedManually, kSemErrorNone);
      }
   }
   
   // Do we need to manually disable?
   if(sem.req_manual_disable)
   {
      sem.req_manual_disable = false;
      
      // Already disabled?
      if (sem.state.global < kSemStateFatal)
      {
         change_state(kSemStateDisabled, kSemErrorNone);
      }
   }
   
   // Do we need to resume?
   if(sem.req_manual_normal)
   {
      sem.req_manual_normal = false;
      
      if (sem.state.global == kSemStateSuspended ||
          sem.state.global == kSemStateSuspendedManually ||
          sem.state.global == kSemStateDisabled ||
         (sem.state.global == kSemStateError && sem.state.error == kSemErrorBulbFailure))
      {
         change_state(kSemStateNormal, kSemErrorNone);

         sem.transition_out = false;
         sem.transition_in = false;
      }
   }
     
   // Run the normal schedule 
   if(sem.state.global == kSemStateNormal || 
      sem.state.global == kSemStateAlert)
   {
      sch = sem_next_sch(sem.ctrl, NULL);
      while(sch != NULL)
      {
         if (is_in_schedule(week_sec, sch))
            break;
         sch = sem_next_sch(sem.ctrl, sch);
      }  
   }
   
   else
   
   // Run the suspended schedule
   if(sem.state.global == kSemStateSuspended || 
      sem.state.global == kSemStateSuspendedManually ||
      sem.state.global == kSemStateError)
   {
      sch = sem_next_sch(sem.ctrl, NULL);
      while(sch != NULL)
      {
         if (is_in_schedule(week_sec, sch) && (sch->flags & kSchFlagMallfunctionFallback))
            break;

         sch = sem_next_sch(sem.ctrl, sch);
      }
   }
   
   if (sch != NULL)
      safely_run_schedule(time, week_sec, milli, sch);
   
   if (sem.curr_sch != sch)
   {
      sem.curr_sch = sch;
      sem_sch_changed();
   }
   
   sem_commit();
   
   return;
   
   
     
   
   /*
   
   // Run normal schedule
   if(sem.state.global != kSemStateNormal && sem.state.global != kSemStateAlert)
   {
      run_schedule(week_sec, milli, sem.curr_sch);
      sem_commit();
      return;
   }
   
   if(!sem.suspended_sch_check)
   {
      sch = sem_next_sch(sem.ctrl, NULL);

      while(sch != NULL)
      {
         if (is_in_schedule(week_sec, sch))
            break;
         sch = sem_next_sch(sem.ctrl, sch);
      }

      if(sch == NULL)
      {
          sem_commit();
          return;
      }
   }
   
   if(sem.curr_sch == NULL && sch == NULL)
   {
      sem_commit();
      return;
   }
   
   if(sch == NULL)
      sch = sem.curr_sch;
   
   if(sem.curr_sch == NULL)
   {
      if(sch->flags & kSchFlagTransIn)
      {
         sem.transition_in = true;
         sem.tranzition_safety = sch->period + 1;
      }
      
      sem_adopt_sch(sch, true);
   }
   else if(sem.curr_sch->id != sch->id)
   {
      if(!sem.transition_in)
      {
         //DBG(kLvlInfo, "transit %04X %04X", sem.curr_sch->id, sch->id);

         if(sem.curr_sch->flags & kSchFlagTransOut || sch->flags & kSchFlagTransIn)
         {
            sem.transition_out = true;
            sem.transition_in = true;
            sem.tranzition_safety = sem.curr_sch->period + sch->period + 1;
         }
         else
         {
            sem_adopt_sch(sch, true);
         }
      }
   }
   
   if(sem.transition_out)
   {
      if(transition_done(sem.curr_sch, true))
      {
         //DBG(kLvlInfo, "transit out done");
         
         sem.transition_out = false;
         sem_adopt_sch(sch, true);
         
         if(sem.transition_in)
            set_transition(sem.curr_sch);
         else clear_transition(sem.curr_sch);
         
         //print_transition(sem.curr_sch);
      }
   }
   
   if(!sem.transition_out && sem.transition_in)
   {
      if(transition_done(sem.curr_sch, false))
      {
         //DBG(kLvlInfo, "transit in done");
         sem.transition_in = false;
      }
   }
   
   
   safely_run_schedule(time, week_sec, milli, sem.curr_sch);

   
   static uint32_t last_time = 0;   
   if(last_time != time)
   {
      last_time = time;
      
      if(sem.transition_in || sem.transition_out)
      {
         if(sem.tranzition_safety > 0)
            sem.tranzition_safety--;
         
         if(sem.tranzition_safety == 0)
         {
            DBG(kLvlError, "sem, transition timeout");
            
            if(sem.transition_out)
               sem_adopt_sch(sch, true);
            
            clear_transition(sem.curr_sch);
            
            sem.transition_in = false;
            sem.transition_out = false;
         }
         
         print_transition(sem.curr_sch);
      }
   }
    * */
}
