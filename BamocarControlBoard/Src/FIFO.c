#include "FIFO.h"


void fifo_init(fifo* f, uint8_t size){
     f->head = 0;
     f->tail = 0;
     if (size > FIFO_MAX_LENGTH) f->size = FIFO_MAX_LENGTH;
     else f->size = size;
}

int8_t fifo_push(fifo* f, const CanTxMsgTypeDef* item){
	//first check to see if there is space in the buffer
	if(fifo_full(f))
		 return -1; //no more room
	else {
	   f->buf[f->head] = *item;
	   f->head++;  //increment the head
	   if( f->head == f->size ){  //check for wrap-around
			f->head = 0;
	   }
	}
	return 0;
}

void fifo_pop(fifo* f){
	if(fifo_empty(f)){ //see if any data is available
		f->tail++;  //increment the tail
		if( f->tail == f->size )  //check for wrap-around
			f->tail = 0;
	}
}

CanTxMsgTypeDef* fifo_read(fifo* f){
	CanTxMsgTypeDef* p;
	if(fifo_empty(f)){ //see if any data is available
		*p = f->buf[f->tail];  //grab a byte from the buffer
		return p;
	}
	else
		return NULL;
}

uint8_t fifo_full(fifo* f){
	return (f->head + 1 == f->tail) || ((f->head + 1 == f->size) && (f->tail ==0));
}

uint8_t fifo_empty(fifo* f){
	return f->tail != f->head;
}

