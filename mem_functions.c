#include "shell.h"

/**
 **_memoryset - fills memory with a constant byte
 *@p: the pointer to the memory area
 *@byte: the byte to fill *p with
 *@number: the amount of bytes to be filled
 *Return: (p) a pointer to the memory area p
 */
char *_memoryset(char *p, char byte, unsigned int number)
{
	unsigned int n;

	for (n = 0; n < number; n++)
		p[n] = byte;
	return (p);
}

/**
 * cfree - frees a string of strings
 * @str: string of strings
 */
void cfree(char **str)
{
	char **b = str;

	if (!str)
		return;
	while (*str)
		cfree(*str++);
	cfree(b);
}

/**
 * _realoc - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @old_sz: byte size of previous block
 * @new_sz: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realoc(void *pointer, unsigned int old_sz, unsigned int new_sz)
{
	char *ptr;

	if (!pointer)
		return (malloc(new_sz));
	if (!new_sz)
		return (cfree(pointer), NULL);
	if (new_sz == old_sz)
		return (pointer);

	p = malloc(new_sz);
	if (!ptr)
		return (NULL);

	old_sz = old_sz < new_sz ? old_sz : new_sz;
	while (old_sz--)
		p[old_sz] = ((char *)pointer)[old_sz];
	cfree(pointer);
	return (ptr);
}

