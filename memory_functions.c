#include "shell.h"

/**
 * _memoryfle - file memory
 * @c: memory area
 * @a: to fill *c
 * @m: to be filled
 * Return: c
 */
char *_memoryfle(char *c, char a, unsigned int m)
{
	unsigned int i;

	for (i = 0; i < m; i++)
		c[i] = a;
	return (c);
}

/**
 * _free - free a variable string
 * @var: sting variable
 * Return: Nothing
 */
void _free(char **var)
{
	char **g = var;

	if (!var)
		return;
	while (*var)
		free(*var++);
	free(g);
}

/**
 * _malloc - realloc a block
 * @p: pointer malloc
 * @var_size: for previous block
 * @var2_size: for new block
 * Return: nothing
 */
void *_malloc(void *p, unsigned int var_size, unsigned int var2_size)
{
	char *g;

	if (!p)
		return (malloc(var2_size));
	if (!var2_size)
		return (free(p), NULL);
	if (var2_size == var_size)
		return (p);

	g = malloc(var2_size);
	if (!p)
		return (NULL);
	var_size = var_size < var2_size ? var_size : var2_size;
	while (var_size--)
		g[var_size] = ((char *)p)[var_size];
	free(p);
	return (g);
}
