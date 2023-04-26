#include "main.h"


/**
 * _sshistory -  Function that will show history lists
 * starting line number from 0 ascending order.
 * @vars: struct variable that contains arguements.
 *
 *  Return: Nothing 0
 */
int _sshistory(var_s *vars)
{
	print_list(vars->history);

	return (0);
}

/**
 * unset_ali - Function that will unsets alias to string characters.
 * @vars: struct variable.
 * @str: string character.
 *
 * Return: 0 if successful or 1 if there is an error.
 */
int unset_ali(var_s *vars, char *str)
{
	char *b, e;
	int ate;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	e = *b;
	*b = 0;
	ate = del_node(&(vars->alias), get_node(vars->alias,
				node_begin_at(vars->alias, str, -1)));
	*b = e;
	return (ate);
}

/**
 * set_ali - Function that will sets the alias to string characters.
 * @vars: struct variable.
 * @str: string character.
 *
 * Return: 0 if successful or 1 if failed.
 */
int set_ali(var_s *vars, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_ali(vars, str));

	unset_ali(vars, str);

	return (add_end(&(vars->alias), str, 0) == NULL);
}

/**
 * print_ali - Function that will print alias string.
 * @node: alias node.
 *
 * Return: ) if successful or 1 if failed.
 */
int print_ali(list_s *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * _ssalias - Function that will replicate or acts like the alias builtin.
 * @vars: struct variable.
 *
 * Return: Nothing 0.
 */
int _ssalias(var_s *vars)
{
	int x = 0;
	char *b = NULL;
	list_s *node = NULL;

	if (vars->arg == 1)
	{
		node = vars->alias;
		while (node)
		{
			print_ali(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; vars->argv[x]; x++)
	{
		b = _strchr(vars->argv[x], '=');
		if (b)
			set_ali(vars, vars->argv[x]);
		else
			print_ali(node_begin_at(vars->alias,
						vars->argv[x], '='));
	}
	return (0);
}



