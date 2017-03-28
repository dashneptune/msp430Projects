#ifndef __USCI_H_
#define __USCI_H_
#include <stdint.h>
//#include <queue.h>

void send_data (uint8_t *tx, uint8_t txlength);
uint8_t has_rx_value (void);
uint8_t get_rx_value (void);

#endif
