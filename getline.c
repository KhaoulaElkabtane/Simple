#include "shell.h"

/**
 * put_buffer - chained commands
 * @info : struct
 * @buffer : buffer adress
 * @var : variable
 *
 * Return: bytes read
 */
ssize_t put_buffer(info_t *info, char **buffer, size_t *var)
{
	ssize_t i = 0;
	size_t var_nd = 0;

	if (!*var)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, fnct_handler);
#if USE_GETLINE
		i = getline(buffer, &var_nd, srdin);
#else
		i = next_line(info, buffer, &var_nd);
#endif

		if (i > 0)
		{
			if ((*buffer)[i - 1] == '\n')
			{
				(*buffer)[i - 1] = '\0';
				i--;
			}
			info->linecount_flag = 1;
			_rvcomments(*buffer);
			history_list(info, *buffer, info->histcount++);
			/*if (_strcharacter(*buffer, ';'))*/
			{
				*var = i;
				info->cmd_buf = buffer;
			}
		}
	}
	return (i);
}


/**
 * input_ - get newlines
 * @info : struct
 *
 * Return: bytes read
 */
ssize_t input_(info_t *info)
{
	static char *buffer;
	static size_t i, j, l;
	ssize_t c = 0;
	char **line = &(info->arg), *g;

	_putchar(BUF_FLUSH);
	c = put_buffer(info, &buffer, &l);
	if (c == -1)
		return (-1);
	if (l)
	{
		j = i;
		g = buffer + i;
		chain_ck(info, buffer, &j, i, l);
		while (j < l)
		{
			if (my_chain(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*line = g;
		return (_strlength(g));
	}
	*line = buffer;
	return (c);
}


/**
 * readbuffer - reads buffer
 * @info : struct
 * @buffer : buffer
 * @var : size
 *
 * Return: variable type ssize_t
 */
ssize_t readbuffer(info_t *info, char *buffer, size_t *var)
{
	ssize_t sst = 0;

	if (*var)
		return (0);
	sst = read(info->readfd, buffer, READ_BUF_SIZE);
	if (sst >= 0)
	{
		*var = sst;
	}
	return (sst);
}


/**
 * next_line - gets the next line
 * @info : struct
 * @pointer : pointer of buffer
 * @siz : size of pointer buffer
 *
 * Return: variable
 */
int next_line(info_t *info, char **pointer, size_t *siz)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, lg;
	size_t j;
	ssize_t c = 0, d = 0;
	char *line = NULL, *new_line = NULL, *s;

	line = *pointer;
	if (line && siz)
		d = *siz;
	if (i == lg)
		i = lg = 0;
	c = readbuffer(info, buffer, &lg);
	if (c == -1 || (c == 0 && lg == 0))
		return (-1);
	s = _strcharacter(buffer + i, '\n');
	j = s ? 1 + (unsigned int)(s - buffer) : lg;
	new_line = _malloc(line, d, d ? d + j : j + 1);
	if (!new_line)
		return (line ? free(line), -1 : -1);
	if (d)
		_strconcatenate(new_line, buffer + i, j - i);
	else
		_strcopy2(new_line, buffer + i, j - i + 1);
	d += j - i;
	i = j;
	line = new_line;
	if (siz)
		*siz = d;
	*pointer = line;
	return (d);
}
