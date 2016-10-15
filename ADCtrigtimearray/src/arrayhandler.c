#include "arrayhandler.h"



unsigned int lengthtoshift (unsigned int length){
	switch (length){
		case 1:
			return 0;
		case 2:
			return 1;
		case 4: 
			return 2;
		case 8:
			return 3;
		case 16:
			return 4;
		case 32:
			return 5;
		case 64:
			return 6;
		case 128:
			return 7;
		default:
			while (1);
	}
}

void zero_array (unsigned int *array, unsigned int length){
	unsigned int ctr;	
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) =0;
	}	
}

unsigned int average_array (unsigned int *array, unsigned int length){
	unsigned long int sum = 0;
	unsigned int ctr;	
	for (ctr = 0; ctr < length; ctr++){
		sum += *(array + ctr);
	}
	return (sum >> lengthtoshift(length));
}
