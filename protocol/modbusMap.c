#define __MODBUS_MAP_C__
    #include "modbusMap.h"
#undef  __MODBUS_MAP_C__

#include "AppData.h"
#include "modbus.h"

typedef enum InputRegAddr_t
{
    INPUT_REG_ = 0,
}InputRegAddr_t;

typedef enum HoldingRegAddr_t
{
    HOLDING_REG_ = 0,
}HoldingRegAddr_t;

extern AppData_t AppData;

void ModbusMap_UpdateInputRegister(uint16_t *buffer)
{
//    buffer[INPUT_REG_] = xxxx;     
}

void ModbusMap_UpdateHoldingRegister(uint16_t *buffer)
{
//    buffer[HOLDING_REG_] = xxxx;  
}

uint8_t ModbusMap_WriteHoldingRegister(uint16_t *buffer,uint16_t addr)
{
    uint8_t exCode = false;

    if(RANGE_CONTAIN(addr,HOLDING_REG_BASE_ADDR_BASE,HOLDING_REG_BASE_ADDR_END))
    {
    	exCode = true;

    	AppData.word[addr] = buffer[addr];
    }

    return exCode;
}

