#ifndef   __APP_DATA_H__
#define   __APP_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __APP_DATA_C__
	#define APP_DATA_EXT
#else
	#define APP_DATA_EXT extern
#endif

#pragma pack(push,1)

typedef struct AppSystemInfo_t
{
	uint8_t serialNum[14];
	uint8_t modelName[14];
	uint8_t adminName[14];
	uint8_t groupName[14];
}AppSystemInfo_t;

typedef struct AppUtilRate_t
{
	uint16_t cpuUsage;
	uint16_t memoryUsage;
	uint16_t diskUsage;
	uint16_t totalCpu;
	float	 totalMemory;
}AppUtilRate_t;

typedef struct AppNetworkVal_t
{
	uint8_t name[14];
	uint8_t ip[18];
}AppNetworkVal_t;

typedef struct AppNetworkInfo_t
{
	uint16_t itemCount;
	AppNetworkVal_t net[8];
}AppNetworkInfo_t;

typedef struct AppStorageVal_t
{
	uint8_t name[8];
	uint16_t usage;
}AppStorageVal_t;

typedef struct AppStorageInfo_t
{
	uint16_t itemCount;
	AppStorageVal_t drive[6];
}AppStorageInfo_t;

typedef struct AppProcessVal_t
{
	uint8_t name[14];
	uint16_t usage;
}AppProcessVal_t;

typedef struct AppProcessInfo_t
{
	uint16_t itemCount;
	uint16_t cpuUsage;
	AppProcessVal_t val[8];
}AppProcessInfo_t;

typedef struct AppData_t
{
	AppSystemInfo_t sysInfo;
	AppUtilRate_t utilRate;
	AppNetworkInfo_t netInfo;
	AppStorageInfo_t storage;
	AppProcessInfo_t process;
}AppData_t;

/******************************************************************/

typedef struct SysData_t
{
	uint32_t okCount[5];
	uint32_t errCount[5];
	uint32_t sysTime;
	uint8_t  sysVer[10];
}SysData_t;

typedef enum GuiEventType_t
{
	GUI_EVENT_SAVE_PARAM = 1,
	GUI_EVENT_SET_BUZZER_USE,
	GUI_EVENT_SET_LCD_ON_TIME
}GuiEventType_t;

typedef struct GuiMessage_t
{
	GuiEventType_t eventType;
	uint32_t 	   data;
}GuiMessage_t;
#pragma pack(pop)


#ifdef __cplusplus
}
#endif

#endif
