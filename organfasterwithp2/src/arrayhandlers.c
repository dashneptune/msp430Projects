#include "arrayhandlers.h"
#include "msp430.h"
#include "pins.h"

// fills an unsigned integer array with zeros

void zeroarray_unsigned (uint8_t *array, uint8_t length){
	uint8_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}



// fills a signed integer array with zeros
void zeroarray_signed (int8_t *array, uint8_t length){
	uint8_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}

// fills an array with the difference between two unsigned arrays
// returns a value equal to the number of non zero entries in the resultant array
uint16_t filldiffarray (uint8_t *currentarray, uint8_t length, uint8_t *lastarray, int8_t *diffarray){
	uint8_t ctr;
	uint16_t diffctr = 0;
	for (ctr = 0; ctr < length; ctr++){
		if (*(currentarray + ctr) != *(lastarray + ctr)){
			if (*(currentarray + ctr)){
				*(diffarray + ctr) = 1;
			} else {
				*(diffarray + ctr) = -1;
			}
			diffctr++;
		} else {
			*(diffarray + ctr) = 0;
		}
	}
	return diffctr;
}

// copies one unsigned array to another

void copyarray (uint8_t *arraytocopy, uint8_t length, uint8_t *copytoarray){
	uint16_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(copytoarray + ctr) = *(arraytocopy + ctr);
	}
}

