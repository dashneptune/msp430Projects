#include "queue.h"


void queue_init (struct queue_struct *queue){
	queue->head = 0;
	queue->tail = -1;
	queue->count = 0;
	queue->maxsize = MAX_QUEUE_SIZE;
	queue->err = QUEUE_SUCCESS;
}

uint8_t queue_isempty (struct queue_struct queue){
	return (queue.count == 0);
}

uint8_t queue_isfull (struct queue_struct queue){
	return (queue.count == queue.maxsize);
}

uint8_t queue_getcount (struct queue_struct queue){
	return (queue.count);
}

uint8_t queue_peek (struct queue_struct queue){
	return (queue.queue[queue.head]);
}

void queue_enqueue (struct queue_struct *queue, uint8_t data){
	if (!queue_isfull (*queue)){	
		queue->queue[++queue->tail]= data;
		queue->count++;
		queue->err = QUEUE_SUCCESS;
	}else {
		queue->err = QUEUE_OV_ERROR;
	}
}

uint8_t queue_dequeue (struct queue_struct *queue){
	if (!queue_isempty (*queue)){
		uint8_t data = queue->queue[queue->head++];
		if (queue->head == queue->maxsize){
			queue->head = 0;
		}
		queue->count--;
		queue->err = QUEUE_SUCCESS;
		return (data);
	} else {
		queue->err = QUEUE_UN_ERROR;
		return (0);
	}
}



uint8_t queue_getmaxsize (struct queue_struct queue){
	return (queue.maxsize);
}

int8_t queue_geterr (struct queue_struct queue){
	return (queue.err);
}

void queue_flush_to_string (struct queue_struct *queue, uint8_t *string){
  uint16_t ctr = 0;
  while (!queue_isempty (*queue)){
    string[ctr++] = queue_dequeue (queue);
  }
  string[ctr] = '\0';
}
