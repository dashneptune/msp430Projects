#include <msp430.h>
#include "pins.h"
#include "watchdog.h"
#include "board.h"
#include "usci.h"
#include "arrayhandlers.h"

#define NOTE_ON		0x90
#define NOTE_OFF	0x80

#define NUMBER_OF_CHANNELS	8

void sensechannels (uint8_t *array, uint8_t numberofchannels);
void send_messages (int8_t *diffptr, uint8_t length, uint8_t velocity);


void main (void){
	uint8_t currentarray[NUMBER_OF_CHANNELS];	// array to hold newest read of states
	uint8_t lastarray[NUMBER_OF_CHANNELS];
	// array to hold last read of states
	int8_t diffarray[NUMBER_OF_CHANNELS];
	// array to hold the difference of states between last and current read
	uint8_t numberofmessages;	// number of messages
	uint8_t velocity = 127;		// velocity to send over MIDI
	stop_watchdog ();		// stop the watchdog timer
	// zero the arrays
	zeroarray_unsigned (currentarray, NUMBER_OF_CHANNELS);
	zeroarray_unsigned (lastarray, NUMBER_OF_CHANNELS);
	zeroarray_signed (diffarray, NUMBER_OF_CHANNELS);
	device_init ();			// initialize the device (in board.c)
	__enable_interrupt ();		// enable interrupts
	while (1){			// the big forever loop in the sky
	uint8_t message[3] = {0xAA, 0xAA, 0xAA};
	send_data (message,3);
/*
		sensechannels (currentarray, NUMBER_OF_CHANNELS);
		// get the current state of all of the channels
		numberofmessages = filldiffarray (currentarray, NUMBER_OF_CHANNELS, lastarray, diffarray);
		// get the difference between the current and last iterations
		if (numberofmessages >0){
			send_messages (diffarray, NUMBER_OF_CHANNELS, velocity);
		}
		// if the number of messages is greatre than 0, send messages over midi
		copyarray (currentarray, NUMBER_OF_CHANNELS, lastarray);
		// copy the current state array to the last one
*/
	}
}

void send_messages (int8_t *array, uint8_t length, uint8_t velocity){
	uint8_t ctr;
	uint8_t messagearray[3] = {NOTE_ON, 0, 0};
	for (ctr = 0; ctr < length; ctr++){
		if (*(array+ctr) != 0){
			if (*(array+ctr) > 0){
				messagearray[2] = velocity;
			} else if (*(array+ctr) < 0){
				messagearray[2] = 0;
			}
			messagearray[1] = ctr;
			send_data (messagearray, 3);
		}
	}
}

void sensechannels (uint8_t *array, uint8_t numberofchannels){
	uint8_t ctr;
	uint8_t mask = 0x01;
	for (ctr = 0; ctr < numberofchannels;ctr++ ){
		P2OUT = mask;
		*(array + ctr) = ((P2IN & mask) == 0);
		mask <<= 1;
	}
}
