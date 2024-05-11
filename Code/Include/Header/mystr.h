#ifndef MYSTR_H_
#define MYSTR_H_
#include "avr/io.h"
void int_to_string(int32_t num, char *str);
void float_to_string(float num, char *str);
void clearCharArray(char* str);
#endif /* MYSTR_H_ */