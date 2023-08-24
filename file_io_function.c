#include "shell.h"

/**
 * history_file - gets the history file
 * @info : struct
 *
 * Return: return string history file
 */
char *history_file(info_t *info)
{
	char *buffer, *str;

	str = get_envirenement(info, "HOME=");
	if (!str)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlength(str) + _strlength(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	buffer = _strcopy(buffer, str);
	buffer = str_cat(buffer, "/");
	buffer = str_cat(buffer, HIST_FILE);
	return (buffer);
}


/**
 * creat_history - Create or overwrite a history file with command history.
 * @info: Pointer to the info_t struct containing history and file data.
 *
 * Return: 1 on success, -1 on failure.
 */
int creat_history(info_t *info)
{
	ssize_t file;
	char *f_name = history_file(info);
	list_t *nd = NULL;

	if (!f_name)
		return (-1);
	file = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (file == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_puts(nd->str, file);
		_putwrit('\n', file);
	}
	_putwrit(BUF_FLUSH, file);
	close(file);
	return (1);
}

/**
 * rhistory - reads history file
 * @info : struct
 *
 * Return: 1 if true or 0 if false
 */
int rhistory(info_t *info)
{
	int i, lt = 0, count = 0;
	ssize_t file, rd, sz = 0;
	struct stat s;
	char *buffer = NULL, *f_name = history_file(info);

	if (!f_name)
		return (0);
	file = open(f_name, O_RDONLY);
	free(f_name);
	if (file == -1)
		return (0);
	if (!fstat(file, &s))
		sz = s.st_size;
	if (sz < 2)
		return (0);
	buffer = malloc(sizeof(char) * (sz + 1));
	if (!buffer)
		return (0);
	rd = read(file, buffer, sz);
	buffer[sz] = 0;
	if (rd <= 0)
		return (free(buffer), 0);
	close(file);
	for (i = 0; i < sz; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			history_list(info, buffer + lt, count++);
			lt = i + 1;
		}
	}
	if (lt != i)
		history_list(info, buffer + lt, count++);
	free(buffer);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		node_index(&(info->history), 0);
	num_history(info);
	return (info->histcount);
}

/**
 * history_list - build entry to history list
 * @info : struct
 * @buffer : buffer
 * @coun : the history linecount
 *
 * Return: always 0
 */
int history_list(info_t *info, char *buffer, int coun)
{
	list_t *n;

	if (info->history)
		n = info->history;
	_nend(&n, buffer, coun);
	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * num_history - the history renumbers
 * @info : struct
 *
 * Return: new history count
 */
int num_history(info_t *info)
{
	list_t *n = info->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (info->histcount = i);
}
