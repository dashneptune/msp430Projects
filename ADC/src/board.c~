#include <msp430.h>
#include "pins.h"

void port1_init ();
void port2_init ();
//void timer_init ();
void adc_init ();

void device_init (){
	port1_init ();
	port2_init ();
	adc_init ();
}


void port1_init (){
	P1OUT = 0x00;
	P1DIR = 0xFF;
	P1SEL = 0x00;
	P1SEL2 = 0x00;
	P1REN = 0x00;
	P1IE = 0x00;
	P1IFG = 0x00;
}

void port2_init (){
	P2OUT = 0x00;
	P2DIR = 0xFF;
	P2SEL = 0x00;
	P2SEL2 = 0x00;
	P2REN = 0x00;
	P2IE = 0x00;
	P2IFG = 0x00;
}

void adc_init (){
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;
	// reference from V++ and gnd, use 64 clocks of the ADC10CLK for sampling, turn the reference on, turn the adc on, enable ADC interrupts
	ADC10CTL1 = INCH_1 | SHS_0 | ADC10DIV_0  | ADC10SSEL_0 | CONSEQ_0;
	// enable input from input channel 1, trigger from ADC10SC bit in ADC10CTL0, don't divide the clock, source clock from ADC10OSC, single channel single sequence
	ADC10AE0 = ANALOG_IN;
	// enable the analog mux
}

