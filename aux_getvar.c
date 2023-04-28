#include "main.h"

/**
 * erase_var -  Function tha will initialize vars.
 * @vars: struct variable contains arguements.
 *
 * Return: Nothing..
 */
void erase_var(var_s *vars)
{
	vars->arg = NULL;
	vars->argv = NULL;
	vars->path = NULL;
	vars->argc = 0;
}

/**
 * fix_var - Function that will initialize and fix vars.
 * @vars: struct variable contains arguements.
 * @av: argument vector
 *
 * Return; Nothing 0.
 */
void fix_var(var_s *vars, char **av)
{
	int x = 0;

	vars->f_name = av[0];
	if (vars->arg)
	{
		vars->argv = strtow(vars->arg, " \t");
		if (!vars->argv)
		{
			vars->argv = malloc(sizeof(char *) * 2);
			if (vars->argv)
			{
				vars->argv[0] = _strdup(vars->arg);
				vars->argv[1] = NULL;
			}
		}
		for (x = 0; vars->argv && vars->argv[x]; x++)
			;
		vars->argc = x;

		swap_alias(vars);
		swap_var(vars);
	}
}

/**
 * free_var -  Function that will print free var_s.
 * @vars: struct variable contains arguement.
 * @full: free all fields character.
 *
 * Return: Nothing.
 */
void free_var(var_s *vars, int full)
{
	free(vars->argv);
	vars->argv = NULL;
	vars->path = NULL;

	if (full)
	{
		if (!vars->cmd_buf)
			free(vars->arg);
		if (vars->env)
			free_lists(&(vars->env));
		if (vars->history)
			free_lists(&(vars->history));
		if (vars->alias)
			free_lists(&(vars->alias));
		free(vars->environ);
			vars->environ = NULL;
		free((void **)vars->cmd_buf);
	
		if (vars->read_fl > 2)
			close(vars->read_fl);
		_putchar(BUF_FLUSH);
	}
}


