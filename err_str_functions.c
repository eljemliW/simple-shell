#include "shell.h"

/**
 *_eputs - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_eputchar(string[n]);
		n++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @car: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char car)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buffer, n);
		i = 0;
	}
	if (car != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @car: The character to print
 * @filed: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char car, int filed)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(filed, buffer, n);
		n = 0;
	}
	if (car != BUF_FLUSH)
		buffer[n++] = car;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @string: the string to be printed
 * @filed: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int filed)
{
	int n = 0;

	if (!string)
		return (0);
	while (*string)
	{
		n += _putfd(*string++, filed);
	}
	return (n);
}
