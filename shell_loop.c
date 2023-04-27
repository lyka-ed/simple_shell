#include "main.h"

/**
 * sh_file - This function acts as the main simple shell loop.
 * @vars: struct variables that contins arguement.
 * @av: argument vector.
 *
 * Return: 0 if sucessful or 1 if failed.
 */
int sh_file(var_s *vars, char **av)
{
	ssize_t x = 0;
	int builtin_ate = 0;

	while (x != -1 && builtin_ate != -2)
	{
		erase_var(vars);
		if (responsive(vars))
			_puts("$ ");
		_postchar(BUF_FLUSH);
		x = get_input(vars);
		if (x != -1)
		{
			fix_var(vars, av);
			builtin_ate = get_builtin(vars);
			if (builtin_ate == -1)
				get_cmd(vars);
		}
		else if (responsive(vars))
			_putchar('\n');
		free_var(vars, 0);
	}
	write_hist(vars);
	free_var(vars, 1);
	if (!responsive(vars) && vars->status)
		exit(vars->status);
	if (builtin_ate == -2)
	{
		if (vars->err_num == -1)
			exit(vars->status);
		exit(vars->err_num);
	}

	return (builtin_ate);
}

/**
 * get_builtin -Function that will print a builtin command that is found.
 * @vars: struct variable.
 *
 * Return: -1 if builtin is not found or 0 if builtin executed successfull
 * 1 if builtin is found but ain't successfully processed.
 */
int get_builtin(var_s *vars)
{
	int x, built_in_ate = -1;
	builtin_s builtins[] = {
		{"exit", _ssexit},
		{"env", _ssenv},
		{"help", _sshelp},
		{"history", _sshistory},
		{"setenv", _sssetenv},
		{"unsetenv", _ssunsetenv},
		{"cd", _sscd},
		{"alias", _ssalias},
		{NULL, NULL}
	};

	for (x = 0; builtins[x].type; x++)
		if (_strcmp(vars->argv[0], builtins[x].type) == 0)
		{
			vars->l_count++;
			built_in_ate = builtins[x].f(vars);
			break;
		}

	return (built_in_ate);
}

/**
 * get_cmd - Function that will locate a command line.
 * @vars: struct variable that contains arguement.
 *
 * Return: void.
 */
void get_cmd(var_s *vars)
{
	char *path = NULL;
	int x, z;

	vars->path = vars->argv[0];
	if (vars->l_count_flag == 1)
	{
		vars->l_count++;
		vars->l_count_flag = 0;
	}
	for (x = 0, z = 0; vars->arg[x]; x++)
		if (!is_token(vars->arg[x], " \t\n"))
			z++;
	if (!z)
		return;

	path = path_access(vars, _getenv(vars, "PATH="), vars->argv[0]);
	if (path)
	{
		vars->path = path;
		fork_cmd(vars);
	}
	else
	{
		if ((responsive(vars) || _getenv(vars, "PATH=")
					|| vars->argv[0][0] == '/') && syn_cmd(vars, vars->argv[0]))
			fork_cmd(vars);
		else if (*(vars->arg) != '\n')
		{
			vars->status = 127;
			get_error(vars, "Not found\n");
		}
	}
}

/**
 * fork_cmd - Function to fork an implemented file so as to run a command line.
 * @vars: struct variable that contains arguement.
 *
 * Return: void.
 */
void fork_cmd(var_s *vars)
{
	pid_t child_file;

	child_file = fork();
	if (child_file == -1)
	{
		/* TODO: ENTER ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (child_file == 0)
	{
		if (execve(vars->path, vars->argv, get_envn(vars)) == -1)
		{
			free_var(vars, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: ENTER ERROR FUNCTION */
	}
	else
	{
		wait(&(vars->status));
		if (WIFEXITED(vars->status))
		{
			vars->status = WEXITSTATUS(vars->status);
			if (vars->status == 126)
				get_error(vars, "Permission denied\n");
		}
	}
}

