//This library provides simple FIFO queue

#ifndef FIFO_
#define FIFO_

#include "can.h"

#define FIFO_LENGTH 8 //max length of fifo queue

typedef struct{
	CanTxMsgTypeDef buf[FIFO_LENGTH];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}fifo;


//This initializes the FIFO structure with the given size
void fifo_init(fifo* f);

//Reads one element from fifo and deletes it
void fifo_pop(fifo* f, CanTxMsgTypeDef* p);

//This writes one item to the FIFO
//If the head runs in to the tail, item is discarded
uint8_t fifo_push(fifo* f, const CanTxMsgTypeDef* item);

//Checks whether fifo is full
uint8_t fifo_full(fifo* f);

//Checks whether fifo is empty
uint8_t fifo_empty(fifo* f);

#endif //FIFO_
