#include "shell.h"

/**
 * _strlenght - returns the length of a string
 * @strin: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlenght(char *string)
{
	int n = 0;

	if (!string)
		return (0);

	while (*string++)
		n++;
	return (n);
}

/**
 * _stringcmp - performs lexicogarphic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begin_with - checks if needle starts with haystack
 * @strsearch: string to search
 * @sub_str_find: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *begin_with(const char *strsearch, const char *sub_str_find)
{
	while (*sub_str_find)
		if (*sub_str_find++ != *strsearch++)
			return (NULL);
	return ((char *)strsearch);
}

/**
 * _stringcat - concatenates two strings
 * @dest_buf: the destination buffer
 * @src_buf: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_stringcat(char *dest_buf, char *src_buf)
{
	char *rt = dest_buf;

	while (*dest_buf)
		dest_buf++;
	while (*src_buf)
		*dest_buf++ = *src_buf++;
	*dest_buf = *src_buf;
	return (rt);
}
