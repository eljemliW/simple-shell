#include "shell.h"

/**
 * _myexit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info *inf)
{
	int extcheck;

	if (inf->argarr[1])  /* If there is an exit arguement */
	{
		extcheck = _erratoint(inf->argarr[1]);
		if (extcheck == -1)
		{
			inf->statuscmd = 2;
			print_errormess(inf, "Illegal number: ");
			_eputs(inf->argarr[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_number = _erratoint(inf->argarr[1]);
		return (-2);
	}
	inf->err_number = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info *inf)
{
	char *str, *direct, buff[1024];
	int chdir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_putstr("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argarr[1])
	{
		direct = _getenv(inf, "HOME=");
		if (!direct)
			chdir_ret = /* TODO: what should this be? */
				chdir((direct = _getenv(inf, "PWD=")) ? direct : "/");
		else
			chdir_ret = chdir(direct);
	}
	else if (_stringcmp(inf->argarr[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_putstr(str);
			_putcharacter('\n');
			return (1);
		}
		_putstr(_getenv(inf, "OLDPWD=")), _putcharacter('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((direct = _getenv(inf, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_ret = chdir(inf->argarr[1]);
	if (chdir_ret == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argarr[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info *inf)
{
	char **arg_arr;

	arg_arr = inf->argarr;
	_putstr("help call works. Function not yet implemented \n");
	if (0)
		_putstr(*arg_arr); /* temp att_unused workaround */
	return (0);
}
