#include "avr/io.h"

void ADC_Init()
{
	DDRA &= ~(1<<0);
	ADCSRA |= (1<<ADEN); //enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX |= (1<<REFS0);
}

int ADC_Read(char channel)
{
	ADMUX = 0x40 | (channel & 0x07);
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)))
	{
		ADCSRA |= (1<<ADIF);
	}
	_delay_ms(1);
	return ADCW;
}