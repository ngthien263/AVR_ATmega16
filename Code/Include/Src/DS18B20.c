#include "DS18B20.h"
#include <mystr.h>
uint8_t reset()
{
	uint8_t re;
	DDRA |= (1<<WIRE_PIN);
	PORTA &= ~(1<<WIRE_PIN);
	_delay_us(480);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(70);
	re = PINA & (1<<WIRE_PIN);
	_delay_us(420);
	return re;
}

void write1()
{
	DDRA |= (1<<WIRE_PIN);
	PORTA &= ~(1<<WIRE_PIN);
	_delay_us(6);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(64);
}

void write0()
{
	DDRA |= (1<<WIRE_PIN);
	PORTA &= ~(1<<WIRE_PIN);
	_delay_us(60);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(10);
}

void writebit(unsigned char bit)
{
	if(bit==1)
		write1();
	else
		write0();
}

uint8_t readbit()
{
	uint8_t res;
	DDRA |= (1<<WIRE_PIN);
	PORTA &= ~(1<<WIRE_PIN);
	_delay_us(6);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(9);
	res = PINA & (1<<WIRE_PIN);
	_delay_us(55);
	return res;
}

void writebyte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		writebit((byte>>i) & 0x01);
	}
}

uint8_t readbyte()
{
	unsigned char i;
	uint8_t n=0;
	for(i = 0; i < 8; i++)
	{
		n |= (readbit()<<i);
	}
	return n;
}

int readTemp()
{
	unsigned char iTempL;
	unsigned char iTempH;
	float ftemp = 0;
	reset();
	writebyte(SKIPROM);
	writebyte(CONVERT_T);
	while(!readbit());
	reset();
	writebyte(SKIPROM);
	writebyte(RSCRATCHPAD);
	
	iTempL = readbyte();
	iTempH = readbyte() ;
	int temp = (iTempH << 8) | iTempL;
	return temp;
}

void int_part(char* intp_str)
{
	uint8_t intp = readTemp()>>4;
	int_to_string(intp, intp_str);
}

void decimal_part(char* dcmp_str)
{
	uint8_t dcmp = readTemp() * 0x000F;
	dcmp = dcmp * 10/16;
	int_to_string(dcmp, dcmp_str);
}