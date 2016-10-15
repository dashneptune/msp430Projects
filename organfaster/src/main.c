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
void 

int main (void){
	uint8_t currentarray[NUMBER_OF_CHANNELS];	// array to hold newest read of states
	uint8_t lastarray[NUMBER_OF_CHANNELS];
	// array to hold last read of states
	int8_t diffarray[NUMBER_OF_CHANNELS];
	// array to hold the difference of states between last and current read
	uint8_t numberofmessages;	// number of messages
	uint8_t velocity;		// velocity to send over MIDI
	stop_watchdog ();		// stop the watchdog timer
	// zero the arrays
	zeroarray_unsigned (currentarray, NUMBER_OF_CHANNELS);
	zeroarray_unsigned (lastarray, NUMBER_OF_CHANNELS);
	zeroarray_signed (diffarray, NUMBER_OF_CHANNELS);
	device_init ();			// initialize the device (in board.c)
	__enable_interrupt ();		// enable interrupts
	while (1){			// the big forever loop in the sky
		ADC10CTL0 |= ENC | ADC10SC;
		// get the ADC reading for the velocity
		__low_power_mode_0 ();	// go into low power mode 0
		velocity = ADC10MEM;	// the velocity is stored in the ADC10 memory register
		velocity >>= 3;
		sensechannels (currentarray, NUMBER_OF_CHANNELS);
		// get the current state of all of the channels
		numberofmessages = filldiffarray (currentarray, NUMBER_OF_CHANNELS, lastarray, diffarray);
		// get the difference between the current and last iterations
		if (numberofmessages){
			send_messages (diffarray,NUMBER_OF_CHANNELS, velocity);
		}
		// if the number of messages is greatre than 0, send messages over midi
		copyarray (currentarray, NUMBER_OF_CHANNELS, lastarray);
		// copy the current state array to the last one
	}
	return (1);
}
void send_messages (int8_t *array, uint8_t length, uint8_t velocity){
	uint8_t ctr;
	uint8_t tmp;
	uint8_t messagearray[3];
	for (ctr = 0; ctr < length; ctr++){
		if (*(array+ctr) != 0){
			if (*(array+ctr) > 0){
				messagearray[0] = NOTE_ON;
				messagearray[1] = *(array + ctr);
				messagearray[2] = velocity;
			} else if (*(array+ctr) < 0){
				tmp = -(*(array + ctr));
				messagearray[0] = NOTE_OFF;
				messagearray[1] = tmp;
				messagearray[2] = velocity;
			}
			send_data (messagearray, 3);
		}
	}


}
void sensechannels (uint8_t *array, uint8_t numberofchannels){
	uint8_t ctr;
	uint8_t cache = P2OUT;
	cache &= ~MUX_PINS;
	P2OUT = cache;
	for (ctr = 0; ctr < numberofchannels; ){
		__delay_cycles (1000);
		*(array + ctr) = ((P2IN & MUX_IN) == 0);
		ctr++;
		cache = P2OUT;
		cache &= ~MUX_PINS;
		cache |= ctr;
		P2OUT = cache;
	}
}


__attribute__((interrupt(ADC10_VECTOR)))
void isr_ADC (void){
	__low_power_mode_off_on_exit ();
}


