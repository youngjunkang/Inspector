#define __MODBUS_C__
    #include "modbus.h"
#undef  __MODBUS_C__

#include "AppData.h"
#include "modbusMap.h"

extern AppData_t AppData;

static uint8_t MakeExceptionPacket(uint8_t* buffer,uint8_t code);
static uint8_t ReadInputRegisters(uint8_t* buffer);
static uint8_t ReadHoldingRegisters(uint8_t* buffer);
static uint8_t WriteSingleRegister(uint8_t* buffer);
static uint8_t WriteMultipleRegisters(uint8_t* buffer);

static uint16_t HoldingReg[HOLDING_REG_COUNT];
//static uint16_t InputReg[INPUT_REG_COUNT];

void ModbusSlave_Init(void)
{
    ModbusSlave_UpdateInputRegister   = ModbusMap_UpdateInputRegister;
    ModbusSlave_UpdateHoldingRegister = ModbusMap_UpdateHoldingRegister;
    ModbusSlave_WriteHoldingRegister  = ModbusMap_WriteHoldingRegister;
}

uint8_t ModbusSlave_RequestProcessing(uint8_t *buffer)
{
    uint8_t txSize;
    
    switch(buffer[0])
    {
    case FuncCode_ReadInputRegisters     : txSize = ReadInputRegisters(buffer);     break;
    case FuncCode_ReadHoldingRegisters   : txSize = ReadHoldingRegisters(buffer);   break;
    case FuncCode_WriteSingleRegister    : txSize = WriteSingleRegister(buffer);    break; 
    case FuncCode_WriteMultipleRegisters : txSize = WriteMultipleRegisters(buffer); break;  
    default : break;  
    }
    
    return txSize;
}

static uint8_t ReadInputRegisters(uint8_t* buffer)
{
	return MakeExceptionPacket( buffer, ILLEGAL_FUNCTION);
/*
    uint8_t  fcode = buffer[0];
    uint16_t addr  = MAKEWORD(buffer[1], buffer[2]);
    uint16_t size  = MAKEWORD(buffer[3], buffer[4]);
    
    if(fcode != FuncCode_ReadInputRegisters)               
        return MakeExceptionPacket( buffer, ILLEGAL_FUNCTION);
    
    if(RANGE_CONTAIN(size,1,125) == false) 
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_VALUE);
    
    if( (RANGE_CONTAIN(addr     , INPUT_REG_BASE_ADDR_BASE, INPUT_REG_BASE_ADDR_END) == false) ||
        (RANGE_CONTAIN(addr+size, INPUT_REG_BASE_ADDR_BASE, INPUT_REG_BASE_ADDR_END) == false) )
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_ADDRESS);
    
    addr -= INPUT_REG_BASE_ADDR_BASE;
    
    ModbusSlave_UpdateInputRegister(InputReg);
    
    uint8_t idx = 1;
    uint8_t bc  = size*2;
    
    buffer[idx++] = bc;
    for(int i=0; i<size; i++)
    {
        buffer[idx++] = HIBYTE(InputReg[addr + i]);
        buffer[idx++] = LOBYTE(InputReg[addr + i]);
    }

    return idx;
    */
}

static uint8_t ReadHoldingRegisters(uint8_t* buffer)
{
    uint8_t  fcode = buffer[0];
    uint16_t addr  = MAKEWORD(buffer[1], buffer[2]);
    uint16_t size  = MAKEWORD(buffer[3], buffer[4]);
    
    if(fcode != FuncCode_ReadHoldingRegisters)               
        return MakeExceptionPacket( buffer, ILLEGAL_FUNCTION);
    
    if(RANGE_CONTAIN(size,1,125) == false) 
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_VALUE);
    
    if( (RANGE_CONTAIN(addr     , HOLDING_REG_BASE_ADDR_BASE, HOLDING_REG_BASE_ADDR_END) == false) ||
        (RANGE_CONTAIN(addr+size, HOLDING_REG_BASE_ADDR_BASE, HOLDING_REG_BASE_ADDR_END) == false) )
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_ADDRESS);
    
    addr -= HOLDING_REG_BASE_ADDR_BASE;

    ModbusSlave_UpdateHoldingRegister(HoldingReg);
    
    uint16_t idx = 1;
    uint8_t  bc = size*2;

    buffer[idx++] = bc;
    for(int i=0; i<size; i++)
    {
        buffer[idx++] = HIBYTE(HoldingReg[addr + i]);
        buffer[idx++] = LOBYTE(HoldingReg[addr + i]);
    }

    return idx;
}
     
static uint8_t WriteSingleRegister(uint8_t* buffer)
{
    uint8_t  fcode = buffer[0];
    uint16_t addr  = MAKEWORD(buffer[1], buffer[2]);

    if(fcode != FuncCode_WriteSingleRegister)               
        return MakeExceptionPacket( buffer, ILLEGAL_FUNCTION);
    
    if( RANGE_CONTAIN(addr, HOLDING_REG_BASE_ADDR_BASE, HOLDING_REG_BASE_ADDR_END) == false )
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_ADDRESS);
    
    addr -= HOLDING_REG_BASE_ADDR_BASE;

    HoldingReg[addr] = MAKEWORD(buffer[3] ,buffer[4]);
    
    if(ModbusSlave_WriteHoldingRegister(HoldingReg,addr) == false)
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_VALUE);
    
    return 5;
}

static uint8_t WriteMultipleRegisters(uint8_t* buffer)
{
    uint8_t  fcode = buffer[0];
    uint16_t addr  = MAKEWORD(buffer[1], buffer[2]);
    uint16_t size  = MAKEWORD(buffer[3], buffer[4]);
    uint8_t  bc    = buffer[5];

    if(fcode != FuncCode_WriteMultipleRegisters)               
        return MakeExceptionPacket( buffer, ILLEGAL_FUNCTION);
    
    if( (RANGE_CONTAIN(size,1,123) == false) ||
        (bc != (size*2)) ) 
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_VALUE);
    
    if( (RANGE_CONTAIN(addr     , HOLDING_REG_BASE_ADDR_BASE, HOLDING_REG_BASE_ADDR_END) == false) ||
        (RANGE_CONTAIN(addr+size, HOLDING_REG_BASE_ADDR_BASE, HOLDING_REG_BASE_ADDR_END) == false) )
        return MakeExceptionPacket( buffer, ILLEGAL_DATA_ADDRESS);
    
    addr -= HOLDING_REG_BASE_ADDR_BASE;
    
    for(int i=0; i<size; i++)
    {
        HoldingReg[addr+i] = MAKEWORD(buffer[6+i*2] ,buffer[7+i*2]);
    }
    
    for(int i=addr; i < addr+size; i++)
    {
        if(ModbusSlave_WriteHoldingRegister(HoldingReg,addr) == false)
            return MakeExceptionPacket( buffer, ILLEGAL_DATA_VALUE);
    }

    return 5;
}

static uint8_t MakeExceptionPacket(uint8_t* buffer,uint8_t exCode)
{
    uint8_t idx = 0;

    buffer[idx++] |= 0x80;
    buffer[idx++] = exCode;

    return idx;
}     

