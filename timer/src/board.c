#include <msp430.h>
#include "pins.h"
#include "board.h"



void device_init (){
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL3 = LFXT1S_3;

	P1OUT = 0x00;
	P1DIR = LED;
	TA0CCR0 = 0xFF;
	TA0CCR1 = 20;
	TA0CTL = TASSEL_1 | ID_0 | TACLR;
	/* src from ACLK, no subdivider, clear the time value */
	TA0CCTL0 = CCIE;
	TA0CCTL1 = CCIE;
}
