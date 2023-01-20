#include "ModbusTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "modbus.h"
#include "modbusRTU.h"
#include "usart.h"

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

AppData_t AppData;
SysData_t SysData;

static uint8_t ModbusRTU_Buffer[MB_RTU_PACKET_SIZE_MAX];

static void Modbus_Task(void *argument);

static void RecvBufClear_wrapper(uint8_t idx);
static uint8_t CheckRecvEnd_wrapper(uint8_t idx);
static uint32_t GetRecvSize_wrapper (uint8_t idx);
static uint8_t ReadByte_wrapper(uint8_t idx);
static void WriteBytes_wrapper(uint8_t idx,uint8_t* data,uint16_t size);

void Modbus_Task_Init(void)
{
	ModbusTaskHandle = osThreadNew(Modbus_Task, NULL, &ModbusTask_attributes);
}

static void Modbus_Task(void *argument)
{
	ModbusSlave_Init();

    ModbusRtuSlave_RecvBufClear = RecvBufClear_wrapper;
    ModbusRtuSlave_CheckRecvEnd = CheckRecvEnd_wrapper;
    ModbusRtuSlave_GetRecvSize  = GetRecvSize_wrapper;
    ModbusRtuSlave_ReadByte     = ReadByte_wrapper;
    ModbusRtuSlave_WriteBytes   = WriteBytes_wrapper;

    ModbusRtuSlave_SetSlaveID(1);

	for(;;)
	{
		ModbusRtuSlave_Listen(0,ModbusRTU_Buffer);
		osDelay(1);
	}
}



static void RecvBufClear_wrapper(uint8_t idx)
{
	MX_USART2_ClearBuf();
}

static uint8_t CheckRecvEnd_wrapper(uint8_t idx)
{
	return !MX_USART2_GetRxBusyFlag();
}

static uint32_t GetRecvSize_wrapper (uint8_t idx)
{
	return MX_USART2_GetRxSize();
}

static uint8_t ReadByte_wrapper(uint8_t idx)
{
	return MX_USART2_GetByte();
}

static void WriteBytes_wrapper(uint8_t idx,uint8_t* data,uint16_t size)
{
	MX_USART2_WriteBytes(data,size);
}

