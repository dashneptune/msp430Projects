#include <msp430.h>
#include <stdint.h>
#include <pins.h>
#include <board.h>
#include <signal.h>

struct tx_struct{
	uint8_t *tx;
	uint8_t txlength;
}tx_struct;

unsigned int rxflag = 0;
unsigned char rxval;

void send_data (uint8_t *tx, uint8_t txlength);

int main (void){
	/*uint8_t array[3];*/
	WDTCTL = WDTPW | WDTHOLD;	/*stop the watchdog timer*/
	/*array[0] = 0x90;
	array[1] = 127 >> 1;
	array[2] = 127;*/
	device_init ();			/* initialize device */
	__nop ();
	__enable_interrupt ();
	IFG2 &= ~UCA0RXIFG;
	IE2 |= UCA0RXIE;
	while (1){
		/*send_data (array,3);*/
		if (rxflag){
			rxflag = 0;
		}
	}
	return (1);
}


void send_data (uint8_t *tx, uint8_t txlength){
	tx_struct.tx = tx;	/* point our transmission pointer at the global pointer*/
	tx_struct.txlength = txlength;
	IE2 |= UCA0TXIE;	/*enable transmission interrupts */
	__low_power_mode_0 ();  /* go into low power mode 0 */
}

__attribute__((interrupt(USCIAB0TX_VECTOR)))
void isr_tx (void){
	static uint8_t ctr = 0;
	if (IFG2 & UCA0TXIFG){
		UCA0TXBUF = *(tx_struct.tx + ctr);
		if (++ctr >= tx_struct.txlength){
			__low_power_mode_off_on_exit ();
			ctr = 0;
			IE2 &= ~UCA0TXIE;
		}
	}
}

__attribute__((interrupt(USCIAB0RX_VECTOR)))
void rx_isr (void){
	if (IFG2 & UCA0RXIFG){
		P1OUT |= LED;
	}
}