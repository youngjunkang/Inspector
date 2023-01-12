#include "ModbusTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "modbus.h"


#define MODBUS_ID	(1)

enum{
	INFO = 0,
	UTIL_RATE,
	NETWORK,
	STORAGE,
	PROCESS,
};

enum{
	MODBUS_BASE_ADDR_INFO       = 1000,
	MODBUS_BASE_ADDR_UTIL_RATE  = 2000,
	MODBUS_BASE_ADDR_NETWORK    = 3000,
	MODBUS_BASE_ADDR_STORAGE    = 4000,
	MODBUS_BASE_ADDR_PROCESS    = 5000,
};

osThreadId_t ModbusTaskHandle;
const osThreadAttr_t ModbusTask_attributes = {
  .name = "modbusTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void ReadSysInfo(void);
static void ReadUtilRate(void);
static void ReadNetInfo(void);
static void ReadStorage(void);
static void ReadProcess(void);

AppData_t AppData;
SysData_t SysData;

static void Modbus_Task(void *argument);

void Modbus_Task_Init(void)
{
	ModbusTaskHandle = osThreadNew(Modbus_Task, NULL, &ModbusTask_attributes);
}

static void Modbus_Task(void *argument)
{
	MODBUS_Master_Init();

	for(;;)
	{
		ReadSysInfo();
		ReadUtilRate();
		ReadNetInfo();
		ReadStorage();
		ReadProcess();
		osDelay(10);
	}
}

static void ReadSysInfo(void)
{
	uint8_t res;
	AppSystemInfo_t sysInfo;

	res = MODBUS_Master_ReadHoldingRegistersOverSize(MODBUS_ID,MODBUS_BASE_ADDR_INFO,&sysInfo,sizeof(AppSystemInfo_t)/2);
	if(res)
	{
		SysData.okCount[INFO]++;
		memcpy(&AppData.sysInfo,&sysInfo,sizeof(AppSystemInfo_t));
	}
	else    SysData.errCount[INFO]++;
}

static void ReadUtilRate(void)
{
	uint8_t res;
	AppUtilRate_t utilRate;

	res = MODBUS_Master_ReadHoldingRegistersOverSize(MODBUS_ID,MODBUS_BASE_ADDR_UTIL_RATE,&utilRate,sizeof(AppUtilRate_t)/2);
	if(res)
	{
		SysData.okCount[UTIL_RATE]++;
		memcpy(&AppData.utilRate,&utilRate,sizeof(AppUtilRate_t));
	}
	else    SysData.errCount[UTIL_RATE]++;
}

static void ReadNetInfo(void)
{
	uint8_t res;
	AppNetworkInfo_t netInfo;

	res = MODBUS_Master_ReadHodingRegisters(MODBUS_ID,MODBUS_BASE_ADDR_NETWORK,&netInfo.itemCount,1);
	if(res)
	{
		SysData.okCount[NETWORK]++;
		AppData.netInfo.itemCount = netInfo.itemCount;

		if(AppData.netInfo.itemCount > 8)
			AppData.netInfo.itemCount = 8;

		if(AppData.netInfo.itemCount > 0)
		{
			res = MODBUS_Master_ReadHoldingRegistersOverSize(MODBUS_ID,MODBUS_BASE_ADDR_NETWORK+1,netInfo.net,sizeof(AppNetworkVal_t)/2*AppData.netInfo.itemCount);
			if(res)
			{
				SysData.okCount[NETWORK]++;
				memcpy(AppData.netInfo.net,netInfo.net,sizeof(AppNetworkVal_t)*AppData.netInfo.itemCount);
			}
			else    SysData.errCount[NETWORK]++;
		}
	}
	else
		SysData.errCount[NETWORK]++;
}

static void ReadStorage(void)
{
	uint8_t res;
	AppStorageInfo_t storage;

	res = MODBUS_Master_ReadHodingRegisters(MODBUS_ID,MODBUS_BASE_ADDR_STORAGE,&storage.itemCount,1);
	if(res)
	{
		SysData.okCount[STORAGE]++;
		AppData.storage.itemCount = storage.itemCount;

		if(AppData.storage.itemCount > 6)
			AppData.storage.itemCount = 6;

		if(AppData.storage.itemCount > 0)
		{
			res = MODBUS_Master_ReadHoldingRegistersOverSize(MODBUS_ID,MODBUS_BASE_ADDR_STORAGE+1,storage.drive,sizeof(AppStorageVal_t)/2*AppData.storage.itemCount);
			if(res)
			{
				SysData.okCount[STORAGE]++;
				memcpy(AppData.storage.drive,&storage.drive,sizeof(AppStorageVal_t)*AppData.storage.itemCount);
			}
			else    SysData.errCount[STORAGE]++;
		}
	}
	else
		SysData.errCount[STORAGE]++;
}

static void ReadProcess(void)
{
	uint8_t res;
	AppProcessInfo_t process;

	res = MODBUS_Master_ReadHodingRegisters(MODBUS_ID,MODBUS_BASE_ADDR_PROCESS,&process.itemCount,2);
	if(res)
	{
		SysData.okCount[PROCESS]++;
		AppData.process.itemCount = process.itemCount;
		AppData.process.cpuUsage = process.cpuUsage;

		if(AppData.process.itemCount > 8)
			AppData.process.itemCount = 8;

		if(AppData.process.itemCount > 0)
		{
			res = MODBUS_Master_ReadHoldingRegistersOverSize(MODBUS_ID,MODBUS_BASE_ADDR_PROCESS+2,process.val,sizeof(AppProcessVal_t)/2*AppData.process.itemCount);
			if(res)
			{
				SysData.okCount[PROCESS]++;
				memcpy(AppData.process.val,process.val,sizeof(AppProcessVal_t)*AppData.process.itemCount);
			}
			else    SysData.errCount[PROCESS]++;
		}
	}
	else
		SysData.errCount[PROCESS]++;
}
