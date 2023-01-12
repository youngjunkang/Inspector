#ifndef   __BL_PARAM_H__
#define   __BL_PARAM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "flash_if.h"

#ifdef __BL_PARAM_C__
	#define BL_PARAM_EXT
#else
	#define BL_PARAM_EXT extern
#endif

#pragma pack(push,1)

typedef enum
{
	LCD_OFF_TIME_10_SEC = 0,
	LCD_OFF_TIME_30_SEC,
	LCD_OFF_TIME_1_MIN,
	LCD_OFF_TIME_5_MIN,
	LCD_OFF_TIME_30_MIN,
	LCD_OFF_TIME_1_HOUR,
	LCD_OFF_TIME_ALWAYS,
}ELcdOffTime;

typedef struct SysParam_t
{
	uint32_t    Confirm;
	uint8_t     buzzerUse;
	uint8_t     lcdOnTime; //sec
}SysParam_t;
#pragma pack(pop)

BL_PARAM_EXT   SysParam_t   SysParam;

BL_PARAM_EXT void SysParam_Init(void);
BL_PARAM_EXT void SysParam_Save(void);
BL_PARAM_EXT void SysParam_Read(void);

#ifdef __cplusplus
}
#endif

#endif
