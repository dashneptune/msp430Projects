#include <stdint.h>

void copyarray (uint8_t *arraytocopy, uint8_t length, uint8_t *copytoarray);
uint16_t filldiffarray (uint8_t *currentarray, uint8_t length, uint8_t *lastarray, int8_t *diffarray);
void zeroarray_unsigned (uint8_t *array, uint8_t length);
void zeroarray_signed (int8_t *array, uint8_t length);
