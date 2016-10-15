#include <msp430.h>
#include "pins.h"
#include "watchdog.h"
#include "multiplexor.h"

int main (void){
	struct portdriver_struct p1;
	struct portdriver_struct p2;
	struct multiplexordriver_struct mult;
	stop_watchdog ();
	portdriver_init (&p1, 0xFF, &P1DIR, &P1IN, &P1OUT);
	portdriver_init (&p2, 0xFF & ~MULT_IN, &P2DIR, &P2IN, &P2OUT);
	multiplexordriver_init (&mult, 1,&p2, 8);
	while (1){
		__nop ();
		multiplexordriver_incchannel(&mult);
	}
	return (1);
}
