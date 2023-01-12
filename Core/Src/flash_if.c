#define __FLASH_IF_C
    #include "flash_if.h"
#undef  __FLASH_IF_C

#include "SysParam.h"

const uint32_t ADDR_FLASH_SECTOR[12] = {ADDR_FLASH_SECTOR_0, ADDR_FLASH_SECTOR_1, ADDR_FLASH_SECTOR_2, ADDR_FLASH_SECTOR_3, ADDR_FLASH_SECTOR_4,
                                   ADDR_FLASH_SECTOR_5, ADDR_FLASH_SECTOR_6, ADDR_FLASH_SECTOR_7,ADDR_FLASH_SECTOR_8,ADDR_FLASH_SECTOR_9,
                                   ADDR_FLASH_SECTOR_10,ADDR_FLASH_SECTOR_11};


static uint32_t GetSector(uint32_t Address);
static void FLASH_If_Init(void);

static void FLASH_If_Init(void)
{
  HAL_FLASH_Unlock(); 

  /* Clear pending flags (if any) */  
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
void FLASH_If_Erase(uint32_t addr)
{
	uint32_t SectorError;
	FLASH_EraseInitTypeDef pEraseInit;

	FLASH_If_Init();

	pEraseInit.TypeErase = TYPEERASE_SECTORS;
	pEraseInit.Sector = GetSector(addr);
	pEraseInit.NbSectors = 1;
	pEraseInit.VoltageRange = VOLTAGE_RANGE_3;

	HAL_FLASHEx_Erase(&pEraseInit, (uint32_t*)&SectorError);
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
void FLASH_If_WriteWord(uint32_t FlashAddress, uint32_t size, uint8_t *Data)
{
  uint32_t i = 0;

  FLASH_If_Init();
  
  for (i = 0; i < size; i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (HAL_FLASH_Program(TYPEPROGRAM_BYTE, FlashAddress, Data[i]) == HAL_OK)      
    {
      /* Increment FLASH destination address */
      FlashAddress++;
    }
  }
}


void FLASH_If_ReadWord(uint32_t FlashAddress, uint32_t size, uint8_t *Data)
{
    uint32_t i;
    
    if(FLASH_WaitForLastOperation((uint32_t)50000) == HAL_OK)
    {
        for(i=0; i<size; i++)
        {
             Data[i] =  *(uint8_t*)(FlashAddress+i);
        }
    }
}    

/**
  * @brief  Gets the sector of a given address
  * @param  Address: Flash address
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_SECTOR_11;  
  }
  return sector;
}

/**
  * @brief  Configure the write protection status of user flash area.
  * @param  modifier DISABLE or ENABLE the protection
  * @retval HAL_StatusTypeDef HAL_OK if change is applied.
  */
HAL_StatusTypeDef FLASH_If_WriteProtectionConfig(uint32_t modifier)
{
  uint32_t ProtectedSECTOR = 0xFFF;
  FLASH_OBProgramInitTypeDef config_new, config_old;
  HAL_StatusTypeDef result = HAL_OK;
  
  /* Get pages write protection status ****************************************/
  HAL_FLASHEx_OBGetConfig(&config_old);

  /* The parameter says whether we turn the protection on or off */
  config_new.WRPState = modifier;

  /* We want to modify only the Write protection */
  config_new.OptionType = OPTIONBYTE_WRP;
  
  /* No read protection, keep BOR and reset settings */
  config_new.RDPLevel = OB_RDP_LEVEL_0;
  config_new.USERConfig = config_old.USERConfig;  
  /* Get pages already write protected ****************************************/
  ProtectedSECTOR = config_old.WRPSector | FLASH_SECTOR_TO_BE_PROTECTED;

  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();

  /* Unlock the Options Bytes *************************************************/
  HAL_FLASH_OB_Unlock();
  
  config_new.WRPSector    = ProtectedSECTOR;
  result = HAL_FLASHEx_OBProgram(&config_new);
  
  return result;
}

