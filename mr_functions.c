#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact(info *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfdinput <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @car: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char car, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == car)
			return (1);
	return (0);
}

/**
 *_isalphabetic - checks for alphabetic character
 *@car: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphabetic(int car)
{
	if ((car >= 'a' && car <= 'z') || (car >= 'A' && car <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoint - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoint(char *str)
{
	int n, sign = 1, f = 0, output;
	unsigned int rslt = 0;

	for (n = 0;  str[n] != '\0' && f != 2; n++)
	{
		if (str[n] == '-')
			sign *= -1;

		if (str[n] >= '0' && str[n] <= '9')
		{
			f = 1;
			rslt *= 10;
			rslt += (str[n] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		output = -rslt;
	else
		output = rslt;

	return (output);
}
