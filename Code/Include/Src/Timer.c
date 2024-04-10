#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/iom16.h"

#define F_CPU 12000000
#define PRESCALER 1

volatile unsigned char t;

void T0_delay_us()
{
	TCNT0 = ;
	TCCR0 |= (1<<CS00);
	TIMSK |= (1<<TOIE0);
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = ;
}

