#include "DS18B20.h"

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
	unsigned char i=8;
	uint8_t n=0;
	for(i = 0; i < 8; i++)
	{
		n |= (readbit()<<i);
	}
	return n;
}

uint8_t readTemp()
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
	unsigned int temp = (iTempH << 8) | iTempL;
	ftemp = (uint8_t)(temp * 0.0625);
	return ftemp;
}
