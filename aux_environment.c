#include "main.h"

/**
 * _ssenv - Function that  prints the current environment.
 * @vars: Struct variable contains arguments.
 *
 * Return: Always 0
 */
int _ssenv(var_s *vars)
{
	print_ls(vars->env);

	return (0);
}

/**
 * _getenv - Function that will print the value of environmental variable.
 * @vars: Struct variable contains arguements.
 * @name: environmental variable name.
 *
 * Return: value of environ.
 */
char *_getenv(var_s *vars, const char *name)
{
	list_s *node = vars->env;
	char *b;

	while (node)
	{
		b = begin_at(node->str, name);
		if (b && *b)
			return (b);
		node = node->next;
	}

	return (NULL);
}

/**
 * _sssetenv - Function that will print an Initialized  environment
 * variable that is new.
 * @vars: Struct variable  contains arguments.
 *
 *  Return: Nothing 0.
 */
int _sssetenv(var_s *vars)
{
	if (vars->argc != 3)
	{
		_post("Invalid number of arguements\n");
		return (1);
	}
	if (_setenv(vars, vars->argv[1], vars->argv[2]))
		return (0);

	return (1);
}

/**
 * _ssunsetenv - Function to unset an environment variable.
 * @vars: struct variable contains arguments.
 *
 * Return: Nothing 0.
 */
int _ssunsetenv(var_s *vars)
{
	int x;

	if (vars->argc == 1)
	{
		_post("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= vars->argc; x++)
		_unsetenv(vars, vars->argv[x]);

	return (0);
}

/**
 * load_envl - Function that will load env list.
 * @vars: struct variable contains arguments.
 *
 * Return: Nothing 0.
 */
int load_envl(var_s *vars)
{
	list_s *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_end(&node, environ[x], 0);
	vars->env = node;

	return (0);
}



