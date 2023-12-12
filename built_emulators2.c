#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info *inf)
{
	print_list(inf->historyn);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info *inf, char *string)
{
	char *ptr, car;
	int rest;

	ptr = _stringchr(string, '=');
	if (!ptr)
		return (1);
	car = *ptr;
	*ptr = 0;
	rest = delete_node_at_index(&(inf->aliasn),
		get_node_index(inf->aliasn, node_starts_with(inf->aliasn, string, -1)));
	*ptr = car;
	return (rest);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info *inf, char *string)
{
	char *ptr;

	ptr = _stringchr(string, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(inf, string));

	unset_alias(inf, string);
	return (add_node_end(&(inf->aliasn), string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nod: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list *nod)
{
	char *ptr = NULL, *b = NULL;

	if (nod)
	{
		ptr = _stringchr(nod->string, '=');
		for (b = nod->string; b <= ptr; b++)
			_putcharacter(*b);
		_putcharacter('\'');
		_putstring(ptr + 1);
		_putstring("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info *inf)
{
	int n = 0;
	char *ptr = NULL;
	list *nod = NULL;

	if (inf->argcount == 1)
	{
		nod = inf->aliasn;
		while (nod)
		{
			print_alias(nod);
			nod = nod->nxt;
		}
		return (0);
	}
	for (n = 1; inf->argarr[n]; n++)
	{
		ptr = _stringchr(inf->argarr[n], '=');
		if (ptr)
			set_alias(inf, inf->argarr[n]);
		else
			print_alias(node_starts_with(inf->aliasn, inf->argarr[n], '='));
	}

	return (0);
}

