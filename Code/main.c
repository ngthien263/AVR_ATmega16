#define F_CPU 8000000ul
#include <avr/io.h>
#include <LCD.h>
#include <mystr.h>
#include "DS18B20.h"
int main(void)
{	
	LCD_init();
    while (1) 
    {
		LCD_print("Temp: ");
		char int_str[7];
		char dcm_str[4];
		int_part(int_str);
		decimal_part(dcm_str);
		LCD_print(int_str);
		LCD_print(".");
		LCD_print(dcm_str);
		_delay_ms(200);
		LCD_clear();
    }
}

