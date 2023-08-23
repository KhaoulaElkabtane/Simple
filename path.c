#include "shell.h"

/**
 * fnct_cmd - determines if a file
 * @info: struct containing
 * @str: string
 * Return: 0
 */
int fnct_cmd(info_t *info, char *str)
{
	struct stat c;

	(void)info;
	if (!str || stat(str, &c))
		return (0);
	if (c.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fnct_dup - function for duplicate
 * @info: the path string
 * @str: variable for start
 * @stp: variable for stop
 * Return: beffer
*/
char *fnct_dup(char *info, int str, int stp)
{
	static char buffer[1024];
	int i = 0, d = 0;

	for (d = 0, i = str; i < stp; i++)
		if (info[i] != ':')
			buffer[d++] = info[i];
	buffer[d] = 0;
	return (buffer);
}

/**
 * creat_path - find this cmd in the path stirng
 * @info: struct
 * @strg: string for path
 * @dm: the dm to find
 * Return: cmd or NULL
*/
char *creat_path(info_t *info, char *strg, char *dm)
{
	int i = 0, j = 0;
	char *path;

	if (!strg)
		return (NULL);
	if ((_strlength(dm) > 2) && startWith(dm, "./"))
	{
		if (fnct_cmd(info, dm))
			return (dm);
	}
	while (1)
	{
		if (!strg[i] || strg[i] == ':')
		{
			path = fnct_dup(strg, j, i);
			if (!*path)
				strcat(path, dm);
			else
			{
				strcat(path, "/");
				strcat(path, dm);
			}
			if (fnct_cmd(info, path))
				return (path);
			if (!strg[i])
				break;
			j = i;
		}
		i++;
	}
	return (NULL);
}
