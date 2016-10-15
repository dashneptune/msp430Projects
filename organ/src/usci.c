#include <msp430.h>



struct tx_struct {
	unsigned char *tx;
	unsigned int txlength;
}tx_struct;

void send_data (unsigned char *tx, unsigned int txlength){
	tx_struct.tx = tx;	/* point our transmission pointer at the global pointer*/
	tx_struct.txlength = txlength;
	IE2 |= UCA0TXIE;	/*enable transmission interrupts */
	__low_power_mode_0 ();  /* go into low power mode 0 */
}


__attribute__((interrupt(USCIAB0TX_VECTOR)))
void isr_cc0_TA0 (void){
	static unsigned int ctr = 0;
	if (IFG2 & UCA0TXIFG){
		UCA0TXBUF = *(tx_struct.tx + ctr);
		if (++ctr >= tx_struct.txlength){
			__low_power_mode_off_on_exit ();
			ctr = 0;
			IE2 &= ~UCA0TXIE;
		}
	}
}
