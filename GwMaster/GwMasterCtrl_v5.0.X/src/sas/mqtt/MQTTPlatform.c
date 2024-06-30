
#include "MQTTPlatform.h"
#include "time.h"
#include "sal/timer.h"

void TimerInit(Timer * timer)
{
   *timer = (Timer){.tick = 0};
}

char TimerIsExpired(Timer * timer)
{
   if(timer_tick() >= timer->tick)
      return true;
   
   return false;
}

void TimerCountdownMS(Timer * timer, unsigned int ms)
{
   timer->tick = timer_tick() + ms;
}

void TimerCountdown(Timer* timer, unsigned int sec)
{
   timer->tick = timer_tick() + sec * 1000;
}

int TimerLeftMS(Timer * timer)
{
   uint32_t tick = timer_tick();
   
   if(timer->tick < tick)
      return 0;
   
   return (int)(timer->tick - tick);
}
