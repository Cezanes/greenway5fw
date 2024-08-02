#include "state.h"
#include "app/net/cellular.h"
#include "app/sem/semaphore.h"
#include "sas/gps.h"
#include "app/edge/edge.h"



static struct
{
   ComData * data;
   const ComConfig * config;
   GlobalState global;
} state;


/////////////////////////////////////////////////////////////////////////////////////////////////////////


const GlobalState * state_global(void)
{
   return &state.global;
}

void state_sem_state_changed(void)
{
   cell_report_new_state();
   edge_send_ctrl_status();
   //mqtt_status_changed();
}

void state_sem_new_sch(void)
{
   //mqtt_status_changed();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void state_init(ComData * data, const ComConfig * config)
{
   state.data = data;
   state.config = config;

   cell_init(&data->cell, &config->cell);
}

void state_start(void)
{
   state.global.sem = sem_get_state();
   state.global.metrics = sem_get_metrics();
   
   //mqtt_start();
   cell_start();
}

void state_service(void)
{
   cell_service();
   //mqtt_service();
   
   if(gps_have_time() != state.global.gps_lock)
   {
      state.global.gps_lock = gps_have_time();
      //mqtt_status_changed();
   }
}