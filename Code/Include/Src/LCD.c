#include "LCD.h"

void LCD_command(unsigned char command) {
	LCD_CONTROL_PORT &= ~(1 << LCD_RS);//RS xuong 0 de ghi lenh
	LCD_CONTROL_PORT &= ~(1 << LCD_RW);//RW xuong 0 de ghi lenh
	_delay_ms(1);
	LCD_DATA_PORT = command;
	LCD_CONTROL_PORT |= (1 << LCD_E);
	_delay_ms(1);
	LCD_CONTROL_PORT &= ~(1 << LCD_E);
	_delay_ms(3);
}

void LCD_data(unsigned char data) {
	LCD_CONTROL_PORT |= (1 << LCD_RS); //  RS len 1 de ghi du lieu
	LCD_CONTROL_PORT &= ~(1 << LCD_RW); //  chân RW lên 0 de ghi du lieu
	_delay_ms(1);
	LCD_DATA_PORT = data; //gui du lieu den chan
	LCD_CONTROL_PORT |= (1 << LCD_E); // Kich hoat chân E
	_delay_ms(1);
	LCD_CONTROL_PORT &= ~(1 << LCD_E); // tat chan 
	_delay_ms(1);
}

void LCD_init() {

	LCD_DATA_DDR = 0xFF; // output
	LCD_CONTROL_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_E);
	_delay_ms(1);
	LCD_command(0x38); // 2 dong, 8 bit
	LCD_command(0x0C); // Bat hien thi chu, tat con tro
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