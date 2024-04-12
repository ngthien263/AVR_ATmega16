#include "DS18B20.h"

unsigned char reset()
{
	unsigned char re;
	DDRA |= (1<<WIRE_PIN);
	PORTA &= (1<<WIRE_PIN);
	_delay_us(480);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(60);
	re = PORTA & (1<<WIRE_PIN);
	_delay_us(420);
	return re;
}

void writebit(unsigned char bit)
{
	DDRA |= (1<<WIRE_PIN);
	PORTA &= (1<<WIRE_PIN);
	_delay_us(1);
	if (bit == 1)
	{
		DDRA &= ~(1<<WIRE_PIN);
	}
	_delay_us(60);
	DDRA &= ~(1<<WIRE_PIN);
}

unsigned char readbit()
{
	unsigned char bit = 0;
	DDRA |= (1<<WIRE_PIN);
	PORTA &= (1<<WIRE_PIN);
	_delay_us(1);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(14);
	if (PORTA & (1<<WIRE_PIN))
		bit = 1;
	_delay_us(45);
	return bit;
}

void writebyte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		writebit(byte & (0x01<<i))
	}
}

unsigned char readbyte()
{
	unsigned char n = 0;
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		n |= (readbit()<<i);
	}
	return n;
}

float readTemp()
{
	unsigned char iTempL;
	unsigned char iTempH;
	float ftemp = 0;
	while(reset());
	writebyte(SKIPROM);
	writebyte(CONVERT_T);
	while(!readbit());
	while(reset());
	writebyte(SKIPROM);
	writebyte(RSCRATCHPAD);
	
	iTempL = readbyte();
	iTempH = readbyte() ;
	unsigned int temp = (iTempH << 8) | iTempL;
	ftemp = temp * 0.0625;
	return ftemp;
}

