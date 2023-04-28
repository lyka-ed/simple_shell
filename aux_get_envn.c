#include "main.h"

/**
 * get_envn - Function that will returns string array of environment variable.
 * @vars: struct variable contains arguments.
 *
 * Return: Nothing 0.
 */
char **get_envn(var_s *vars)
{
	if (!vars->environ || vars->env_change)
	{
		vars->environ = list_strings(vars->env);
		vars->env_change = 0;
	}

	return (vars->environ);
}

/**
 * _unsetenv - Function that will print a deletedenvironment variable.
 * @vars: struct variable contains arguments.
 * @stg: string character for environment.
 *
 * Return: 1 on delete or 0.
 */
int _unsetenv(var_s *vars, char *stg)
{
	list_s *node = vars->env;
	size_t x = 0;
	char *b;

	if (!node || !stg)
		return (0);

	while (node)
	{
		b = begin_at(node->str, stg);
		if (b && *b == '=')
		{
			vars->env_change = del_node(&(vars->env), x);
			x = 0;
			node = vars->env;
			continue;
		}
		node = node->next;
		x++;
	}

	return (vars->env_change);
}

/**
 * _setenv - Function that will initialize a new environment variable.
 * @vars:struct contains arguments.
 * @stg: string character in environment.
 * @value: string value in environment.
 *
 *  Return: Nothing 0.
 */
int _setenv(var_s *vars, char *stg, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *b;

	if (!stg || !value)
		return (0);

	buf = malloc(_strlen(stg) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, stg);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = vars->env;
	while (node)
	{
		b = begin_at(node->str, stg);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buf;
			vars->env_change = 1;
			return (0);
		}
		node = node->next;
	}
	add_end(&(vars->env), buf, 0);
	free(buf);
	vars->env_change =  1;

	return (0);
}



