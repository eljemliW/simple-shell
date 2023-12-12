#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @buffer: address of buffer
 * @lenght: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info *inf, char **buffer, size_t *lenght)
{
	ssize_t u = 0;
	size_t lenght_p = 0;

	if (!*lenght) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inf->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &lenght_p, stdin);
#else
		u = _getline(inf, buffer, &lenght_p);
#endif
		if (u > 0)
		{
			if ((*buffer)[u - 1] == '\n')
			{
				(*buffer)[u - 1] = '\0'; /* remove trailing newline */
				u--;
			}
			inf->linecount_fl = 1;
			remove_cmnts(*buffer);
			build_history_list(inf, *buffer, inf->histcounter++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*lenght = u;
				inf->comand_buf = buffer;
			}
		}
	}
	return (u);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info *inf)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t n, m, lenght;
	ssize_t u = 0;
	char **buffer_p = &(inf->argstr), *ptr;

	_putcharacter(BUF_FLUSH);
	u = input_buf(inf, &buffer, &lenght);
	if (u == -1) /* EOF */
		return (-1);
	if (lenght)	/* we have commands left in the chain buffer */
	{
		m = n; /* init new iterator to current buffer position */
		ptr = buffer + n; /* get pointer for return */

		check_chain(inf, buffer, &m, n, lenght);
		while (m < lenght) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buffer, &m))
				break;
			m++;
		}

		n = m + 1; /* increment past nulled ';'' */
		if (n >= lenght) /* reached end of buffer? */
		{
			n = lenght = 0; /* reset position and length */
			inf->comand_buf_type = CMD_NORM;
		}

		*buffer_p = ptr; /* pass back pointer to current command position */
		return (_strlenght(ptr)); /* return length of current command */
	}

	*buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (u); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buffer: buffer
 * @n: size
 *
 * Return: r
 */
ssize_t read_buf(info *inf, char *buffer, size_t *n)
{
	ssize_t u = 0;

	if (*n)
		return (0);
	u = read(inf->readfdinput, buffer, READ_BUF_SIZE);
	if (u >= 0)
		*n = u;
	return (u);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @p: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info *inf, char **p, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t n, len;
	size_t l;
	ssize_t u = 0, str = 0;
	char *ptr = NULL, *new_ptr = NULL, *car;

	ptr = *ptr;
	if (ptr && length)
		str = *length;
	if (n == len)
		n = len = 0;

	u = read_buf(inf, buffer, &len);
	if (u == -1 || (u == 0 && len == 0))
		return (-1);

	car = _stringchr(buffer + n, '\n');
	l = car ? 1 + (unsigned int)(car - buffer) : len;
	new_ptr = _realoc(p, str, str ? str + l : l + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (str)
		_stringncat(new_ptr, buffer + n, l - n);
	else
		_stringncpy(new_ptr, buffer + n, l - n + 1);

	str += l - n;
	n = l;
	ptr = new_ptr;

	if (length)
		*length = str;
	*ptr = ptr;
	return (str);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_number: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_number)
{
	_putstr("\n");
	_putstr("$ ");
	_putcharacter(BUF_FLUSH);
}

