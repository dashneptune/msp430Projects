

#include "portdriver.h"

const uint8_t pinToByte[8] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

uint8_t PinInRange (uint8_t pin){
	return ((pin < 8 && pin > 0));
}

void portdriver_init (struct portdriver_struct *port, uint8_t directionmask, uint8_t * directionptr, uint8_t *input_ptr, uint8_t *outputptr){
	port->dirptr = directionptr;
	*(port->dirptr) = directionmask; 
	port->inputptr = input_ptr;
	port->outputptr = outputptr;
	port->overr = PORTDRIVER_NO_ERR;
}

uint8_t portdriver_getdirection (struct portdriver_struct port){
	return (*port.dirptr);
}


uint8_t portdriver_getportval (struct portdriver_struct port){
	return (*port.inputptr);
}

void portdriver_setpinhigh (struct portdriver_struct *port, uint8_t pin){
	if (PinInRange(pin)){
		uint8_t cache = *(port->outputptr);
		cache |= pinToByte[pin -1 ];
		*(port->outputptr) = cache;
		port->overr = PORTDRIVER_NO_ERR;
	} else {
		port->overr = PORTDRIVER_OV_ERR;
	}
}

void portdriver_setpinlow (struct portdriver_struct *port, uint8_t pin){
	if (PinInRange(pin)){
		uint8_t cache = *(port->outputptr);
		cache &= ~pinToByte[pin - 1];
		*(port->outputptr) = cache;
		port->overr = PORTDRIVER_NO_ERR;
	} else {
		port->overr = PORTDRIVER_OV_ERR;
	}
}


void portdriver_setmask (struct portdriver_struct *port, uint8_t mask){
	*(port->outputptr) = mask;
}

uint8_t portdriver_getpinval (struct portdriver_struct *port, uint8_t pin){
	if (PinInRange (pin)){
		port->overr = PORTDRIVER_NO_ERR;
		return ((*(port->inputptr) & pinToByte[pin - 1]) != 0);
	} else {
		port->overr = PORTDRIVER_OV_ERR;
		return 0;
	}
}

void portdriver_writetopin (struct portdriver_struct *port, uint8_t pin, uint8_t state){
	if (state){
		portdriver_setpinhigh (port, pin);
	} else {
		portdriver_setpinlow (port, pin);
	}
}

uint8_t portdriver_geterr (struct portdriver_struct port){
	return (port.overr);
}

