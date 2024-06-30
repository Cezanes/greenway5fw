#include "sem_objects.h"
#include "sal/debug.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////


static const SignalBulb * next_bulb(const SignalBulb * bulb)
{
   const uint8_t * ptr = (const uint8_t *) bulb;
   const size_t offs = sizeof(SignalBulb);
   return (const SignalBulb *)&ptr[offs];
}

static const SignalPattern * next_pattern(const SignalPattern * pat)
{
   const uint8_t * ptr = (const uint8_t *) pat;
   
   size_t offs = sizeof(SignalPattern);
   offs += pat->span_count * sizeof(SignalSpan);
   offs += pat->bulb_count * sizeof(SignalBulb);
   
   return (const SignalPattern *)&ptr[offs];
}

static const SignalSchedule * next_schedule(const SignalSchedule * sch)
{
   const SignalPattern * pat = (const SignalPattern *)(sch + 1);
   size_t patterns = sch->pattern_count;
   
   while(patterns)
   {
      patterns--;
      pat = next_pattern(pat);
   }
   
   return (const SignalSchedule *)pat;
}

static const SignalBulbDesc * next_bulb_desc(const SignalBulbDesc * bdesc, size_t index)
{
   return &bdesc[index];
}

const SignalController * sem_next_ctrl(const SignalNetwork * netw, const SignalController * ctrl)
{
   if(netw->controller_count == 0)
      return NULL;
      
   if(ctrl == NULL)
   {
      ctrl = (const SignalController *)(netw + 1);
      return ctrl;
   }
   
   const void * sch = ctrl + 1;
   
   if ((uint32_t)sch - (uint32_t)netw >= netw->size)
      return NULL;
   
   for(size_t i = 0; i < ctrl->schedule_count; i++)
   {
      sch = next_schedule(sch);
   }
   
   sch = next_bulb_desc(sch, ctrl->port_count * ctrl->port_size);
   
   if ((uint32_t)sch - (uint32_t)netw >= netw->size)
      return NULL;   
   
   return sch;
}

const SignalSchedule * sem_next_sch(const SignalController * ctrl, const SignalSchedule * sch)
{
   if(ctrl->schedule_count == 0)
      return NULL;
   
   const void * schit = ctrl + 1;
   
   if(sch == NULL)
      return schit;
   
   for(size_t i = 0; i < ctrl->schedule_count; i++)
   {
      const void * schnext = next_schedule(schit);
      
      if(schit == sch)
      {
         if(i == ctrl->schedule_count - 1)
            return NULL;
         
         return schnext;
      }
      
      schit = schnext;
   }
   
   return NULL;
}

const SignalPattern * sem_next_pattern(const SignalSchedule * sch, const SignalPattern * pat)
{
   if(sch->pattern_count == 0)
      return NULL;
   
   const SignalPattern * pat_it = (const SignalPattern *)(sch + 1);
   
   if(pat == NULL)
      return pat_it;
   
   for(size_t i = 0; i < sch->pattern_count; i++)
   {
      const SignalPattern * pat_next = next_pattern(pat_it);
      
      if(pat_it == pat)
      {
         if(i == sch->pattern_count - 1)
            return NULL;
         
         return pat_next;
      }
      
      pat_it = pat_next;
   }
   
   return NULL;
}

const SignalBulb * sem_next_bulb(const SignalPattern * pat, const SignalBulb * bulb)
{
   if(pat->bulb_count == 0)
      return NULL;
   
   const void * bulbit = pat + 1;
   
   if(bulb == NULL)
      return bulbit;
   
   for(size_t i = 0; i < pat->bulb_count; i++)
   {
      const void * bulbnext = next_bulb(bulbit);
      
      if(bulbit == bulb)
      {
         if(i == pat->bulb_count - 1)
            return NULL;
         
         return bulbnext;
      }
      
      bulbit = bulbnext;
   }
   
   return NULL;
}

const SignalBulbDesc * sem_get_bulb_desc(const SignalController * ctrl, size_t port, size_t id)
{
   if(port >= ctrl->port_count || id >= ctrl->port_size)
   {
      return NULL;
   }
   
   const void * sch = ctrl + 1;
   
   if ((uint32_t)sch - (uint32_t)ctrl >= ctrl->size)
      return NULL;
   
   for(size_t i = 0; i < ctrl->schedule_count; i++)
   {
      sch = next_schedule(sch);
   }
   
   return next_bulb_desc(sch, ctrl->port_size * port + id);
}

void sem_print_sch(const SignalSchedule * sch)
{
   DBG(kLvlInfo, "sem, sch '%s', size %u, flags %02X, start %u, duration %u, days %u, signals %u", sch->name, sch->size, sch->flags, sch->time_start, sch->time_duration, sch->repeat_days, sch->pattern_count);
   
   return;
   
   if(sch->pattern_count > 0)
   {
      const SignalPattern * pat = sem_next_pattern(sch, NULL);

      while(pat != NULL)
      {
         DBG(kLvlInfo, "sem, sig spans %u, bulbs %u", pat->span_count, pat->bulb_count);

         const SignalSpan * span = (const SignalSpan *)(pat + 1);
         for(size_t i = 0; i < pat->span_count; i++, span++)
         {
            DBG(kLvlInfo, "sem, span %u:%u %u", span->offs, span->count, span->blink);
         }

         const SignalBulb * bulb = (const SignalBulb *)(span);
         for(size_t i = 0; i < pat->bulb_count; i++, bulb++)
         {
            DBG(kLvlInfo, "sem, bulb P%u.%02u", bulb->port, bulb->pin);
         }

         pat = sem_next_pattern(sch, pat);
      }
   }
}

void sem_print_port(const SignalController * ctrl)
{
   DBG(kLvlInfo, "sem, ctrl '%s', id %u, sch %u, ports %u, size %u", ctrl->name, ctrl->id, ctrl->schedule_count, ctrl->port_count, ctrl->port_size);

   const SignalBulbDesc * bdesc;
   
   char desc[sizeof(bdesc->name) + 1];
   desc[sizeof(bdesc->name)] = 0;
   
   for(size_t i = 0; i < ctrl->port_count; i++)
   {
      DBGHDR(kLvlInfo, "sem, port %u: ", i + 1);
      
      for(size_t j = 0; j < ctrl->port_size; j++)
      {
         bdesc = sem_get_bulb_desc(ctrl, i, j);
         strncpy(desc, bdesc->name, sizeof(bdesc->name));
         
         DBGRAW(kLvlInfo, "%-8s ", &desc[0]);
      }
      
      DBGLN(kLvlInfo);
   }
}