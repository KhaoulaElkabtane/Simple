#include "shell.h"

/**
 * bfree - frees a pointer
 * @p: pointer to free
 *
 * Return: 1 if ok, 0 if not.
 */
int freemem(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
