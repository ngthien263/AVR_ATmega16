void int_to_string(int n, char *str)
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