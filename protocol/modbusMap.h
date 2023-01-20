#ifndef   __MODBUS_MAP_H__
#define   __MODBUS_MAP_H__

#include "main.h"

#ifdef __MODBUS_MAP_C__
	#define MODBUS_MAP_EXT
#else
	#define MODBUS_MAP_EXT extern
#endif


MODBUS_MAP_EXT void ModbusMap_UpdateInputRegister  (uint16_t *buffer);
MODBUS_MAP_EXT void ModbusMap_UpdateHoldingRegister(uint16_t *buffer);
MODBUS_MAP_EXT uint8_t   ModbusMap_WriteHoldingRegister (uint16_t *buffer,uint16_t addr);

#endif

