#ifndef DS18B20_H
#define DS18B20_H
#define F_CPU 8000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define WIRE_PIN 0
#define CONVERT_T 0x44
#define RSCRATCHPAD 0xBE
#define WSCRATCHPAD 0x4E
#define SKIPROM 0xCC
#define LED_R 3
#define LED_Y 4
#define LED_G 5
float readTemp();
void handleLED(float wTemp);
#endif // DS18B20_H
