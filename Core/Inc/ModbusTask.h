#ifndef __MODBUS_TASK_H__
#define __MODBUS_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "AppData.h"

void Modbus_Task_Init(void);

extern AppData_t AppData;
extern SysData_t SysData;

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

