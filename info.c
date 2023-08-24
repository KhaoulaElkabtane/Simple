#include "shell.h"

/**
 * free_info - initializes info_t struct
 * @info : struct address
 *
 * Return: Nothing
 */
void free_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * _setinis - Set initial information in the info_t struct.
 * @info: Pointer to the info_t struct to store information.
 * @ar: Array of strings containing command-line arguments.
 *
 * Return: Nothing
 */
void _setinis(info_t *info, char **ar)
{
	int i = 0;

	info->fname = ar[0];
	if (info->arg)
	{
		info->argv = _strwords(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strduplication(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		_realias(info);
		var_replacing(info);
	}
}



/**
 * lib_info - free info struct field
 * @info : struct address
 * @var : freeing fields
 *
 * Return: nothing
 */
void lib_info(info_t *info, int var)
{
	_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (var)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			l_free(&(info->env));
		if (info->history)
			l_free(&(info->history));
		if (info->alias)
			l_free(&(info->alias));
		_free(info->environ);
		info->environ = NULL;
		_freemalloc((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar (BUF_FLUSH);
	}
}
