#ifndef STORAGE_H
#define STORAGE_H

#include "types.h"

#define FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS    32
#define FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS   (FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS  * 8)
#define FLASH_WRITE_ROW_SIZE_IN_PC_UNITS        (FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS  * 4)
#define FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS       (FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS * 4)

#define STORAGE_PAGE_SIZE      FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS
#define STORAGE_ROW_SIZE       FLASH_WRITE_ROW_SIZE_IN_PC_UNITS
#define STORAGE_WORD_SIZE      (4)


typedef struct
{
   uint32_t size;
   size_t pages;
   const uint8_t * ptr;
} StorageSector;

typedef struct
{
   const StorageSector * sectors;
   size_t sector_count;
} StorageConfig;

void storage_init(const StorageConfig * config);
const void * storage_get_ptr(const size_t sector_id);
uint32_t storage_get_size(const size_t sector_id);
bool storage_erase(const size_t sector_id);
bool storage_write(const size_t sector_id, const void * dest, const void * ptr, const uint32_t size);
bool storage_replace(const size_t sector_id, const uint32_t offs, const void * ptr, const uint32_t size);
bool storage_write_words(const size_t sector_id, const void * dest, const void * ptr, const uint32_t size);


#endif