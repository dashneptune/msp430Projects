

void zeroarray_8bitunsigned (unsigned char *array, unsigned int length){
	unsigned int ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}
void zeroarray_8bitsigned (signed char *array, unsigned int length){
	unsigned int ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(array + ctr) = 0;
	}
}

void copyarray_8bitunsigned (unsigned char *arraytocopy, unsigned int length, unsigned char *copytoarray){
	unsigned int ctr;
	for (ctr = 0; ctr < length; ctr++){
		*(copytoarray + ctr) = *(arraytocopy + ctr);
	}
}

unsigned char filldiffarray (unsigned char *currentarray, unsigned int length, unsigned char *lastarray, signed char *diffarray){
	unsigned int ctr;
	unsigned char diffctr = 0;
	zeroarray_8bitsigned (diffarray, length);
	for (ctr = 0; ctr < length; ctr++){
		if (*(currentarray + ctr) != *(lastarray + ctr)){
			if (*(currentarray + ctr)){
				*(diffarray + diffctr) = ctr;
			}else {
				*(diffarray + diffctr) = -ctr;
			}
			diffctr++;
		}
	}
	return diffctr;
}
