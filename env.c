#include "shell.h"

/**
 * _envirenement - the current envirenement
 * @info: structure containnig potentiel
 * Return: Always 0
 */
int _envirenement(info_t *info)
{
	list_str(info->env);
	return (0);
}

/**
 * get_envirenement - gets the valus for an envirenement var
 * @info: structure containnig potentiel
 * @var: variable of envirenement
 * Return: the variable
 */
char *get_envirenement(info_t *info, const char *var)
{
	list_t *n = info->env;
	char *p;

	while (n)
	{
		p = startWith(n->str, var);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * new_envirenement - intialize a new envirenement
 * @info: structure containnig potentiel
 * Return: Always 0
 */
int new_envirenement(info_t *info)
{
	if (info->argc != 3)
	{
		er_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (new_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_envirenement - remove an envirenement
 * @info: structure containnig potentiel
 * Return: Always 0
*/
int remove_envirenement(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		er_puts("Too few arguements\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rem_envirenement(info, info->argv[i]);
	return (0);
}

/**
 * penv_list - populates env list
 * @info: structure containnig potentiel
 * Return: Always 0
*/
int penv_list(info_t *info)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_nend(&n, environ[i], 0);
	info->env = n;
	return (0);
}
