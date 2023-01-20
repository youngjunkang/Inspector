#ifndef   __MODBUS_H__
#define   __MODBUS_H__

#include "main.h"

#ifdef __MODBUS_C__
	#define MODBUS_EXT
#else
	#define MODBUS_EXT extern
#endif

#define MODBUS_PDU_SIZE         (253)

#define INPUT_REG_COUNT    (1)
#define HOLDING_REG_COUNT  (6000)

#define INPUT_REG_BASE_ADDR_BASE    (30001)
#define INPUT_REG_BASE_ADDR_END     (INPUT_REG_BASE_ADDR_BASE + INPUT_REG_COUNT)

#define HOLDING_REG_BASE_ADDR_BASE  (0)
#define HOLDING_REG_BASE_ADDR_END   (HOLDING_REG_BASE_ADDR_BASE + HOLDING_REG_COUNT)

typedef enum FuncCode_t
{
FuncCode_ReadDiscreteInputs         = 2,
FuncCode_ReadCoils                  = 1,
FuncCode_WriteSingleCoil            = 5,
FuncCode_WriteMultipleCoils         = 15,
FuncCode_ReadInputRegisters         = 4,
FuncCode_ReadHoldingRegisters       = 3,
FuncCode_WriteSingleRegister        = 6,
FuncCode_WriteMultipleRegisters     = 16,
FuncCode_ReadWriteMultipleRegisters = 23,
}FuncCode_t;

typedef enum ExceptionCode_t
{
ILLEGAL_FUNCTION = 1,
ILLEGAL_DATA_ADDRESS = 2,
ILLEGAL_DATA_VALUE = 3,
SLAVE_DEVICE_FAILURE = 4,
ACKNOWLEDGE = 5,
SLAVE_DEVICE_BUSY = 6,
MEMORY_PARITY_ERROR = 8,
GATEWAY_PATH_UNAVAILABLE = 0x0A,
GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND = 0x0B,
}ExceptionCode_t;

MODBUS_EXT void ModbusSlave_Init(void);
MODBUS_EXT uint8_t ModbusSlave_RequestProcessing(uint8_t *buffer);

MODBUS_EXT void (*ModbusSlave_UpdateInputRegister)  (uint16_t *buffer);
MODBUS_EXT void (*ModbusSlave_UpdateHoldingRegister)(uint16_t *buffer);
MODBUS_EXT uint8_t   (*ModbusSlave_WriteHoldingRegister) (uint16_t *buffer,uint16_t addr);
#endif
