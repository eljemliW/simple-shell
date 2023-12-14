#include "shell.h"

/**
 * add_nod - adds a node to the start of the list
 * @headp: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list *add_nod(list **headp, const char *string, int number)
{
	list *n_head;

	if (!headp)
		return (NULL);
	n_head = malloc(sizeof(list));
	if (!n_head)
		return (NULL);
	_memoryset((void *)n_head, 0, sizeof(list));
	n_head->number = number;
	if (string)
	{
		n_head->string = _stringdup(string);
		if (!n_head->string)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->nxt = *headp;
	*headp = n_head;
	return (n_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @headp: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list *add_node_end(list **headp, const char *string, int number)
{
	list *n_nod, *nod;

	if (!headp)
		return (NULL);

	nod = *headp;
	n_nod = malloc(sizeof(list));
	if (!n_nod)
		return (NULL);
	_memoryset((void *)n_nod, 0, sizeof(list));
	n_nod->number = number;
	if (string)
	{
		n_nod->string = _stringdup(string);
		if (!n_nod->string)
		{
			free(n_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->nxt)
			nod = nod->nxt;
		nod->nxt = n_nod;
	}
	else
		*headp = n_nod;
	return (n_nod);
}

/**
 * print_list_str - prints only the str element of a list linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list *p)
{
	size_t n = 0;

	while (p)
	{
		_putstr(p->string ? p->string : "(nil)");
		_putstr("\n");
		p = p->nxt;
		n++;
	}
	return (n);
}

/**
 * delete_node_at_index - deletes node at given index
 * @headp: address of pointer to first node
 * @indexnod: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list **headp, unsigned int indexnod)
{
	list *nod, *prev_nod;
	unsigned int n = 0;

	if (!headp || !*headp)
		return (0);

	if (!indexnod)
	{
		nod = *headp;
		*headp = (*headp)->nxt;
		free(nod->string);
		free(nod);
		return (1);
	}
	nod = *headp;
	while (nod)
	{
		if (n == indexnod)
		{
			prev_nod->nxt = nod->nxt;
			free(nod->string);
			free(nod);
			return (1);
		}
		n++;
		prev_nod = nod;
		nod = nod->nxt;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_p: address of pointer to head node
 *
 * Return: void
 */
void free_list(list **head_p)
{
	list *nod, *next_nod, *headp;

	if (!head_p || !*head_p)
		return;
	headp = *head_p;
	nod = headp;
	while (nod)
	{
		next_nod = nod->nxt;
		free(nod->string);
		free(nod);
		nod = next_nod;
	}
	*head_p = NULL;
}
