#include "shell.h"

/**
 * exit_fun - exit shell
 * @info: struct containing
 * Return: exits
 */
int exit_fun(info_t *info)
{
	int ex;

	if (info->arg[1])
	{
		ex = _convertsti(info->argv[1]);
		if (ex == -1)
		{
			info->status = 2;
			_fnct_error(info, "Illegal number: ");
			er_puts(info->argv[1]);
			erputchar('\n');
			return (1);
		}
		info->err_num = _convertsti(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cd_directory - charges current directory
 * @info: struct containing
 * Return: 0
 */
int cd_directory(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
	{
		_strputs("TODO: >>getcwd failure emsg here<<\n");
	}
	if (!info->argv[1])
	{
		dir = get_envirenement(info, "Home=");
		if (!dir)
			chdir_ret = chdir((dir = get_envirenement(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcomparison(info->argv[1], "-") == 0)
	{
		if (!get_envirenement(info, "OLDPWD="))
		{
			_strputs(str);
			_putchar('\n');
			return (1);
		}
		_strputs(get_envirenement(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir ((dir = get_envirenement(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_fnct_error(info, "can't cd to");
		er_puts(info->argv[1]);
		erputchar('\n');
	}
	else
	{
		new_env(info, "OLDPWD", get_envirenement(info, "PWD="));
		new_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * fnct_help - current directory of the process
 * @info: struct containing
 * Return: 0
*/
int fnct_help(info_t *info)
{
	char **ar;

	ar = info->argv;
	_strputs("help call works. Function not yet implemented \n");
	if (0)
		_strputs(*ar);
	return (0);
}
