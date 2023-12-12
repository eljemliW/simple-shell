#include "shell.h"

/**
 * list_len - determines length of linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list *p)
{
	size_t n = 0;

	while (p)
	{
		p = p->nxt;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @headp: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list *headp)
{
	list *nod = headp;
	size_t n = list_len(headp), m;
	char **strstring;
	char *string;

	if (!headp || !n)
		return (NULL);
	strstring = malloc(sizeof(char *) * (n + 1));
	if (!strstring)
		return (NULL);
	for (n = 0; nod; nod = nod->nxt, n++)
	{
		string = malloc(_strlenght(nod->string) + 1);
		if (!string)
		{
			for (m = 0; m < n; m++)
				free(strstring[m]);
			free(strstring);
			return (NULL);
		}

		string = _stringcpy(string, nod->string);
		strstring[n] = string;
	}
	strstring[n] = NULL;
	return (strstring);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list *p)
{
	size_t n = 0;

	while (p)
	{
		_putstr(convert_num(p->number, 10, 0));
		_putcharacter(':');
		_putcharacter(' ');
		_putstr(p->string ? p->string : "(nil)");
		_putstr("\n");
		p = p->nxt;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @prefixstr: string to match
 * @car: the next character after prefix to match
 *
 * Return: match node or null
 */
list *node_starts_with(list *nod, char *prefixstr, char car)
{
	char *ptr = NULL;

	while (nod)
	{
		ptr = _begin_with(nod->string, prefixstr);
		if (ptr && ((car == -1) || (*ptr == car)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @headp: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list *headp, list *nod)
{
	size_t n = 0;

	while (headp)
	{
		if (headp == nod)
			return (n);
		headp = headp->nxt;
		n++;
	}
	return (-1);
}
