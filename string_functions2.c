#include "shell.h"

/**
 * _strcopy - copies
 * @ds : destination
 * @sre : source
 *
 * Return: char*
 */
char *_strcopy(char *ds, char *sre)
{
	int i = 0;

	if (ds == sre || sre == 0)
		return (ds);
	ds = (char *)malloc(sizeof(char) * _strlength(sre));
	while (sre[i])
	{
		ds[i] = sre[i];
		i++;
	}
	ds[i] = '\0';
	return (ds);
}


/**
 * _strduplication - duplicates a string
 * @dpl : variable to duplicate
 *
 * Return: pointer
 */
char *_strduplication(const char *dpl)
{
	int lgh;
	char *str;

	if (!dpl)
		return (NULL);
	while (*dpl++)
		lgh++;
	str = malloc(sizeof(char) * (lgh + 1));
	if (!str)
		return (NULL);
	for (lgh++; lgh--;)
		str[lgh] = *--dpl;
	return (str);
}


/**
 * _strputs - input string
 * @put : printed
 *
 * Return: nothing
 */
void _strputs(char *put)
{
	int i = 0;

	if (!put)
		return;
	while (put[i] != '\0')
	{
		_putchar(put[i]);
		i++;
	}
}


/**
 * _putchar - writes the character d to stdout
 * @d : the character to print
 *
 * Return: on success 1
 *          On error, -1 is returned, and errno is set appropriately
 */
int _putchar(char d)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buffer[i++] = d;
	return (i);
}
