#include "shell.h"

/**
 * _myenv - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info *inf)
{
	print_list_str(inf->environ);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @envname: env var name
 *
 * Return: the value
 */
char *_getenv(info *inf, const char *envname)
{
	list *nod = inf->environ;
	char *ptr;

	while (nod)
	{
		ptr = _begin_with(nod->string, envname);
		if (ptr && *ptr)
			return (ptr);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info *inf)
{
	if (inf->argcount != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argarr[1], inf->argarr[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info *inf)
{
	int n;

	if (inf->argcount == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= inf->argcount; n++)
		_unsetenv(inf, inf->argarr[n]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info *inf)
{
	list *nod = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&nod, environ[n], 0);
	inf->environ = nod;
	return (0);
}

