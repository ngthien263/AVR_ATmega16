#ifndef DS18B20_H
#define DS18B20_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define WIRE_PIN 1
#define CONVERT_T 0x44
#define RSCRATCHPAD 0xBE
#define WSCRATCHPAD 0x4E
#define SKIPROM 0xCC
unsigned char reset(void);
void writebit(unsigned char bit);
unsigned char readbit(void);
void writebyte(unsigned char byte);
unsigned char readbyte(void);
float readTemp(void);

#endif // DS18B20_H
