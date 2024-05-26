#ifndef LCD_H_
#define LCD_H_
#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DATA_PORT			PORTD
#define LCD_DATA_DDR			DDRD
#define LCD_CONTROL_PORT		PORTB
#define LCD_CONTROL_DDR			DDRB
#define LCD_RS	PB2
#define LCD_RW	PB1
#define LCD_E	PB0
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init() ;
void LCD_clear();
void LCD_gotoxy(unsigned char x, unsigned char y);
void LCD_print(const char *str); 

#endif /* LCD_H_ */