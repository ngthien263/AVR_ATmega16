#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define WIRE_PIN 1
uint8_t reset()
{
	uint8_t re;
	DDRA |= (1<<WIRE_PIN);
	PORTA &= (1<<WIRE_PIN);
	_delay_us(480);
	DDRA &= ~(1<<WIRE_PIN);
	_delay_us(60);
	re = PORTA & (1<<WIRE_PIN);
	_delay_us(420);
	return re;
}

void writebit(uint8_t bit)
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

uint8_t readbit()
{
	uint8_t bit = 0;
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

void writebyte(uint8_t byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		writebit(byte & (0x01<<i))
	}
}

uint8_t readbyte()
{
	uint8_t n = 0;
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		n |= (readbit()<<i);
	}
	return n;
}