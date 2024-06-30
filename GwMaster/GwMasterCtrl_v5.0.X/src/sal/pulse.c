#include <xc.h>
#include "pulse.h"
#include "sal/debug.h"

typedef struct
{
   size_t flags;
   uint32_t passed;
   uint32_t pulses;
} PulseData;

static struct
{
   const PulseInstance * inst;
   size_t count;
   PulseData data[20];
} pu;

/* 
 * Gets the list of pins with their patterns.
 */
void pulse_init(const PulseConfig * config)
{
   pu.inst = config->inst;
   pu.count = config->count;
   
   if(pu.count > COUNT(pu.data))
   {
      DBG(kLvlError, "pulse, not enough pulse data slots.");
      pu.count = COUNT(pu.data);
   }
}

/* 
 * Activates a IO pin.
 */
void pulse_deactive(const PulseInstance *inst)
{
   volatile uint32_t * port = inst->pin_port_clr;
   
   if(inst->flags & kPulseRevPolarity)
   {
      port = inst->pin_port_set;
   }
   
   *port = inst->pin_mask;
}

/* 
 * Deactivates a IO pin.
 */
void pulse_active(const PulseInstance * inst)
{
   volatile uint32_t * port = inst->pin_port_set;
   
   if(inst->flags & kPulseRevPolarity)
   {
      port = inst->pin_port_clr;
   }
   
   *port = inst->pin_mask;
}

/* 
 * Activates a pattern, with a specific number of pulses.
 */
void pulse_start_count(const size_t index, const size_t count)
{
   if(index >= pu.count)
      return;
   
   const PulseInstance *inst = &pu.inst[index];
   PulseData *data = &pu.data[index];
   
   __builtin_disable_interrupts();
   
   data->flags |= kPulseEnable;
   data->passed = 0;
   data->pulses = count;

   if(inst->flags & kPulseStartActive)
   {
      data->pulses--;
      data->flags |= kPulseActive;
      pulse_active(inst);
   }
   
   __builtin_enable_interrupts();
}

void pulse_reset(const size_t index)
{
   if(index >= pu.count)
      return;
   
   const PulseInstance *inst = &pu.inst[index];
   PulseData *data = &pu.data[index];
   
   __builtin_disable_interrupts();
   
   data->flags |= kPulseEnable;
   data->passed = 0;
   data->pulses = inst->total_pulses;

   if(inst->flags & kPulseStartActive)
   {
      data->pulses--;
      data->flags |= kPulseActive;
      pulse_active(inst);
   }
   
   __builtin_enable_interrupts();
}

void pulse_set_isr(const size_t index, const bool en)
{
   if(index >= pu.count)
      return;
   
   const PulseInstance *inst = &pu.inst[index];
   
   if(en) pulse_active(inst);
      else pulse_deactive(inst);
}

void pulse_start(const size_t index)
{
   if(index >= pu.count)
      return;
   
   const PulseInstance *inst = &pu.inst[index];
   PulseData *data = &pu.data[index];
   
   __builtin_disable_interrupts();
   
   if((data->flags & kPulseEnable) == 0)
   {
      data->flags |= kPulseEnable;
      data->passed = 0;
      data->pulses = inst->total_pulses;

      if(inst->flags & kPulseStartActive)
      {
         data->pulses--;
         data->flags |= kPulseActive;
         pulse_active(inst);
      }
   }
   
   __builtin_enable_interrupts();
}

/* 
 * Stops a pattern with it's associated pin
 */
void pulse_stop(const size_t index)
{
   if(index >= pu.count)
      return;
   
   const PulseInstance *inst = &pu.inst[index];
   PulseData *data = &pu.data[index];
   
   __builtin_disable_interrupts();
   
   data->flags &= ~(kPulseEnable | kPulseActive);
   
   if(data->flags & kPulseCloseActive) pulse_active(inst);
      else pulse_deactive(inst);
   
   __builtin_enable_interrupts();
}

/* 
 * Service routine, must be called periodically. Usually from a timer ISR.
 */
void pulse_service(const uint32_t mili)
{
   PulseInstance *inst = (PulseInstance *) &pu.inst[0];
   PulseData *data = &pu.data[0];
   
   for(size_t i = 0; i < pu.count; ++i, inst++, data++)
   {
      if(data->flags & kPulseEnable)
      {
         uint32_t period = data->flags & kPulseActive ? inst->period_on : inst->period_off;
         data->passed += mili;
         
         if(data->passed >= period)
         {
            data->passed -= period;
            
            if(data->flags & kPulseActive) pulse_deactive(inst);
               else pulse_active(inst);
           
            data->flags ^= kPulseActive;
           
            if((kPulseInfinite != inst->total_pulses) && (data->pulses > 0))
            {
               data->pulses--;
               if(!data->pulses)
               {
                  data->passed = 0;
                  data->flags &= ~(kPulseActive | kPulseEnable);
                  
                  if(data->flags & kPulseCloseActive)
                     pulse_active(inst);
                  else pulse_deactive(inst);
               }
            }
         }
      } 
   }
}