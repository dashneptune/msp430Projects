#include <msp430.h>
#include <pins.h>

void device_init (void){
	P1OUT = 0x00;	// preload all outputs off
	P1DIR =  LED | TX_PIN;	// the only outputs are the led and the transmission pin
	P1SEL = TX_PIN | RX_PIN;	// give the tx pin to the usci special function
	P1SEL2 = TX_PIN | RX_PIN;
	P1IE = LEFT_MOTOR_PIN | RIGHT_MOTOR_PIN;
	P1IES = 0x00;
	P1IFG = 0x00;
	P1REN = LEFT_MOTOR_PIN | RIGHT_MOTOR_PIN;
	// ""
	P2OUT = 0x00;	// preload all outputs low
	P2DIR =0xFF;	// everything is an input in port 2
	P2REN = 0x00;	// enable all of the pullup resistors
	P2SEL = 0x00;
	P2SEL2 = 0x00;
	P2IE = 0x00;
	P2IES = 0x00;
	P2IFG = 0x00;

	BCSCTL1 = CALBC1_1MHZ;
	// set the fast clocks to be 16 MHz
	DCOCTL = CALDCO_1MHZ;
  BCSCTL3 = LFXT1S_2;

	// set the fast clocks to be 16 MHz
	UCA0CTL1 = UCSWRST;
	// allow the USCI to be configured
	UCA0CTL0 =0;	// nothing fancy going on
	UCA0BR0 = 104;		// shoot for a baud rate of 9600
	UCA0BR1 = 0;
	UCA0CTL1 |= UCSSEL_3;	// clock from SMCLK
	UCA0CTL1 &= ~UCSWRST;	// free up the USCI

  
  TA0CTL = MC_0 | TASSEL_1 | ID_0 | TACLR;    // clock from ACLK, divide by 64 clear the value dont count yet
  TA0CCTL0 = CCIE;                            // enable interrupts off of TACCR0
  TACCR0 = 0x40;

  TA1CTL = MC_0 | TASSEL_2 | ID_0 | TACLR;    // clock from SMCLK, no division, clear the vlaue in the register
  TA1CCTL0 = CCIE;
  TA1CCR0 =100;
}
