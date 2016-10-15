#include "portdriver.h"

struct multiplexordriver_struct{
	uint8_t channel;
	uint8_t minpin;
	uint8_t numberofchannels;
	struct portdriver_struct *port;
	uint8_t overr;
	uint8_t width;
};

#define MULTIPLEXORDRIVER_OV_ERR	1
#define MULTIPLEXORDRIVER_NO_ERR	0


void multiplexordriver_init (struct multiplexordriver_struct *mult, uint8_t minpin, struct portdriver_struct *port, uint8_t channel);
void multiplexordriver_setchannel (struct multiplexordriver_struct *mult, uint8_t channel);
void multiplexordriver_incchannel (struct multiplexordriver_struct *mult);
uint8_t multiplexordriver_getchannel (struct multiplexordriver_struct mult);

