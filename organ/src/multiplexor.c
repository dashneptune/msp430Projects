#include "multiplexor.h"


uint8_t multiplexordriver_calcwidth (uint8_t numberofchannels){
	int8_t width = 0;
	if (numberofchannels){
		width++;
	}
	if (numberofchannels > 2){
		width++;
	}
	if (numberofchannels > 4){
		width++;
	}
	if (numberofchannels > 8){
		width++;
	}
	if (numberofchannels > 16){
		width++;
	}
	return (width);
}


void multiplexordriver_applytoport (struct multiplexordriver_struct *mult, uint8_t oldchannel){
	uint8_t cache;
	cache = portdriver_getportval (*mult->port);
	cache &= ~oldchannel;
	cache |= (mult->channel << (mult->minpin - 1));
	portdriver_setmask (mult->port,cache);
}


void multiplexordriver_init (struct multiplexordriver_struct *mult, uint8_t minpin, struct portdriver_struct *port, uint8_t numberofchannels){
	mult->channel = 0;
	mult->minpin = minpin;
	mult->port = port;
	mult->numberofchannels = numberofchannels;
	mult->width = multiplexordriver_calcwidth (numberofchannels);
}

void multiplexordriver_setchannel (struct multiplexordriver_struct *mult, uint8_t channel){
	uint8_t oldchannel = mult->channel;
	if (channel < mult->numberofchannels){
		mult->channel = channel;
		mult->overr = MULTIPLEXORDRIVER_NO_ERR;
		multiplexordriver_applytoport (mult, oldchannel);
	} else {
		mult->overr = MULTIPLEXORDRIVER_OV_ERR;
	}
}


void multiplexordriver_incchannel (struct multiplexordriver_struct *mult){
	uint8_t oldchannel = mult->channel;
	if (mult->channel < mult->numberofchannels){
		mult->channel++;
	} else {
		mult->channel = 0;
	}
	mult->overr = MULTIPLEXORDRIVER_NO_ERR;
	multiplexordriver_applytoport (mult, oldchannel);
}

uint8_t multiplexordriver_getchannel (struct multiplexordriver_struct mult){
	return mult.channel;
}