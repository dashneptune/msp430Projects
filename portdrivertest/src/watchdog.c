#include "watchdog.h"
#include <msp430.h>


void stop_watchdog (void){
	WDTCTL = WDTPW | WDTHOLD;
}
