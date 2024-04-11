/*
 * LCD.h
 *
 * Created: 4/3/2024 10:40:08 AM
 *  Author: Danh Quan
 */ 


#ifndef LCD_H_
#define LCD_H_


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA_PORTC			PORTC
#define LCD_DATA_DDRC			DDRC
#define LCD_CONTROL_PORTD		PORTD
#define LCD_CONTROL_DDRD			DDRD
#define LCD_RS					PD2
#define LCD_RW					PD1
#define LCD_E					PD0

void LCD_command(unsigned char command) {
	LCD_CONTROL_PORTD &= ~(1 << LCD_RS);//RS xuong 0 de ghi lenh
	LCD_CONTROL_PORTD &= ~(1 << LCD_RW);//RW xuong 0 de ghi lenh
	_delay_ms(1);
	LCD_DATA_PORTC = command;
	LCD_CONTROL_PORTD |= (1 << LCD_E);
	_delay_ms(1);
	LCD_CONTROL_PORTD &= ~(1 << LCD_E);
	_delay_ms(3);
}

void LCD_data(unsigned char data) {
	LCD_CONTROL_PORTD |= (1 << LCD_RS); //  RS len 1 de ghi du lieu
	LCD_CONTROL_PORTD &= ~(1 << LCD_RW); //  chân RW lên 0 de ghi du lieu
	_delay_ms(1);
	LCD_DATA_PORTC = data; //gui du lieu den chan
	LCD_CONTROL_PORTD |= (1 << LCD_E); // Kich hoat chân E
	_delay_ms(1);
	LCD_CONTROL_PORTD &= ~(1 << LCD_E); // tat chan E
	_delay_ms(1);
}

void LCD_init() {
	LCD_DATA_DDRC = 0xFF; // output
	LCD_CONTROL_DDRD |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_E);
	_delay_ms(1);
	LCD_command(0x38); // 2 dong, 8 bit
	LCD_command(0x0C); // Bat hien thi chu, tat con tro
	LCD_command(0x01); //
	_delay_ms(1);
	
}

void LCD_clear() {
	LCD_command(0x01); // xoa man hinh
	_delay_ms(2);
}

void LCD_gotoxy(unsigned char x, unsigned char y) {
	unsigned char address;
	if(y != 1)
	address = 0xC0 + x - 1;
	else
	address = 0x80 + x - 1;
	LCD_command(address);
}

void LCD_print(const char *str) {
	while(*str) {
		LCD_data(*str++);
	}
}


#endif /* LCD_H_ */