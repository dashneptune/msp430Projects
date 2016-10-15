#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "watchdog.h"
#include "board.h"

uint16_t result;

#define HALF_RANGE	(0x01 << 9)


int main (void){
	stop_watchdog ();
	device_init ();
	__enable_interrupt ();
	while (1){
		ADC10CTL0 |= (ENC | ADC10SC);
		__low_power_mode_0 ();
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
void isr_ADC (void){cd 
	result = ADC10MEM;
	__low_power_mode_off_on_exit ();
}


