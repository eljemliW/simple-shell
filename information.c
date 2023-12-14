#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @inf: struct address
 */
void clear_info(info *inf)
{
	inf->argstr = NULL;
	inf->argarr = NULL;
	inf->strpath = NULL;
	inf->argcount = 0;
}

/**
 * set_info - initializes info_t struct
 * @inf: struct address
 * @avector: argument vector
 */
void set_info(info *inf, char **avector)
{
	int n = 0;

	inf->filname = avector[0];
	if (inf->argstr)
	{
		inf->argarr = stringtow(inf->argstr, " \t");
		if (!inf->argarr)
		{

			inf->argarr = malloc(sizeof(char *) * 2);
			if (inf->argarr)
			{
				inf->argarr[0] = _stringdup(inf->argstr);
				inf->argarr[1] = NULL;
			}
		}
		for (n = 0; inf->argarr && inf->argarr[n]; n++)
			;
		inf->argcount = n;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing al fields
 */
void free_info(info *inf, int al)
{
	free(inf->argarr);
	inf->argarr = NULL;
	inf->strpath = NULL;
	if (al)
	{
		if (!inf->comand_buf)
			free(inf->argstr);
		if (inf->environ)
			free_list(&(inf->environ));
		if (inf->historyn)
			free_list(&(inf->historyn));
		if (inf->aliasn)
			free_list(&(inf->aliasn));
		cfree(inf->environmnt);
			inf->environmnt = NULL;
		afree((void **)inf->comand_buf);
		if (inf->readfdinput > 2)
			close(inf->readfdinput);
		_putcharacter(BUF_FLUSH);
	}
}

