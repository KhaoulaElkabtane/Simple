#include "shell.h"

/**
 * er_puts - prints a string
 * @c: string
 * Return: Nothing
 */
void er_puts(char *c)
{
	int i = 0;

	if (!c)
		return;
	while (c[i] != '\0')
	{
		erputchar(c[i]);
		i++;
	}
}

/**
 * erputchar - writes the character str
 * @ch: charecter to print
 * Return: if true 1 or -1 if false
 */
int erputchar(char ch)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * _puts - prints a string
 * @str: string
 * @file: file discriptor
 * Return: number characters
 */
int _puts(char *str, int file)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putwrit(*str++, file);
	}
	return (i);
}

/**
 * _putwrit - writes the character ch to given file
 * @ch: character
 * @file: file discriptor
 * Return: if true 1 or -1 if false
*/
int _putwrit(char ch, int file)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}
