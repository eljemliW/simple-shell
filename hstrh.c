#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @avector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info *inf, char **avector)
{
	ssize_t u = 0;
	int built_ret = 0;

	while (u != -1 && built_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_putstr("$ ");
		_eputchar(BUF_FLUSH);
		u = get_input(inf);
		if (u != -1)
		{
			set_info(inf, avector);
			built_ret = find_builtin(inf);
			if (built_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putcharacter('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->statusn)
		exit(inf->statusn);
	if (built_ret == -2)
	{
		if (inf->err_number == -1)
			exit(inf->statusn);
		exit(inf->err_number);
	}
	return (built_ret);
}

/**
 * find_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info *inf)
{
	int n, built_ret = -1;
	builtin_t builtintable[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintable[n].type; n++)
		if (_stringcmp(inf->argarr[0], builtintable[i].type) == 0)
		{
			inf->line_counter++;
			built_ret = builtintable[i].func(inf);
			break;
		}
	return (built_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info *inf)
{
	char *pa = NULL;
	int n, l;

	inf->pa = inf->argarr[0];
	if (inf->linecount_f == 1)
	{
		inf->line_counter++;
		inf->linecount_f = 0;
	}
	for (n = 0, l = 0; inf->argstr[n]; n++)
		if (!is_delimeter(inf->argstr[n], " \t\n"))
			l++;
	if (!l)
		return;

	pa = find_path(inf, _getenv(inf, "PATH="), inf->argarr[0]);
	if (pa)
	{
		inf->pa = pa;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argarr[0][0] == '/') && is_cmd(inf, inf->argarr[0]))
			fork_cmd(inf);
		else if (*(inf->argstr) != '\n')
		{
			inf->statusn = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info *inf)
{
	pid_t child_p;

	child_p = fork();
	if (child_p == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_p == 0)
	{
		if (execve(inf->strpath, inf->argarr, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->statusn));
		if (WIFEXITED(inf->statusn))
		{
			inf->statusn = WEXITSTATUS(inf->statusn);
			if (inf->statusn == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

