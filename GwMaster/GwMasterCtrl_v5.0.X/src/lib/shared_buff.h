#ifndef SHARED_BUF
#define SHARED_BUF

#include "types.h"

typedef struct
{
   uint8_t * ptr;
   size_t size;
   size_t chunk_count;
} SharedBuff;


void shared_buff_init(const SharedBuff * buff);
void * shared_buff_get_chunk(void);
void shared_buff_release_chunk(const void * chunk);
void * shared_buff_get_full(void);
void shared_buff_release_full(void);

size_t shared_buff_chunk_size(void);



#endif