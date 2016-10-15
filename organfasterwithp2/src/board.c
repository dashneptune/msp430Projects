#include <msp430.h>
#include <pins.h>

void device_init (void){
	P1OUT = 0x00;	// preload all outputs off
	P1DIR =  LED | TX_PIN;	// the only outputs are the led and the transmission pin
	P1SEL = TX_PIN | RX_PIN;	// give the tx pin to the usci special function
	P1SEL2 = TX_PIN | RX_PIN;
	P1IE = 0x00;
	P1IES = 0x00;
	P1IFG = 0x00;
	P1REN = 0x00;
	// ""
	P2OUT = 0x00;	// preload all outputs low
	P2DIR =0x00;	// everything is an input in port 2
	P2REN = 0xFF;	// enable all of the pullup resistors
	P2SEL = 0x00;
	P2SEL2 = 0x00;
	P2IE = 0x00;
	P2IES = 0x00;
	P2IFG = 0x00;

	BCSCTL1 = CALBC1_1MHZ;
	// set the fast clocks to be 1MHz
	DCOCTL = CALDCO_1MHZ;
	// set the fast clocks to be 1 MHz
	UCA0CTL1 = UCSWRST;
	// allow the USCI to be configured
	UCA0CTL0 = 0x00;	// nothing fancy going on
	UCA0BR0 = 32;		// shoot for a baud rate of 31250
	// defined by MIDI spec
	UCA0BR1 = 0;
	UCA0CTL1 |= UCSSEL_3;	// clock from SMCLK
	UCA0CTL1 &= ~UCSWRST;	// free up the USCI
/*
	// use the internal reference, wait for 64 sample and hold clock cycles, turn the reference on, turn the adc on, enable adc interrupts
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;
	ADC10CTL1 = INCH_1 | CONSEQ_0 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0;
	// use input channel 1 (p1.1), single conversion, single channel, trigger from the ADC10SC bit in ADC10CTL0, don't divide the clock down at all, clock from ADC10OSC (~5Mhz but not guaranteed)
	ADC10DTC1 = 0;	//disable the data transfer controller
	ADC10AE0 = ANALOG_IN;

*/	
}
