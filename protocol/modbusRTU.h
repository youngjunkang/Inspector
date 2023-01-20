#ifndef   __MODBUS_RTU_H__
#define   __MODBUS_RTU_H__

#include "main.h"
#include "modbus.h"

#ifdef __MODBUS_RTU_C__
	#define MODBUS_RTU_EXT
#else
	#define MODBUS_RTU_EXT extern
#endif

#define MB_RTU_PACKET_SIZE_MIN      (8)
#define MB_RTU_PACKET_SIZE_MAX      (256)

MODBUS_RTU_EXT uint32_t ModbusRtuSlaveOkCount;

MODBUS_RTU_EXT void ModbusRtuSlave_Listen(uint8_t idx,uint8_t* buffer);
MODBUS_RTU_EXT void ModbusRtuSlave_SetSlaveID(uint8_t id);

MODBUS_RTU_EXT void (*ModbusRtuSlave_RecvBufClear)(uint8_t idx);
MODBUS_RTU_EXT uint8_t   (*ModbusRtuSlave_CheckRecvEnd)(uint8_t idx);
MODBUS_RTU_EXT uint32_t  (*ModbusRtuSlave_GetRecvSize) (uint8_t idx);
MODBUS_RTU_EXT uint8_t   (*ModbusRtuSlave_ReadByte)    (uint8_t idx);
MODBUS_RTU_EXT void (*ModbusRtuSlave_WriteBytes)  (uint8_t idx,uint8_t* data,uint16_t size);

#endif
