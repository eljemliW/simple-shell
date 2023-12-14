#include "shell.h"

/**
 * **stringtow - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @delimeter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stringtow(char *string, char *delimeter)
{
	int n, m, l, p, numwords = 0;
	char **str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (n = 0; string[n] != '\0'; n++)
		if (!is_delimeter(string[n], delimeter) && (is_delimeter(string[n + 1], delimeter) || !string[n + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	str = malloc((1 + numwords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (n = 0, m = 0; m < numwords; m++)
	{
		while (is_delimeter(string[n], delimeter))
			n++;
		l = 0;
		while (!is_delimeter(string[n + l], delimeter) && string[n + l])
			l++;
		str[m] = malloc((l + 1) * sizeof(char));
		if (!str[m])
		{
			for (l = 0; l < m; l++)
				free(str[l]);
			free(str);
			return (NULL);
		}
		for (p = 0; p < l; p++)
			str[m][p] = string[n++];
		str[m][p] = 0;
	}
	str[m] = NULL;
	return (str);
}

/**
 * **stringtow2 - splits a string into words
 * @string: the input string
 * @delimeter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stringtow2(char *string, char delimeter)
{
	int n, m, l, p, numwords = 0;
	char **str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (n = 0; string[n] != '\0'; n++)
		if ((string[n] != delimeter && string[n + 1] == delimeter) ||
		    (string[n] != delimeter && !string[n + 1]) || string[n + 1] == delimeter)
			numwords++;
	if (numwords == 0)
		return (NULL);
	str = malloc((1 + numwords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (n = 0, m = 0; m < numwords; m++)
	{
		while (string[n] == delimeter && string[n] != delimeter)
			n++;
		l = 0;
		while (string[n + l] != delimeter && string[n + l] && string[n + l] != delimeter)
			l++;
		str[m] = malloc((l + 1) * sizeof(char));
		if (!str[m])
		{
			for (l = 0; l < m; l++)
				free(str[l]);
			free(str);
			return (NULL);
		}
		for (p = 0; p < l; p++)
			str[m][p] = string[n++];
		str[m][p] = 0;
	}
	str[m] = NULL;
	return (str);
}
