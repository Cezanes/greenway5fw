#ifndef STATEH
#define STATEH

#include "types.h"
#include "app/net/cellular.h"
#include "app/sem/semaphore.h"


typedef struct
{
   CellData cell;
} ComData;


typedef struct
{
   CellConfig cell;
} ComConfig;


typedef struct
{
   const SemState * sem;
   const SemPowerMetrics * metrics;
   bool gps_lock;
} GlobalState;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void state_init(ComData * data, const ComConfig * config);
void state_start(void);
void state_service(void);

const GlobalState * state_global(void);

void state_sem_update(void);
void state_sem_new_sch(void);




#endif