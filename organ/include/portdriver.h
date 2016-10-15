
#include <stdint.h>

struct portdriver_struct {
	volatile uint8_t *dirptr;
	volatile uint8_t *inputptr;
	volatile uint8_t *outputptr;
	uint8_t overr;
};


#define PORTDRIVER_NO_ERR	0
#define PORTDRIVER_OV_ERR	1
#define PORTDRIVER_AFFECT_SPECIAL	2

void portdriver_init (struct portdriver_struct *port, uint8_t direction_mask, volatile uint8_t *directionptr, volatile uint8_t *inputptr,  volatile uint8_t *outputptr);
uint8_t portdriver_getdirection (struct portdriver_struct port);
uint8_t portdriver_getportval (struct portdriver_struct port);
void portdriver_setpinhigh (struct portdriver_struct *port, uint8_t pin);
void portdriver_setpinlow (struct portdriver_struct *port, uint8_t pin);
void portdriver_setmask (struct portdriver_struct *port, uint8_t mask);
uint8_t portdriver_getpinval (struct portdriver_struct *port, uint8_t pin);
void portdriver_writetopin (struct portdriver_struct *port, uint8_t pin, uint8_t state);
uint8_t portdriver_geterr (struct portdriver_struct port);
void portdriver_setrangeofpins (struct portdriver_struct *port, uint8_t val, uint8_t mask);
