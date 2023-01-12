#define __QUEUE_C__
    #include "Que.h"
#undef  __QUEUE_C__


void Que_Clear(Que_t* pQue)
{
    pQue->head = pQue->tail = pQue->size = 0;
    memset(pQue->buff,0,BUFF_SIZE);
}

uint8_t Que_PutByte(Que_t* pQue, uint8_t data)
{
    if(Que_GetSize(pQue) == (BUFF_SIZE-1)) 
      return FALSE;
    pQue->buff[pQue->head++] =data;
    pQue->head %= BUFF_SIZE;
    
    pQue->size = Que_GetSize(pQue);
    return TRUE;
}

uint8_t Que_GetByte(Que_t* pQue, uint8_t *data)
{
    if(Que_GetSize(pQue) == 0) 
      return FALSE;
    *data = pQue->buff[pQue->tail++];
    pQue->tail %= BUFF_SIZE;
    
    pQue->size = Que_GetSize(pQue);
    return TRUE;
}

uint32_t Que_GetSize(Que_t* pQue)
{
    return (pQue->head - pQue->tail  + BUFF_SIZE) % BUFF_SIZE;
}


