#include "shell.h"

/**
 **_stringncpy - copies a string
 *@dest_str: the destination string to be copied to
 *@src_str: the source string
 *@number: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_stringncpy(char *dest_str, char *src_str, int number)
{
	int n, m;
	char *str = dest_str;

	n = 0;
	while (src_str[n] != '\0' && n < number - 1)
	{
		dest_str[n] = src_str[n];
		n++;
	}
	if (n < number)
	{
		m = n;
		while (m < number)
		{
			dest_str[m] = '\0';
			m++;
		}
	}
	return (str);
}

/**
 **_stringncat - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@number: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_stringncat(char *destination, char *source, int number)
{
	int n, m;
	char *str = destination;

	n = 0;
	m = 0;
	while (destination[n] != '\0')
		i++;
	while (source[m] != '\0' && m < number)
	{
		destination[n] = source[m];
		n++;
		m++;
	}
	if (m < number)
		destination[n] = '\0';
	return (str);
}

/**
 **_stringchr - locates a character in a string
 *@str: the string to be parsed
 *@car: the character to look for
 *Return: (str) a pointer to the memory area s
 */
char *_stringchr(char *str, char car)
{
	do {
		if (*str == car)
			return (s);
	} while (*str++ != '\0');

	return (NULL);
}
