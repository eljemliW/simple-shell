#include "shell.h"

/**
 * _stringcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_stringcpy(char *destination, char *source)
{
	int n = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[n])
	{
		destination[n] = source[n];
		n++;
	}
	destination[n] = 0;
	return (destination);
}

/**
 * _stringdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_stringdup(const char *string)
{
	int len = 0;
	char *rt;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	rt = malloc(sizeof(char) * (len + 1));
	if (!rt)
		return (NULL);
	for (len++; len--;)
		rt[len] = *--string;
	return (rt);
}

/**
 *_putstr - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _putstr(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_putcharacter(string[n]);
		n++;
	}
}

/**
 * _putcharacter - writes the character c to stdout
 * @car: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putcharacter(char car)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (car != BUF_FLUSH)
		buffer[n++] = car;
	return (1);
}
