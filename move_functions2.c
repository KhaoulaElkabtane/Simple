#include "shell.h"

/**
 * _convertsti - converts string to an integer
 * @str: string to be converted
 * Return: 0 if no numbers, -1 on error
 */

int _convertsti(char *str)
{
	int i;
	unsigned long int rst;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			rst *= 10;
			rst += (str[i] - '0');
			if (rst > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rst);
}

/**
 * _fnct_error - prints an error
 * @str: parameter & return info struct
 * @error: string containing specified error type
 * Return: 0 if no numbers, -1 on error
 */
void _fnct_error(info_t *str, char *error)
{
	er_puts(str->fname);
	er_puts(": ");
	_decimal(str->line_count, STDERR_FILENO);
	er_puts(": ");
	er_puts(str->argv[0]);
	er_puts(": ");
	er_puts(error);
}

/**
 * _decimal - printd decimal number
 * @var: variable
 * @file: filedescriptor to write
 * Return: variable printed
 */
int _decimal(int var, int file)
{
	int (*_putchar) (char) = _putchar;
	int i, count = 0;
	unsigned int abc, crt;

	if (file == STDERR_FILENO)
		_putchar = erputchar;
	if (var < 0)
	{
		abc = var;
		_putchar('-');
		count++;
	}
	else
		abc = var;
	crt = abc;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abc / i)
		{
			_putchar('0' + crt / i);
			count++;
		}
		crt %= i;
	}
	_putchar('0' + crt);
	count++;
	return (count);
}

/**
 * str_convertion - converter function a clone itoa
 * @n: number
 * @variable: base
 * @flag: argument flags
 * Return: string
 */
char *str_convertion(long int n, int var, int flag)
{
	static char *array;
	static char buffer[50];
	char s;
	char *pointer;
	unsigned long m = n;

	if (!(flag & CONVERT_UNSIGNED) && n < 0)
	{
		m = -n;
		s = '-';
	}
	array = flag & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';
	do {
		*--pointer = array[m % var];
		m /= var;
	} while (m != 0);
	if (s)
		*--pointer = s;
	return (pointer);
}

/**
 * _rvcomments - replace first instance '#' with '\0'
 * @b: the string to modify
 * return: 0
 */
void _rvcomments(char *b)
{
	int i;

	for (i = 0; b[i] != '\0'; i++)
	{
		if (b[i] == '#' && (!i || b[i - 1] == ' '))
		{
			b[i] = '\0';
			break;
		}
	}
}

