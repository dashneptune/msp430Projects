#include <msp430.h>
#include <usci.h>
#include <pins.h>
#include <intrinsics.h>

struct tx_struct {
	uint8_t *tx;
	uint8_t txlength;
}tx_struct;

//struct queue_struct *input_struct;
uint16_t err;
uint8_t rx;
uint8_t new_rx;

/*
void init_internal_queue (struct queue_struct *input){
  queue_init (input);     // initialize the struct 
  input_struct = input;   // point our internal file pointer at the struct
}*/

uint8_t get_rx_value (){
  new_rx = 0;
  return rx;
}

uint8_t has_rx_value (){
  return new_rx;
}

void send_data (uint8_t *tx, uint8_t txlength){
	tx_struct.tx = tx;	/* point our transmission pointer at the global pointer*/
	tx_struct.txlength = txlength;
	IE2 |= UCA0TXIE;	/*enable transmission interrupts */
	LPM0;  /* go into low power mode 0 */
}

__attribute__((interrupt(USCIAB0TX_VECTOR)))
void isr_usci_tx (void){
	static uint8_t ctr = 0;
	if (IFG2 & UCA0TXIFG){
		UCA0TXBUF = *(tx_struct.tx + ctr);
		if (++ctr >= tx_struct.txlength){
		  LPM4_EXIT;
			ctr = 0;
			IE2 &= ~UCA0TXIE;
		}
	}
}

__attribute__((interrupt(USCIAB0RX_VECTOR)))
void isr_usci_rx (void){
	if (IFG2 & UCA0RXIFG){
    rx = UCA0RXBUF;
    new_rx = 1;  
    LPM4_EXIT;
		IFG2 &= ~UCA0RXIFG;
	}
}

