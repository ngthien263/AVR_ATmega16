#include <avr/io.h>
void int_to_string(uint8_t n, char *str)
{
	unsigned char i = 0;
	while (n!= 0)
	{
		int digit = n%10;
		str[i] = digit + '0';
		n = n /10;
		i++;
	}
	str[i] = '\0';
	unsigned char start = 0;
	unsigned char end = i - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

void float_to_string(float n, char *fstr)
{
	uint8_t int_part = (uint8_t)n;
	uint8_t decimal_part = (uint8_t)((n - int_part)*100);
	char int_str[8];
	char decimal_str[8];
	int_to_string(int_part, int_str);
	int_to_string(decimal_part, decimal_str);
	unsigned char i = 0;
	unsigned char j = 0;
	while(int_str[i] != '\0')
	{
		fstr[i] = int_str[i];
		i++;
	}
	fstr[i] = '.';
	i++;
	while(decimal_str[j] != '\0')
	{
		fstr[i] = decimal_str[j];
		i++;
		j++;
	}
}

