#include "main.h"

/**
 * is_chain - Function that will test to know if the current character
 * in a buffer is a chain token.
 * @vars: struct variable.
 * @buf: the char buffer.
 * @b: position that access the current position.
 *
 * Return: 1 if successful to  chain toke or, 0 if failed.
 */
int is_chain(var_s *vars, char *buf, size_t *b)
{
	size_t y = *b;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		vars->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		vars->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		vars->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*b = y;

	return (1);
}

/**
 * conf_chain - Fuction that will show continued chaining process based
 * on last status.
 * @vars: struct variable.
 * @buf: buffer character.
 * @b: address accessing current position in buf.
 * @x: buf beginning position.
 * @len: buf length.
 *
 * Return: Void
 */
void conf_chain(var_s *vars, char *buf, size_t *b, size_t x, size_t len)
{
	size_t y = *b;

	if (vars->cmd_buf_type == CMD_AND)
	{
		if (vars->status)
		{
			buf[x] = 0;
			y = len;
		}
	}
	if (vars->cmd_buf_type == CMD_OR)
	{
		if (!vars->status)
		{
			buf[x] = 0;
			y = len;
		}
	}

	*b = y;
}

/**
 * swap_alias - Function that will replaces an alias in the token string.
 * @vars: struct variable.
 *
 * Return: 1 if successfully replaced or  0 if failed.
 */
int swap_alias(var_s *vars)
{
	int x;
	list_s *node;
	char *b;

	for (x = 0; x < 10; x++)
	{
		node = node_begins_at(vars->alias, vars->argv[0], '=');
		if (!node)
			return (0);
		free(vars->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		vars->argv[0] = b;
	}

	return (1);
}

/**
 * swap_var - Function that willl swap vars in place of  tokenized string.
 * @vars: struct variable.
 *
 * Return: 1 if successfully swapped or 0 if failed.
 */
int swap_var(var_s *vars)
{
	int x = 0;
	list_s *node;

	for (x = 0; vars->argv[x]; x++)
	{
		if (vars->argv[x][0] != '$' || !vars->argv[x][1])
			continue;

		if (!_strcmp(vars->argv[x], "$?"))
		{
			swap_string(&(vars->argv[x]),
					_strdup(trans_number(vars->status, 10, 0)));
			continue;
		}
		if (!_strcmp(vars->argv[x], "$$"))
		{
			swap_string(&(vars->argv[x]),
					_strdup(trans_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_at(vars->env, &vars->argv[x][1], '=');
		if (node)
		{
			swap_string(&(vars->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		swap_string(&vars->argv[x], _strdup(""));

	}

	return (0);
}

/**
 * swap_string - Function will print replaced string.
 * @aged: address to access old string.
 * @new: new string.
 *
 * Return: 1 if successfully swapped or 0 failed.
 */
int swap_string(char **aged, char *new)
{
	free(*aged);
	*aged = new;

	return (1);
}

