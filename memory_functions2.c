#include "shell.h"

/**
 * _freemalloc - frees pointer and NULL adress
 * @frm: pointer to free
 * Return: 1 if free or 0
 */
int _freemalloc(void **frm)
{
	if (frm && *frm)
	{
		free(*frm);
		*frm = NULL;
		return (1);
	}
	return (0);
}
