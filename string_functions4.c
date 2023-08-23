#include "shell.h"

/**
 * _strwords - into words
 * @scr: string
 * @del: the delimeter
 * Return: array string or NULL
 */
char **_strwords(char *scr, char *del)
{
	int i, j, f, h, nemberwords = 0;
	char **c;

	if (scr == NULL || scr[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; scr[i] != '\0'; i++)
		if (!_strdelimeter(scr[i], del) &&
				(_strdelimeter(scr[i + 1], del)
				 || !scr[i + 1]))
			nemberwords++;

	if (nemberwords == 0)
		return (NULL);
	c = malloc((1 + nemberwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < nemberwords; j++)
	{
		while (_strdelimeter(scr[i], del))
			i++;
		f = 0;
		while (!_strdelimeter(scr[i + f], del) && scr[i + f])
			f++;
		c[j] = malloc((f + 1) * sizeof(char));
		if (!c[j])
		{
			for (f = 0; f < j; f++)
				free(c[f]);
			free(c);
			return (NULL);
		}
		for (h = 0; h < f; h++)
			c[j][h] = scr[i++];
		c[j][h] = 0;
	}
	c[j] = NULL;
	return (c);
}

/**
 * _strwords2 - into words
 * @scr: string
 * @del: the delimeter
 * Return: array string or NULL
 */
char **_strwords2(char *scr, char del)
{
	int i, j, f, h, nemberwords = 0;
	char **c;

	if (scr == NULL || scr[0] == 0)
		return (NULL);
	for (i = 0; scr[i] != '\0'; i++)
		if ((scr[i] != del && scr[i + 1] == del) ||
				(scr[i] != del && !scr[i + 1])
				|| scr[i + 1] == del)
			nemberwords++;
	if (nemberwords == 0)
		return (NULL);
	c = malloc((1 + nemberwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < nemberwords; j++)
	{
		while (scr[i] == del && scr[i] != del)
			i++;
		f = 0;
		while (scr[i + f] != del && scr[i + f] && scr[1 + f] != del)
			f++;
		c[j] = malloc((f + 1) * sizeof(char));
		if (!c[j])
		{
			for (f = 0; f < j; f++)
				free(c[f]);
			free(c);
			return (NULL);
		}
		for (h = 0; h < f; h++)
			c[j][h] = scr[i++];
		c[j][h] = 0;
	}
	c[j] = NULL;
	return (c);
}
