#include "main.h"

/**
 * main - Function that implement entry point.
 * @ac: arguement count.
 * @av: argument vector.
 *
 * Return: 0 if successful or 1 if failed.
 */
int main(int ac, char **av)
{
	var_s vars[] = {VARS_INIT};
	int fl = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fl)
			: "r" (fl));

	if (ac == 2)
	{
		fl = open(av[1], O_RDONLY);
		if (fl == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_post(av[0]);
				_post(": 0: Can't open ");
				_post(av[1]);
				_postchar('\n');
				_postchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		vars->read_fl = fl;
	}
	load_envl(vars);
	read_hist(vars);
	sh_file(vars, av);

	return (EXIT_SUCCESS);
}

