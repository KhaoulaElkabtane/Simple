#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info : info struct
 * @arg : the argument from main
 *
 * Return: 0 if true or 0 if not
 */
int shell_loop(info_t *info, char **arg)
{
	ssize_t i = 0;
	int ret = 0;
	
	while (i != -1 && ret != -2)
	{
		free_info(info);
		if (_reactive(info))
			_strputs("$ ");
		erputchar(BUF_FLUSH);
		i = input_(info);
		if (i != -1)
		{
			_setinis(info, arg);
			ret = fbuil(info);
			if (ret == -1)
				path_command(info);
		}
		else if (_reactive(info))
			_putchar('\n');
		lib_info(info, 0);
	}
	creat_history(info);
	lib_info(info, 1);
	if (!_reactive(info) && info->status)
		exit(info->status);
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}


/**
 * path_command - finds a command in path
 * @info : struct
 *
 * Return: nothing
 */
void path_command(info_t *info)
{
	char *p = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
	{
		if (!_strdelimeter(info->arg[i], "\t\n"))
		{
			j++;
		}
	}
	if (!j)
		return;
	p = creat_path(info, get_envirenement(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->path = p;
		fcmd(info);
	}
	else
	{
		if ((_reactive(info) || get_envirenement(info, "PATH=") || info->argv[0][0] == '/') && fnct_cmd(info, info->argv[0]))
			fcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_fnct_error(info, "not found\n");
		}
	}
}


/**
 * fcmd - forks a an exec to run cmd
 * @info : sturct
 *
 * Return: nothing
 */
void fcmd(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		if (execve(info->path, info->argv, _environ(info)) == -1)
		{
			lib_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_fnct_error(info, "Permission denied\n");
		}
	}
}


/**
 * fbuil - finds builtin cmd
 * @info strct
 *
 * Return: variable ret
 */
int fbuil(info_t *info)
{
	int i, ret = -1;

	builtin_table buil[] = {
		{"exit", exit_fun},
		{"env", _envirenement},
		{"help", fnct_help},
		{"history", cmd_history},
		{"new envirenement", new_envirenement},
		{"cd directory", cd_directory},
		{"my alias", _alias},
		{NULL, NULL}
	};
	for (i = 0; buil[i].type; i++)
	{
		if (_strcomparison(info->argv[0], buil[i].type) == 0)
		{
			info->line_count++;
			ret = buil[i].func(info);
			break;
		}
	}
	return(ret);
}
