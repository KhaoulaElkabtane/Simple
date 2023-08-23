#include "shell.h"

/**
 * _strcopy2- for copies
 * @est: destionation to copied
 * @str: source
 * @m: characters to copied
 * Return: the concatenated string
 */
char *_strcopy2(char *est, char *str, int m)
{
	int i, j;
	char *c = est;

	i = 0;
	while (str[i] != '\0' && i < m - 1)
	{
		est[i] = str[i];
		i++;
	}
	if (i < m)
	{
		j = i;
		while (j < m)
		{
			est[j] = '\0';
			j++;
		}
	}
	return (c);
}

/**
 * _strcharacter - locates a character
 * @c: parsed
 * @m: character
 * Return: pointer to the memory area
 */
char *_strcharacter(char *c, char m)
{
	do {
		if (*c == m)
			return (c);
	} while (*c++ != '\0');
	return (NULL);
}

/**
 * _strconcatenate - concatenate 2 stringstream
 * @est: first string
 * @str: second string
 * @m: variable to used to be maximally
 * Return: concatenate string
 */
char *_strconcatenate(char *est, char *str, int m)
{
	int i, j;
	char *c = est;

	i = 0;
	j = 0;
	while (est[i] != '\0')
		i++;
	while (str[j] != '\0' && j < m)
	{
		est[i] = str[j];
		i++;
		j++;
	}
	if (j < m)
		est[i] = '\0';
	return (c);
}
