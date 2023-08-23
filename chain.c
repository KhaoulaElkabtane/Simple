#include "shell.h"


/**
 * my_chain - test if current char in buffer is a chain delimeter
 * @info: struct
 * @buffer: character of buffer
 * @position: the position in buffer
 * Return: 1 if true or 0 if false
*/
int my_chain(info_t *info, char *buffer, size_t *position)
{
	size_t i = *position;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = i;
	return (1);
}

/**
 * chain_ck - checks we should continue chaining based
 * @info: struct
 * @buffer: character of buffer
 * @position: the position in buffer
 * @i: variable for start position in buffer
 * @lgt: length of buffer
 * Return: Nothing
*/
void chain_ck(info_t *info, char *buffer, size_t *position,
		size_t i, size_t lgt)
{
	size_t p = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			p = lgt;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			p = lgt;
		}
	}
	*position = p;
}

/**
 * _realias - replacing alias in the string
 * @info: struct
 * Return: 1 if true or 0 if not
*/
int _realias(info_t *info)
{
	int i;
	list_t *nd;
	char *replace;

	for (i = 0; i < 10; i++)
	{
		nd = _nstart(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
	free(info->argv[0]);
	replace = _strcharacter(nd->str, '=');
	if (!replace)
		return (0);
	replace = _strduplication(replace + 1);
	if (!replace)
		return (0);
	info->argv[0] = replace;
	}
	return (1);
}

/**
 * var_replacing - replacing variable in the string
 * @info: struct
 * Return: 1 if true or 0 if not
*/
int var_replacing(info_t *info)
{
	int i = 0;
	list_t *nd;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcomparison(info->argv[i], "$?"))
		{
			str_replacing(&(info->argv[i]),
					_strduplication(str_convertion(getpid(), 10, 0)));
			continue;
		}
		nd = _nstart(info->env, &info->argv[i][1], '=');
		if (nd)
		{
			str_replacing(&(info->argv[i]),
					_strduplication(_strcharacter(nd->str, '=') + 1));
			continue;
		}
		str_replacing(&info->argv[i], _strduplication(""));
	}
	return (0);
}

/**
 * str_replacing - replacing string
 * @str_old: old variable string
 * @str_new: new variable string
 * Return: 1 if true or 0 if not
*/
int str_replacing(char **str_old, char *str_new)
{
	free(*str_old);
	*str_old = str_new;
	return (1);
}

