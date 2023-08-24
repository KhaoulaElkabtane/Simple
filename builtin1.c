#include "shell.h"

/**
 * printhistory - displays the history list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int printHistory(info *info)
{
	printList(info->history);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(infocmd *info, char *s)
{
	char *p, c;
	int ret;

	p = strFindchar(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delNodeIndex(&(info->alias),
		nodeIndex(info->alias, nodeStart(info->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(infocmd *info, char *s)
{
	char *p;

	p = strFindchar(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, s));

	unset_alias(info, s);
	return (addEndNode(&(info->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(liststr *n)
{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = strFindchar(n->s, '=');
		for (a = n->s; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		strputs(pt + 1);
		strputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * manAlias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int manAlias(infocmd *info)
{
	int i = 0;
	char *p = NULL;
	liststr *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			printAlias(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strFindchar(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStart(info->alias, info->argv[i], '='));
	}

	return (0);
}
