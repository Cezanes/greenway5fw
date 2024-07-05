#include "shared_buff.h"

#include "sal/debug.h"



static struct
{
   size_t chunk_map;
   size_t chunk_size;
   size_t chunk_count;
   void * chunk_ptrs[4];
   const SharedBuff * buff;
} sb;


void shared_buff_init(const SharedBuff * buff)
{
   sb.buff = buff;
   
   sb.chunk_count = sb.buff->chunk_count;
   
   if(sb.chunk_count > COUNT(sb.chunk_ptrs))
   {
      DBG(kLvlError, "shared, chunk count too large");
      sb.chunk_count = COUNT(sb.chunk_ptrs);
   }
   
   sb.chunk_size = sb.buff->size / sb.buff->chunk_count;
   
   for(size_t i = 0; i < sb.buff->chunk_count; i++)
   {
      sb.chunk_ptrs[i] = &sb.buff->ptr[sb.chunk_size * i];
   }
}

void * shared_buff_get_chunk(void)
{
   size_t mask = 1;

   for(size_t i = 0; i < sb.buff->chunk_count; i++, mask <<= 1)
   {
      if((mask & sb.chunk_map) == 0)
      {
         sb.chunk_map |= mask;
         return sb.chunk_ptrs[i];
      }
   }
   
   DBG(kLvlError, "shared, no available free chunks");
   
   return NULL;
}

void shared_buff_release_chunk(const void * chunk)
{
   if(chunk == 0)
   {
      DBG(kLvlError, "shared, released a NULL ptr");
      return;
   }
   
   size_t mask = 1;
   
   for(size_t i = 0; i < sb.buff->chunk_count; i++, mask <<= 1)
   {
      if(sb.chunk_ptrs[i] == chunk)
      {
         if((sb.chunk_map | mask) == 0)
         {
            DBG(kLvlError, "shared, chunk released but not previously taken %X", sb.chunk_map);
         }
         
         sb.chunk_map &= ~mask;
      }
   }
}

void * shared_buff_get_full(void)
{
   if(sb.chunk_map)
   {
      DBG(kLvlError, "shared, cannot take full buff %X", sb.chunk_map);
      return NULL;
   }
   
   sb.chunk_map = -1;
   
   return sb.buff->ptr;
}

void shared_buff_release_full(void)
{
   if(!sb.chunk_map)
   {
      DBG(kLvlError, "shared, full buff released but not previously taken %X", sb.chunk_map);
   }
   
   sb.chunk_map = 0;
}

size_t shared_buff_chunk_size(void)
{
   return sb.chunk_size;
}