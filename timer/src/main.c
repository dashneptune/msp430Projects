#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "watchdog.h"
#include "board.h"

int main (void){
	uint16_t ctr;
	stop_watchdog ();
	device_init ();
	TA0CTL |= MC_1;
	ctr = 0xFF;
	__enable_interrupt ();
	while (1){
		__low_power_mode_0 ();
	}
	return (1);
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void isr_cc0_TA0 (void){
	P1OUT |= LED;
	TA0CTL &= ~MC_3;
	__low_power_mode_off_on_exit ();
}

__attribute__((interrupt(TIMER0_A1_VECTOR)))
void isr_cc1_TA0 (void){
	TA0CCTL1 &= ~CCIFG;
	P1OUT &= ~LED;
}
