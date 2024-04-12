#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#define LCD_DATA_PORTC			PORTC
#define LCD_DATA_DDRC			DDRC
#define LCD_CONTROL_PORTD		PORTD
#define LCD_CONTROL_DDRD			DDRD
#define LCD_RS					PD2
#define LCD_RW					PD1
#define LCD_E					PD0
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init() ;
void LCD_clear();
void LCD_gotoxy(unsigned char x, unsigned char y);
void LCD_print(const char *str); 

#endif /* LCD_H_ */