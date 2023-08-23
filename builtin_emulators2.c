#include "shell.h"

/**
 * cmd_history - displays the history list
 * @info: struct containing
 * Return: 0
*/
int cmd_history(info_t *info)
{
	_list(info->history);
	return (0);
}

/**
 * remove_alias - remove alias
 * @info: struct containing
 * @str: string alias
 * Return: 0
*/
int remove_alias(info_t *info, char *str)
{
	char *a, d;
	int i;

	a = _strcharacter(str, '=');
	if (!a)
		return (1);
	d = *a;
	*a = 0;
	i = node_index(&(info->alias),
			gnode(info->alias, _nstart(info->alias, str, -1)));
	*a = d;
	return (i);
}


/**
 * str_alias - sets alias to string
 * @info: struct containing
 * @str: string alias
 * Return: 1 if true or 0 if false
*/
int str_alias(info_t *info, char *str)
{
	char *a;

	a = _strcharacter(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (remove_alias(info, str));
	remove_alias(info, str);
	return (_nend(&(info->alias), str, 0) == NULL);
}

/**
 * p_alias - print a string alias
 * @info: variable alias
 * Return: 0
*/
int p_alias(list_t *info)
{
	char *d = NULL, *st;

	if (info)
	{
		d = _strcharacter(info->str, '=');
		for (st = info->str; st <= d; st++)
			_putchar(*st);
		_putchar('\'');
		_strputs(d + 1);
		_strputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin
 * @info: struct containing
 * Return: 0
*/
int _alias(info_t *info)
{
	int i = 0;
	char *st;
	list_t *n;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			p_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		st = _strcharacter(info->argv[i], '=');
		if (st)
			str_alias(info, info->argv[i]);
		else
			p_alias(_nstart(info->alias, info->argv[i], '='));
	}
	return (0);
}
