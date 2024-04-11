#ifndef DS18B20_H_
#define DS18B20_H_
uint8_t reset();
void writebit(uint8_t bit);
uint8_t readbit();
void writebyte(uint8_t byte);
uint8_t readbyte();
#endif /* DS18B20_H_ */