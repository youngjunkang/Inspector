#ifndef   __QUEUE_H__
#define   __QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __QUEUE_C__
	#define QUEUE_EXT
#else
	#define QUEUE_EXT extern
#endif

#define BUFF_SIZE 256

typedef struct Que_t
{
    uint8_t buff[BUFF_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t size;
}Que_t;

QUEUE_EXT void Que_Clear(Que_t* pQue);
QUEUE_EXT uint8_t Que_PutByte(Que_t* pQue, uint8_t data);
QUEUE_EXT uint8_t Que_GetByte(Que_t* pQue, uint8_t *data);
QUEUE_EXT uint32_t Que_GetSize(Que_t* pQue);

#ifdef __cplusplus
}
#endif

#endif

