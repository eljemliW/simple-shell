#include "shell.h"

/**
 * main - entry point
 * @acount: arg count
 * @avector: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int acount, char **avector)
{
	info inf[] = { INFO_INIT };
	int filed = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filed)
		: "r" (filed));

	if (acount == 2)
	{
		filed = open(avector[1], O_RDONLY);
		if (filed == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avector[0]);
				_eputs(": 0: Can't open ");
				_eputs(avector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfdinput = filed;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, avector);
	return (EXIT_SUCCESS);
}

