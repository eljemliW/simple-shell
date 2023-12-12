#include "shell.h"

/**
 * _erratoint - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoint(char *str)
{
	int n = 0;
	unsigned long int rslt = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (n = 0;  str[n] != '\0'; n++)
	{
		if (str[n] >= '0' && str[n] <= '9')
		{
			rslt *= 10;
			rslt += (str[n] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * print_errormess - prints an error message
 * @inf: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_errormess(info_t *inf, char *errstr)
{
	_eputs(inf->filname);
	_eputs(": ");
	print_decimal(inf->line_counter, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argarr[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @filed: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int filed)
{
	int (*__putchar)(char) = _putchar;
	int n, counter = 0;
	unsigned int _abs_, curent;

	if (filed == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	curent = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + curent / n);
			counter++;
		}
		curent %= n;
	}
	__putchar('0' + curent);
	counter++;

	return (counter);
}

/**
 * convert_num - converter function, a clone of itoa
 * @number: number
 * @b: base
 * @fl: argument flags
 *
 * Return: string
 */
char *convert_num(long int number, int b, int fl)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *p;
	unsigned long i = number;

	if (!(fl & CONVERT_UNSIGNED) && number < 0)
	{
		i = -number;
		sign = '-';

	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * remove_cmnts - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_cmnts(char *buffer)
{
	int n;

	for (n = 0; buffer[n] != '\0'; n++)
		if (buffer[n] == '#' && (!n || buffer[n - 1] == ' '))
		{
			buffer[n] = '\0';
			break;
		}
}
