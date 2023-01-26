#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <string.h>

#include "cmsis_os2.h"
#include "ModbusTask.h"
#include "SysParam.h"

extern osMessageQueueId_t GuiTaskMBoxHandle;

static void CheckDataRange(void);

static AppData_t AppDataAlias;

static AppSystemInfo_t *sysInfo;
static AppUtilRate_t *utilRate;
static AppNetworkInfo_t *netInfo;
static AppStorageInfo_t *storage;
static AppProcessInfo_t *process;

Model::Model() : modelListener(0)
{
	sysInfo  = &AppDataAlias.sysInfo;
	utilRate = &AppDataAlias.utilRate;
	netInfo  = &AppDataAlias.netInfo;
	storage  = &AppDataAlias.storage;
	process  = &AppDataAlias.process;

	buzzerUse = SysParam.buzzerUse;
	lcdOnTime = SysParam.lcdOnTime;
}

void Model::tick()
{
	if(osMessageQueueGetCount(GuiTaskMBoxHandle)>0)
	{
		GuiMessage_t msg;
		osMessageQueueGet(GuiTaskMBoxHandle,&msg,NULL,0);
		switch(msg.eventType)
		{
		case GUI_EVENT_SAVE_PARAM :
			SysParam.buzzerUse = buzzerUse;
			SysParam.lcdOnTime = lcdOnTime;
			SysParam_Save();
			break;
		}
	}

	memcpy(&AppDataAlias,&AppData,sizeof(AppData_t));
	CheckDataRange();

	modelListener->info_SetDeviceSerialNum((char*)sysInfo->serialNum);
	modelListener->info_SetDeviceModelName((char*)sysInfo->modelName);
	modelListener->info_SetDeviceAdminName((char*)sysInfo->adminName);
	modelListener->info_SetDeviceGroup((char*)sysInfo->groupName);

	modelListener->UtilRate_SetCpuUsage(utilRate->cpuUsage);
	modelListener->UtilRate_SetMemoryUsage(utilRate->memoryUsage);
	modelListener->UtilRate_SetDiskUsage(utilRate->diskUsage);
	modelListener->UtilRate_SetTotalCpuCore(utilRate->totalCpu);
	modelListener->UtilRate_SetTotalMemory((char*)utilRate->totalMemory);

	modelListener->Network_SetListMax(netInfo->itemCount);
	for(char i=0; i<netInfo->itemCount; i++)
		modelListener->Network_SetListData(i,
			    (char*)netInfo->net[i].name,
			    (char*)netInfo->net[i].ip);

	modelListener->Storage_SetListMax(storage->itemCount);
	for(char i=0; i<storage->itemCount; i++)
		modelListener->Storage_SetListInfo(i,
				(char*)storage->drive[i].name,
				storage->drive[i].usage);

	modelListener->Process_SetListMax(process->itemCount);
	modelListener->Process_SetCpuUsage(process->cpuUsage);
	for(char i=0; i<process->itemCount; i++)
		modelListener->Process_SetListInfo(i,
				(char*)process->val[i].name,
				process->val[i].usage);
}

static void CheckDataRange(void)
{
	sysInfo->serialNum[13] = 0;
	sysInfo->modelName[13] = 0;
	sysInfo->adminName[13] = 0;
	sysInfo->groupName[13] = 0;

	if(utilRate->cpuUsage > 100) 	utilRate->cpuUsage = 100;
	if(utilRate->memoryUsage > 100) utilRate->memoryUsage = 100;
	if(utilRate->diskUsage > 100) 	utilRate->diskUsage = 100;
	if(utilRate->totalCpu > 99) 	utilRate->totalCpu = 99;
	utilRate->totalMemory[4] = 0;

	if(netInfo->itemCount > 8) netInfo->itemCount = 8;
	for(char i=0; i<netInfo->itemCount; i++)
	{
		netInfo->net[i].name[13] = 0;
		netInfo->net[i].ip[17]   = 0;
	}

	if(storage->itemCount > 6) storage->itemCount = 6;
	for(char i=0; i<storage->itemCount; i++)
	{
		storage->drive[i].name[7] = 0;
		if(storage->drive[i].usage > 100)
			storage->drive[i].usage = 100;
	}

	if(process->itemCount > 8) process->itemCount = 8;
	if(process->cpuUsage > 100) process->cpuUsage = 100;
	for(char i=0; i<process->itemCount; i++)
	{
		process->val[i].name[13] = 0;
		if(process->val[i].usage > 100)
			process->val[i].usage = 100;
	}
}

