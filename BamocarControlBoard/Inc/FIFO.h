//This library provides simple FIFO queue

#ifndef FIFO_
#define FIFO_

#include "can.h"

#define FIFO_MAX_LENGTH 8 //max length of fifo queue

typedef struct{
	CanTxMsgTypeDef * buf;
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}fifo;


//This initializes the FIFO structure with the given buffer and size
void fifo_init(fifo* f, uint8_t size);

//This reads nbytes bytes from the FIFO
//The number of bytes read is returned
void fifo_pop(fifo* f);

//This writes up to nbytes bytes to the FIFO
//If the head runs in to the tail, not all bytes are written
//The number of bytes written is returned
int8_t fifo_push(fifo* f, const CanTxMsgTypeDef* item);

CanTxMsgTypeDef* fifo_read(fifo* f);

uint8_t fifo_full(fifo* f);

uint8_t fifo_empty(fifo* f);

#endif //FIFO_
