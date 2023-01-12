#ifndef __FLASH_IF_H
#define __FLASH_IF_H

#include "main.h"

#ifdef __FLASH_IF_C
	#define FLASH_IF_EXT
#else
	#define FLASH_IF_EXT extern
#endif
/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */

/* Define bitmap representing user flash area that could be write protected (check restricted to pages 8-39). */
#define FLASH_SECTOR_TO_BE_PROTECTED (OB_WRP_SECTOR_0 | OB_WRP_SECTOR_1 | OB_WRP_SECTOR_2 | OB_WRP_SECTOR_3 |\
                                      OB_WRP_SECTOR_4 | OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7)

#define APP_PARAM_ADDR        ADDR_FLASH_SECTOR_11

#define APP_FLASH_ADDR        ADDR_FLASH_SECTOR_0
#define END_FLASH_ADDR        ((uint32_t)0x080FFFFF)

#define CONFIRM_PARAM ((uint32_t)0x6ABCD124)

FLASH_IF_EXT void FLASH_If_Erase(uint32_t addr);
FLASH_IF_EXT void FLASH_If_WriteWord(uint32_t FlashAddress, uint32_t size, uint8_t *Data);
FLASH_IF_EXT void FLASH_If_ReadWord(uint32_t FlashAddress, uint32_t size, uint8_t *Data);
FLASH_IF_EXT HAL_StatusTypeDef FLASH_If_WriteProtectionConfig(uint32_t modifier);


#endif  
