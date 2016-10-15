#include "arrayhandlers.h"

void zeroarray_unsigned (uint8_t *array, uint8_t length){
	uint8_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}
void zeroarray_signed (int8_t *array, uint8_t length){
	uint8_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}

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
		}else {
			*(diffarray + ctr) = 0;
		}
	}
	return diffctr;
}

void copyarray (uint8_t *arraytocopy, uint8_t length, uint8_t *copytoarray){
	uint16_t ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(copytoarray + ctr) = *(arraytocopy + ctr);
	}
}

