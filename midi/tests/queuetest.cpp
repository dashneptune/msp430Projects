#include "CppUTest/TestHarness.h"

extern "C"
{
	//#include <stdint.h>
	#include "queue.h"
}

void overflow_queue (struct queue_struct *queue){
	uint8_t ctr = 0;
	do {
		queue_enqueue (queue, ctr);
		ctr++;
	}while ((ctr-4) <= queue_getmaxsize (*queue));
}


static struct queue_struct global_queue;

TEST_GROUP (queue)
{
	void setup ()
	{
		queue_init (&global_queue);
	}
	void teardown ()
	{
		while (!queue_isempty (global_queue)){
			queue_dequeue (&global_queue);
		}
	}
	void expect ()
	{
	}
	void given ()
	{
	}
};

TEST(queue, isemptyoninit){
	CHECK_EQUAL(0,queue_getcount (global_queue));
}

TEST(queue, takeseightbit){
	uint8_t data = 0xFE;
	queue_enqueue (&global_queue,data);
	CHECK_EQUAL (data,queue_peek(global_queue));
}

TEST (queue, returnseightbit){
	uint8_t data = 0xFF;
	queue_enqueue (&global_queue, data);
	CHECK_EQUAL(data,queue_dequeue (&global_queue));
}

TEST (queue, isfifo){
	uint8_t data1, data2;
	data1 = 0;
	data2 = 0xff;
	queue_enqueue (&global_queue, data1);
	queue_enqueue (&global_queue, data2);
	CHECK_EQUAL (data1, queue_dequeue(&global_queue));
	CHECK_EQUAL (data2, queue_dequeue(&global_queue));
}

TEST (queue, morethanonecopy){
	struct queue_struct queue;
	uint8_t data1, data2;
	data1 = 0x00;
	data2 = 0xff;
	queue_init (&queue);
	queue_enqueue (&global_queue, data1);
	queue_enqueue (&queue, data2);
	CHECK_EQUAL (data1,queue_dequeue (&global_queue));
	CHECK_EQUAL (data2, queue_dequeue (&queue));
}

TEST (queue, canreturncount){
	uint8_t size = 30;
	uint8_t i = 0;
	do {
		queue_enqueue(&global_queue, i);
		i++;
		CHECK_EQUAL(i,queue_getcount(global_queue));
	}while (i < size);
}

TEST (queue, wontoverflow){
	overflow_queue (&global_queue);
	CHECK_EQUAL (queue_getmaxsize (global_queue), queue_getcount(global_queue));
}

TEST (queue, notifiescallerofoverflow){
	overflow_queue (&global_queue);
	CHECK_EQUAL (QUEUE_OV_ERROR, queue_geterr (global_queue));
}

TEST (queue, wontunderflow){
	queue_dequeue (&global_queue);
	CHECK_EQUAL (0, queue_getcount(global_queue));
}

TEST (queue, notifiescallerofunderflow){
	queue_dequeue (&global_queue);
	CHECK_EQUAL (QUEUE_UN_ERROR, queue_geterr (global_queue));
}

TEST (queue, clearserrstatusonsuccess){
	queue_dequeue (&global_queue);
	queue_enqueue (&global_queue, 25);
	CHECK_EQUAL (QUEUE_SUCCESS, queue_geterr(global_queue));
	overflow_queue (&global_queue);
	queue_dequeue (&global_queue);
	CHECK_EQUAL (QUEUE_SUCCESS, queue_geterr(global_queue));
}

