#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info *inf)
{
	if (!inf->environmnt || inf->environ_changed)
	{
		inf->environmnt = list_to_strings(inf->environ);
		inf->environ_changed = 0;
	}

	return (inf->environmnt);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @varstrenv: the string env var property
 */
int _unsetenv(info *inf, char *varstrenv)
{
	list *nod = inf->environ;
	size_t n = 0;
	char *ptr;

	if (!nod || !varstrenv)
		return (0);

	while (nod)
	{
		ptr = _begin_with(nod->string, varstrenv);
		if (ptr && *ptr == '=')
		{
			inf->environ_changed = delete_node_at_index(&(inf->environ), n);
			n = 0;
			nod = inf->environ;
			continue;
		}
		nod = nod->nxt;
		n++;
	}
	return (inf->environ_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varstrenv: the string env var property
 * @varstrenvalue: the string env var value
 *  Return: Always 0
 */
int _setenv(info *inf, char *varstrenv, char *varstrenvalue)
{
	char *buffer = NULL;
	list *nod;
	char *ptr;

	if (!varstrenv || !varstrenvalue)
		return (0);

	buffer = malloc(_strlenght(varstrenv) + _strlenght(varstrenvalue) + 2);
	if (!buffer)
		return (1);
	_stringcpy(buffer, varstrenv);
	_stringcat(buffer, "=");
	_stringcat(buffer, varstrenvalue);
	nod = inf->environ;
	while (nod)
	{
		ptr = _begin_with(nod->string, varstrenv);
		if (ptr && *ptr == '=')
		{
			free(nod->string);
			nod->string = buffer;
			inf->environ_changed = 1;
			return (0);
		}
		nod = nod->nxt;
	}
	add_node_end(&(inf->environ), buffer, 0);
	free(buffer);
	inf->environ_changed = 1;
	return (0);
}

