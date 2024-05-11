#define F_CPU 8000000ul
#include <avr/io.h>
#include <LCD.h>
#include <mystr.h>
#include "DS18B20.h"
float temp;
char temp_str[10];
float wTemp = 24.1;
int main(void)
{	
	LCD_init();
    while (1) 
    {
		temp = readTemp();
		clearCharArray(temp_str);
		float_to_string(temp, temp_str);
		LCD_clear();
		LCD_print("Temp: ");
		LCD_print(temp_str);
		handleLED(wTemp);
    }
}

