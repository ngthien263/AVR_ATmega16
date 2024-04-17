#ifndef DS18B20_H
#define DS18B20_H
#define F_CPU 8000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define WIRE_PIN 0
#define CONVERT_T 0x44
#define RSCRATCHPAD 0xBE
#define WSCRATCHPAD 0x4E
#define SKIPROM 0xCC
uint8_t reset(void);
void writebit(unsigned char bit);
uint8_t readbit(void);
void writebyte(unsigned char byte);
uint8_t readbyte(void);
int readTemp(void);
void int_part(char *intp_str);
void decimal_part(char *dcmp_str);
#endif // DS18B20_H
