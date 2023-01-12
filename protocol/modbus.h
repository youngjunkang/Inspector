#ifndef   __MODBUS_H__
#define   __MODBUS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __MODBUS_C__
	#define MODBUS_EXT
#else
	#define MODBUS_EXT extern
#endif

typedef struct ModbusMaster_t
{
	void (*WriteBytes)(uint8_t*,uint8_t);
	uint8_t (*readByte)(void);
	uint8_t (*isRxBusy)(void);
	uint8_t (*getSize)(void);
}ModbusMaster_t;

MODBUS_EXT ModbusMaster_t ModbusMaster;

MODBUS_EXT uint8_t MODBUS_Master_Init(void);
MODBUS_EXT uint8_t MODBUS_Master_ReadHodingRegisters(uint16_t id, uint16_t addr, uint16_t *data,uint8_t size);
MODBUS_EXT uint8_t MODBUS_Master_WriteMultipleRegisters(uint16_t id, uint16_t addr, uint16_t* data, uint8_t size);
MODBUS_EXT uint8_t MODBUS_Master_ReadHoldingRegistersOverSize(uint16_t id, uint16_t addr, uint16_t *data,uint16_t size);
#ifdef __cplusplus
}
#endif

#endif
