#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "watchdog.h"
#include "board.h"
#include "arrayhandler.h"
#define HALF_RANGE	(0x01 << 9)


int main (void){
	volatile unsigned int samplearray[NUMBER_OF_SAMPLES];
	unsigned int result = 0x00;
	stop_watchdog ();
	zero_array ((unsigned int*)samplearray, NUMBER_OF_SAMPLES);
	device_init ();
	ADC10SA = (unsigned short)samplearray;
	__enable_interrupt ();
	ADC10CTL0 |= ENC;
	TA0CTL |= MC_1;
	while (1){
		__low_power_mode_0 ();
		result = average_array ((unsigned int *)samplearray,NUMBER_OF_SAMPLES);
		if (result > HALF_RANGE){
			P1OUT &= ~LOWER_LED;
			P1OUT |= UPPER_LED;
		}else {
			P1OUT |= LOWER_LED;
			P1OUT &= ~UPPER_LED;
		}
	}
	return (1);
}


__attribute__((interrupt(ADC10_VECTOR)))
void isr_ADC (void){
	__low_power_mode_off_on_exit ();
}


