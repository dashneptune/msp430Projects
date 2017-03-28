#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdint.h>

#define QUEUE_OV_ERROR			(1)
#define QUEUE_UN_ERROR			(-1)
#define QUEUE_SUCCESS			0
#define MAX_QUEUE_SIZE			50

struct queue_struct {
	uint8_t queue[MAX_QUEUE_SIZE];
	int8_t tail;
	int8_t head;
	uint8_t count;
	uint8_t maxsize;
	int8_t err;
};


void queue_init (struct queue_struct *queue);
uint8_t queue_getcount (struct queue_struct queue);
uint8_t queue_peek (struct queue_struct queue);
void queue_enqueue (struct queue_struct *queue, uint8_t data);
uint8_t queue_dequeue (struct queue_struct *queue);
uint8_t queue_getmaxsize (struct queue_struct queue);
uint8_t queue_isfull (struct queue_struct queue);
int8_t queue_geterr (struct queue_struct queue);
uint8_t queue_isempty (struct queue_struct queue);
void queue_flush_to_string (struct queue_struct *queue, uint8_t *string);

#endif
