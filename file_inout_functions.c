#include "shell.h"

/**
 * get_history_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info *inf)
{
	char *buffer, *directory;

	directory = _getenv(inf, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlenght(directory) + _strlenght(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_stringcpy(buffer, directory);
	_stringcat(buffer, "/");
	_stringcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info *inf)
{
	ssize_t filed;
	char *fname = get_history_file(inf);
	list *nod = NULL;

	if (!fname)
		return (-1);

	filed = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (filed == -1)
		return (-1);
	for (nod = inf->historyn; nod; nod = nod->nxt)
	{
		_putsfd(nod->string, filed);
		_putfd('\n', filed);
	}
	_putfd(BUF_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * read_history - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info *inf)
{
	int n, lst = 0, lecount = 0;
	ssize_t filed, rdlenght, filesize = 0;
	struct stat st;
	char *buffer = NULL, *fename = get_history_file(inf);

	if (!fename)
		return (0);

	filed = open(fename, O_RDONLY);
	free(fename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	rdlenght = read(filed, buffer, filesize);
	buffer[filesize] = 0;
	if (rdlenght <= 0)
		return (free(buffer), 0);
	close(filed);
	for (n = 0; n < filesize; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			build_history_list(inf, buffer + lst, lecount++);
			lst = n + 1;
		}
	if (lst != n)
		build_history_list(inf, buffer + lst, lecount++);
	free(buffer);
	inf->histcounter = lecount;
	while (inf->histcounter-- >= HIST_MAX)
		delete_node_at_index(&(inf->historyn), 0);
	renumber_history(inf);
	return (inf->histcounter);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lcount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info *inf, char *buffer, int lcount)
{
	list *nod = NULL;

	if (inf->historyn)
		nod = inf->historyn;
	add_node_end(&nod, buffer, lcount);

	if (!inf->historyn)
		inf->historyn = nod;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info *inf)
{
	list *nod = inf->historyn;
	int n = 0;

	while (nod)
	{
		nod->number = n++;
		nod = nod->nxt;
	}
	return (inf->histcounter = n);
}

