#include <msp430.h>
#include "pins.h"
#include "watchdog.h"
#include "portdriver.h"

int main (void){
	uint16_t j;
	stop_watchdog ();
	struct portdriver_struct port;
	portdriver_init (&port, LED,&P1DIR,&P1IN, &P1OUT);
	while (1){
		portdriver_writetopin (&port, 1, 0);
		while (j--);
		portdriver_writetopin (&port, 1, 1);
		while (j--);
	}
	return (1);
}
