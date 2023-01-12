#define __BL_PARAM_C__
    #include "SysParam.h"
#undef  __BL_PARAM_C__

#include "flash_if.h"

static void SysParam_FactorySet(void);

void SysParam_Read(void)
{
    FLASH_If_ReadWord(APP_PARAM_ADDR, sizeof(SysParam_t), (uint8_t*)&SysParam);
}

void SysParam_Save(void)
{
    FLASH_If_Erase(APP_PARAM_ADDR);
    FLASH_If_WriteWord(APP_PARAM_ADDR, sizeof(SysParam_t), (uint8_t*)&SysParam);
}

void SysParam_FactorySet(void)
{        
    memset((uint8_t*)&SysParam, 0, sizeof(SysParam_t));

    SysParam.Confirm = CONFIRM_PARAM;

    SysParam.buzzerUse = 0;
    SysParam.lcdOnTime = LCD_OFF_TIME_10_SEC;

    SysParam_Save();
}

void SysParam_Init()
{    
    SysParam_Read();

    if( SysParam.Confirm != CONFIRM_PARAM )
    {
        SysParam_FactorySet();
    } 
}
