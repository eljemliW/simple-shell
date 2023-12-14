#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info *inf, char *buffer, size_t *p)
{
	size_t m = *p;

	if (buffer[m] == '|' && buffer[m + 1] == '|')
	{
		buffer[m] = 0;
		m++;
		inf->comand_buf_type = CMD_OR;
	}
	else if (buffer[m] == '&' && buffer[m + 1] == '&')
	{
		buffer[m] = 0;
		m++;
		inf->comand_buf_type = CMD_AND;
	}
	else if (buffer[m] == ';') /* found end of this command */
	{
		buffer[m] = 0; /* replace semicolon with null */
		inf->comand_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buffer: the char buffer
 * @adressp: address of current position in buf
 * @n: starting position in buf
 * @lenght: length of buf
 *
 * Return: Void
 */
void check_chain(info *inf, char *buffer, size_t *adressp, size_t n, size_t lenght)
{
	size_t m = *adressp;

	if (inf->comand_buf_type == CMD_AND)
	{
		if (inf->statusn)
		{
			buffer[n] = 0;
			m = lenght;
		}
	}
	if (inf->comand_buf_type == CMD_OR)
	{
		if (!inf->statuscmd)
		{
			buffer[n] = 0;
			m = lenght;
		}
	}

	*adressp = m;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info *inf)
{
	int n;
	list *nod;
	char *ptr;

	for (n = 0; n < 10; n++)
	{
		nod = node_starts_with(inf->aliasn, inf->argarr[0], '=');
		if (!nod)
			return (0);
		free(inf->argarr[0]);
		ptr = _stringchr(nod->string, '=');
		if (!ptr)
			return (0);
		ptr = _stringdup(ptr + 1);
		if (!ptr)
			return (0);
		inf->argarr[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info *inf)
{
	int n = 0;
	list *nod;

	for (n = 0; inf->argarr[n]; n++)
	{
		if (inf->argarr[n][0] != '$' || !inf->argarr[n][1])
			continue;

		if (!_stringcmp(inf->argarr[n], "$?"))
		{
			replace_string(&(inf->argarr[n]),
				_stringdup(convert_num(inf->statusn, 10, 0)));
			continue;
		}
		if (!_stringcmp(inf->argarr[n], "$$"))
		{
			replace_string(&(inf->argarr[n]),
				_stringdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		nod = node_starts_with(inf->environ, &inf->argarr[n][1], '=');
		if (nod)
		{
			replace_string(&(inf->argarr[n]),
				_stringdup(_stringchr(nod->string, '=') + 1));
			continue;
		}
		replace_string(&inf->argarr[n], _stringdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @adressold: address of old string
 * @adressnew: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **adressold, char *adressnew)
{
	free(*adressold);
	*adressold = adressnew;
	return (1);
}

