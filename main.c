#include "shell.h"

/**
 * main - entry point
 * @arg: count
 * @arg1: vector
 * Return: 0 if true, 1 if false
 */
int main(int arg, char **arg1)
{
	info_t info[] = { INFO_INIT };
	int var = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (var)
			: "r" (var));
	if (arg == 2)
	{
		var = open(arg1[1], O_RDONLY);
		if (var == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				er_puts(arg1[0]);
				er_puts(": 0 : can't open");
				er_puts(arg1[1]);
				erputchar('\n');
				erputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = var;
	}
	penv_list(info);
	rhistory(info);
	shell_loop(info, arg1);
	return (EXIT_SUCCESS);
}

