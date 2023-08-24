#include "shell.h"


/**
 * _getline - Read a line from input using a buffer.
 * @info: Pointer to the info_t struct containing data.
 * @pointer: Pointer to the buffer storing the line.
 * @len: Pointer to the length of the line.
 *
 * Return: The number of characters read, or -1 on failure.
 */
int _getline(info_t *info, char **pointer, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, gh;
	size_t j;
	ssize_t str = 0, sts = 0;
	char *p = NULL, *np = NULL, *s;

	p = *pointer;
	if (p && len)
		sts = *len;
	if (i == gh)
		i = gh = 0;
	str = readbuffer(info, buffer, &gh);
	if (str == -1 || (str == 0 && gh == 0))
		return (-1);
	s = _strcharacter(buffer + 1, '\n');
	j = s ? 1 + (unsigned int)(s - buffer) : gh;
	np = _malloc(p, sts, sts ? sts + j : j + 1);
	if (!np)
		return (p ? free(p), -1 : -1);
	if (sts)
		_strconcatenate(np, buffer + i, j - 1);
	else
		_strcopy2(np, buffer + 1, j - i + 1);
	sts += j - i;
	i = j;
	p = np;
	if (len)
		*len = sts;
	*pointer = p;
	return (sts);
}

/**
 * fnct_handler - blocks ctrl-c
 * @info : the signal number
 *
 * Return: nothing
 */
void fnct_handler(__attribute__((unused))int info)
{
	_strputs("\n");
	_strputs("$ ");
	_putchar(BUF_FLUSH);
}
