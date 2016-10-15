//
// Author: marc olberding
// File : main.c
// project: organ
// date 9/30/15
// Runs on the msp430G2553. Senses binary swicthes from a CD4051 multiplexer. could be replaced with a non analog version in the future
// Relays the information via MIDI
//

// includes
#include <msp430.h>
#include "pins.h"
#include "watchdog.h"	// holds members for accessing the watchdog timer
#include "multiplexor.h"	// holds interface for mutliplexor access
#include "board.h"	// holds configuration specific intialization
#include "usci.h"	// Holds interface for sending UART messages
#include "arrayhandlers.h"
#include "midi.h"

void sensechannels (uint8_t *array, uint8_t numberofchannels, struct multiplexordriver_struct *mult);
void send_messages (int8_t *diffptr, uint8_t length, uint8_t velocity);

int main (void){
	struct portdriver_struct p2;	// a port driver struct that gives multiplexor struct access to port 2
	struct multiplexordriver_struct mult;	// a multiplexor driver that gives access to the pins controlling the multiplexor input
	uint8_t currentarray[NUMBER_OF_CHANNELS];	// holds the state of all of the pins on the multiplexor
	uint8_t lastarray[NUMBER_OF_CHANNELS];		// holds the last state of all of the pins on the multiplexor
	int8_t diffarray[NUMBER_OF_CHANNELS];		// holds which states are different since the last sense
	uint8_t numberofmessages;			// holds how many states are different since the last sense
	stop_watchdog ();				// stop the watchdog
	zeroarray_8bitunsigned (currentarray, NUMBER_OF_CHANNELS); // initialize variables
	zeroarray_8bitunsigned (lastarray, NUMBER_OF_CHANNELS);
	zeroarray_8bitsigned (diffarray, NUMBER_OF_CHANNELS);
	portdriver_init (&p2, 0xFF & ~MULT_IN, &P2DIR, &P2IN, &P2OUT);
	device_init ();					// initialize device
	multiplexordriver_init (&mult, 1,&p2,NUMBER_OF_CHANNELS);
	while (1){
		P1OUT |= LED;				// measures 2.64 ms
		sensechannels (currentarray, NUMBER_OF_CHANNELS, &mult);	// 1. get the current sense
		P1OUT &= ~LED;				// rest of loop measures 820 us
		numberofmessages = filldiffarray (currentarray, NUMBER_OF_CHANNELS, lastarray, diffarray);
		// 2. find which inputs are different since the last sense
		if (numberofmessages){	// 3. if there are any messages to send
			send_messages (diffarray,numberofmessages, 127);	// send them
		}
		copyarray_8bitunsigned (currentarray, NUMBER_OF_CHANNELS, lastarray);	// 4. Copy the current sense into the last sense
	}
	return (1);
}


void send_messages (int8_t *array, uint8_t length, uint8_t velocity){
	uint8_t ctr;
	int8_t tmp;
	uint8_t messagearray[3] = {NOTE_ON, 0, 0};
	for (ctr = 0; ctr < length; ctr++){
		if (*(array+ctr) > 0){
			messagearray[1] = *(array + ctr) + (LOWEST_NOTE);
			messagearray[2] = velocity;
		} else if (*(array+ctr) < 0){
			tmp = -(*(array + ctr));
			messagearray[1] = tmp + (LOWEST_NOTE);
			messagearray[2] = 0;
		}
		send_data (messagearray, 3);
	}


}

void sensechannels (uint8_t *array, uint8_t numberofchannels, struct multiplexordriver_struct *mult){
	uint8_t ctr;
	multiplexordriver_setchannel (mult, 0);
	for (ctr = 0; ctr < numberofchannels; ctr++){
		*(array + ctr) = ((P2IN & MULT_IN) == 0);
		multiplexordriver_incchannel (mult);	
	}
}



