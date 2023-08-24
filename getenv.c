#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: environ value
 */
char **getEnv(infocmd *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int unsetEnv(infocmd *info, char *v)
{
	liststr *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = startsWith(node->s, v);
		if (p && *p == '=')
		{
			info->env_changed = delNodeIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int setEnv(infocmd *info, char *v, char *val)
{
	char *buffer = NULL;
	liststr *node;
	char *p;

	if (!v || !val)
		return (0);

	buffer = malloc(strlength(v) + strlength(val) + 2);
	if (!buffer)
		return (1);
	strcopy(buffer, v);
	strCat(buffer, "=");
	strCat(buffer, val);
	node = info->env;
	while (node)
	{
		p = startsWith(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addEndNode(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
