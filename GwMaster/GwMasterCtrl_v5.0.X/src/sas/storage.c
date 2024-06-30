#include "storage.h"
#include "sal/debug.h"

/////////////////////////////////////////////////////////////////////////////////////

#define UPPER_FLASH_ADDRESS                   0x1FFFFFFF
#define PHYS_ADDR(x)         (((uint32_t)x) & 0x1FFFFFFF)

enum
{
   kNvmCmdClearError  = 0x4000,
   kNvmCmdWriteWord   = 0x4001,
   kNvmCmdWriteDWord  = 0x4002,
   kNvmCmdWriteRow    = 0x4003,
   kNvmCmdErasePage   = 0x4004,
};

/////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
   const StorageSector * sectors;
   size_t sector_count;
} StorageInternal;

static StorageInternal storage;

/////////////////////////////////////////////////////////////////////////////////////

/*
uint32_t __attribute__((nomips16)) NVMUnlock(unsigned int nvmop) 
{
    __builtin_disable_interrupts();

    NVMCON = nvmop;

    NVMKEY = 0xAA996655;
    NVMKEY = 0x556699AA;

    NVMCONSET = 0x8000;

    while (NVMCON & 0x8000);

    __builtin_enable_interrupts();

    NVMCONCLR = 0x0004000;

    return (NVMCON & 0x3000);
}


uint32_t NVMWrite64bitWord(void* address, uint32_t data1, uint32_t data2) 
{
    unsigned int res;
    // Load data into NVMDATA register
    NVMDATA0 = data1;
    NVMDATA1 = data2;
    // Load address to program into NVMADDR register
    NVMADDR = (unsigned int) PHYS_ADDR(address);
    // Unlock and Write Word
    res = NVMUnlock(0x4002);
    // Return Result
    return res;
}*/

static uint32_t __attribute__((nomips16)) nvm_unlock(const uint32_t nvmop) 
{
   // Suspend or Disable all Interrupts
   uint32_t status;
   asm volatile ("di %0" : "=r" (status));
      
   // Enable Flash Write/Erase Operations and Select
   // Flash operation to perform
   NVMCON = nvmop;
      
   // Write Keys
   NVMKEY = 0xAA996655;
   NVMKEY = 0x556699AA;
    
   // Start the operation using the Set Register
   NVMCONSET = 0x8000;
    
   // Wait for operation to complete
   while (NVMCON & 0x8000);
    
   // Restore Interrupts
   if (status & 0x00000001)
      {asm volatile ("ei");}
   else {asm volatile ("di");}
    
   // Disable NVM write enable
   NVMCONCLR = 0x0004000;
    
   // Return WRERR and LVDERR Error Status Bits 
   uint32_t res = (NVMCON & 0x3000);
   
   if(res > 0)
   {
      DBG(kLvlError, "storage, nvm operation failed %X", res);
   }
   
   return res;
}

static bool nvm_write_dword(const void * address, uint32_t Data) 
{
   const uint32_t flash_addr = PHYS_ADDR((uint32_t)address);
   
   // if address is not aligned, return.
   if ((flash_addr & (STORAGE_WORD_SIZE - 1)) || (flash_addr > UPPER_FLASH_ADDRESS))
   {
      DBG(kLvlError, "storage, invalid dword addr %X", flash_addr);
      return false;
   }
   
   // Load data into NVMDATA register
   NVMDATA = Data;
    
   // Load address to program into NVMADDR register
   NVMADDR = flash_addr;
    
   // Unlock and Write Word
   return nvm_unlock(kNvmCmdWriteWord) == 0;
}

static bool nvm_write_row(const void * address, const void * data)
{
   const uint32_t flash_addr = PHYS_ADDR(address);

   // Validate address is row aligned and in flash area
   if ((flash_addr & (STORAGE_ROW_SIZE - 1)) || (flash_addr > UPPER_FLASH_ADDRESS))
   {
      DBG(kLvlError, "storage, invalid page row addr %X", flash_addr);
      return false;
   }
   
   // Set NVMADDR to Start Address of row to program
   NVMADDR = flash_addr;

   // Set NVMSCRCADDR to the SRAM data buffer Address
   NVMSRCADDR = PHYS_ADDR(data);

   // Unlock and Write Row
   return nvm_unlock(kNvmCmdWriteRow) == 0;
}

static bool nvm_erase_page(const void * address) 
{
   const uint32_t flash_addr = PHYS_ADDR(address);

   // Make sure request is page aligned.
   if (flash_addr & ((STORAGE_PAGE_SIZE) - 1))
   {
      DBG(kLvlError, "storage, erase invalid page %X", flash_addr);
      return false;
   }
    
   // Set NVMADDR to the Start Address of the page to erase
   NVMADDR = flash_addr;

   //Unlock and Erase Page
   return nvm_unlock(kNvmCmdErasePage) == 0;
}


/////////////////////////////////////////////////////////////////////////////////////


void storage_init(const StorageConfig * config)
{
   storage = (StorageInternal) {
     .sectors = config->sectors,
     .sector_count = config->sector_count,
   };
}

const void * storage_get_ptr(const size_t sector_id)
{
   if (sector_id >= storage.sector_count)
   {
      DBG(kLvlError, "storage, invalid sector id %u", sector_id);
      return NULL;
   }
   
   return storage.sectors[sector_id].ptr;
}


uint32_t storage_get_size(const size_t sector_id)
{
   if (sector_id >= storage.sector_count)
   {
      DBG(kLvlError, "storage, invalid sector id %u", sector_id);
      return 0;
   }
   
   return storage.sectors[sector_id].size;
}

bool storage_erase(const size_t sector_id)
{
   if (sector_id >= storage.sector_count)
   {
      DBG(kLvlError, "storage, invalid sector id %u", sector_id);
      return false;
   }
    
   const uint8_t * addr = storage.sectors[sector_id].ptr;
   uint32_t size = storage.sectors[sector_id].size;
   
   while (size)
   {
      DBG(kLvlVerb, "storage, erasing page %X", addr);

      if (!nvm_erase_page(addr))
      {
         DBG(kLvlError, "storage, erase sector %X failed", addr);
         return false;
      }
      
      addr += STORAGE_PAGE_SIZE;
      size -= STORAGE_PAGE_SIZE;
   }
       
   return true;
}

static bool write_row(const uint8_t * addr, const uint8_t * ptr)
{
   DBG(kLvlDbg, "storage, writing page %X", addr);
   
   if (!nvm_write_row(addr, ptr))
   {
      DBG(kLvlError, "storage, cannot write row %X", addr);
      return false;
   }
   
   return true;
}

bool storage_write(const size_t sector_id, const void * dest, const void * ptr, const uint32_t size)
{
   if (sector_id >= storage.sector_count)
   {
      DBG(kLvlError, "storage, invalid sector id %u", sector_id);
      return false;
   }
   
   const uint8_t * sector_addr = storage.sectors[sector_id].ptr;
   const uint32_t sector_size = storage.sectors[sector_id].size;
   
   if ((uint32_t)dest < (uint32_t)sector_addr || (uint32_t)dest >= (uint32_t)sector_addr + sector_size)
   {
      DBG(kLvlError, "storage, write addr outside sector ");
      return false;
   }
   
   uint32_t offs = (uint32_t)dest - (uint32_t)sector_addr;
   
   if (offs + size > sector_size)
   {
      DBG(kLvlError, "storage, write size exceeds sector space %u vs %u", offs + size, sector_size);
      return false;
   }
   
   const uint8_t * data = ptr;
   
   uint32_t offs_shift = offs & (STORAGE_ROW_SIZE - 1);
   uint32_t remaining = size;
   
   uint8_t buf[STORAGE_ROW_SIZE];
   
   if (offs_shift)
   {
      uint32_t offs_sector = offs & ~(STORAGE_ROW_SIZE - 1);
      uint32_t to_write = remaining;
      
      if (to_write > STORAGE_ROW_SIZE - offs_shift)
         to_write = STORAGE_ROW_SIZE - offs_shift;
      
      memset(buf, 0xFF, sizeof(buf));
      memcpy(buf, sector_addr + offs_sector, offs_shift);
      memcpy(&buf[offs_shift], data, to_write);
   
      if (!write_row(sector_addr + offs_sector, buf))
         return false;
      
      data += to_write;
      remaining -= to_write;
      sector_addr += STORAGE_ROW_SIZE;
   }
   
   while(remaining)
   {
      uint32_t to_write = remaining;
      
      if (to_write > STORAGE_ROW_SIZE)
         to_write = STORAGE_ROW_SIZE;
      
      memset(buf, 0xFF, sizeof(buf));
      memcpy(buf, data, to_write);
      
      if (!write_row(sector_addr, buf))
         return false;
      
      sector_addr += STORAGE_ROW_SIZE;
      remaining -= to_write;
      data += to_write;
   }
   
   if (0 != memcmp(ptr, dest, size))
   {
      DBG(kLvlError, "storage, write verification failed");
      return false;
   }
   
   return true;
}

bool storage_write_words(const size_t sector_id, const void * dest, const void * ptr, const uint32_t size)
{
   if (sector_id >= storage.sector_count)
   {
      DBG(kLvlError, "storage, invalid sector id %u", sector_id);
      return false;
   }
   
   const uint8_t * sector_addr = storage.sectors[sector_id].ptr;
   const uint32_t sector_size = storage.sectors[sector_id].size;
   
   if ((uint32_t)dest < (uint32_t)sector_addr || (uint32_t)dest >= (uint32_t)sector_addr + sector_size)
   {
      DBG(kLvlError, "storage, write addr outside sector ");
      return false;
   }
   
   uint32_t offs = (uint32_t)dest - (uint32_t)sector_addr;
   
   if (offs + size > sector_size)
   {
      DBG(kLvlError, "storage, write size exceeds sector space %u vs %u", offs + size, sector_size);
      return false;
   }
   
   const uint8_t * data = ptr;
   const uint8_t * addr = dest;

   if ((uint32_t)addr & 0x07)
   {
      DBG(kLvlError, "storage, write address not aligned %X", addr);
      return false;
   }
   
   uint32_t remaining = size;
   
   while(remaining > 0)
   {
      uint8_t buff[STORAGE_WORD_SIZE];
      memset(buff, 0xFF, sizeof(buff));
      
      uint32_t to_write = remaining;
      
      if(to_write > sizeof(buff))
         to_write = sizeof(buff);
      
      for(size_t i = 0; i < to_write; i++)
      {
         buff[i] = *data++;
         remaining--;
      }
      
      /*if(NVMWrite64bitWord(addr, *(uint32_t *)&buff[0], *(uint32_t *)&buff[4]) > 0)
         return false;*/
      
      if(!nvm_write_dword(addr, *(uint32_t *)&buff[0]))
         return false;
      
      addr += sizeof(buff);
   }
   
   if (0 != memcmp(ptr, dest, size))
   {
      DBG(kLvlError, "storage, write verification failed");
      return false;
   }
   
   return true;
}

bool storage_replace(const size_t sector_id, const uint32_t offs, const void * ptr, const uint32_t size)
{
   
}

