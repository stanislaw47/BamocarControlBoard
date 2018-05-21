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


//This initializes the FIFO structure with the given size
void fifo_init(fifo* f, uint8_t size);

//Reads one element from fifo and deletes it
CanTxMsgTypeDef* fifo_pop(fifo* f);

//This writes one item to the FIFO
//If the head runs in to the tail, item is discarded
int8_t fifo_push(fifo* f, const CanTxMsgTypeDef* item);

//Checks whether fifo is full
uint8_t fifo_full(fifo* f);

//Checks whether fifo is empty
uint8_t fifo_empty(fifo* f);

#endif //FIFO_
