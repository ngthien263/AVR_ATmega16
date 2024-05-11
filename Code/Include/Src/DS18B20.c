#include "DS18B20.h"
#include <mystr.h>

extern float temp;

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

float readTemp()
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
	ftemp = ( ( iTempH << 8 ) + iTempL ) * 0.0625;
	return ftemp;
}

void handleLED(float wTemp)
{
	PORTD &= ~((1<<LED_R) | (1<<LED_G) | (1<<LED_Y)); 

	if(temp < wTemp - 0.5)
	{
		PORTD |= (1<<LED_R); 
	}
	else if(temp > wTemp + 0.5)
	{
		PORTD |= (1<<LED_G); 
	}
	else if((wTemp - 0.5 < temp) && (temp < wTemp + 0.5))
	{
		PORTD |= (1<<LED_Y); 
	}
}
