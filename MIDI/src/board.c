#include <msp430.h>
#include <pins.h>

void device_init (void){
	P1OUT = 0x00;
	P1DIR = LED | TX_PIN;
	P1SEL = TX_PIN;
	P1SEL2 = TX_PIN;

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	UCA0CTL1 = UCSWRST;
	UCA0CTL0 = 0x00;
	UCA0BR0 = 32;
	UCA0BR1 = 0;
	UCA0CTL1 |= UCSSEL_3;
	UCA0CTL1 &= ~UCSWRST;

	
	
}
