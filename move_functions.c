#include "shell.h"

/**
 * _reactive - for interactive mode
 * @shell: struct address
 * Return: 1 interactive, 0 others
 */
int _reactive(info_t *shell)
{
	int i;

	i = isatty(STDIN_FILENO) && shell->readfd <= 2;
	return (i);
}

/**
 * _strdelimeter - checks if character is a delimeter
 * @s: variable to check
 * @strd: variable delimeter
 * Return: 1 if true or 0 if false
 */
int _strdelimeter(char s, char *strd)
{
	while (*strd)
		if (*strd++ == s)
			return (1);
	return (0);
}

/**
 * _alphabetic - alphabetic character
 * @s: character
 * Return: 1 if s alphabetic or 0 if not
 */
int _alphabetic(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s >= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _strconvert - converts a string to an integer
 * @c: variable to be converted
 * Return: 0 if no numbers converted
 */
int _strconvert(char *c)
{
	int i, sign = 1, flag = 0, p;
	unsigned int rst = 0;

	for (i = 0; c[i] != '\0' && flag != 2; i++)
	{
		if (c[i] == '-')
			sign *= -1;
		if (c[i] >= '0' && c[i] <= '9')
		{
			flag = 1;
			rst *= 10;
			rst += (c[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		p = -rst;
	else
		p = rst;
	return (p);
}
