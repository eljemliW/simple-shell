#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @pa: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info *inf, char *pa)
{
	struct stat state;

	(void)inf;
	if (!pa || stat(pa, &state))
		return (0);

	if (state.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstring: the PATH string
 * @begin: starting index
 * @finish: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstring, int begin, int finish)
{
	static char buffer[1024];
	int n = 0, l = 0;

	for (l = 0, n = begin; n < finish; n++)
		if (pathstring[n] != ':')
			buffer[l++] = pathstring[n];
	buffer[l] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the info struct
 * @pathstring: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info *inf, char *pathstring, char *command)
{
	int n = 0, curr_position = 0;
	char *pa;

	if (!pathstring)
		return (NULL);
	if ((_strlenght(command) > 2) && _begin_with(command, "./"))
	{
		if (is_cmd(inf, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[n] || pathstring[n] == ':')
		{
			pa = dup_chars(pathstring, curr_position, n);
			if (!*pa)
				_stringcat(pa, command);
			else
			{
				_stringcat(pa, "/");
				_stringcat(pa, command);
			}
			if (is_cmd(inf, pa))
				return (pa);
			if (!pathstring[n])
				break;
			curr_position = n;
		}
		n++;
	}
	return (NULL);
}

