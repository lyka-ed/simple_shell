#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * input_buffer - Function that will print buffer chained commands.
 * @vars: struct variable contains arguements.
 * @buf: address accessing buffer.
 * @len: address accessing length.
 *
 * Return: bytes.
 */
ssize_t input_buffer(var_s *vars, char **buf, size_t *len)
{
	ssize_t u = 0;
	size_t len_num = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_handle);
#if USE_GETLINE
		u = getlines(buf, &len_num, stdin);
#else
		u = _getlines(vars, buf, &len_num);
#endif
		if (u > 0)
		{
			if ((*buf)[u - 1] == '\n')
			{
				(*buf)[u - 1] = '\0';
				u--;
			}
			vars->l_count_flag = 1;
			delete_comment(*buf);
			build_hlist(vars, *buf, vars->hist_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = u;
				vars->cmd_buf = buf;
			}
		}
	}

	return (u);
}

/**
 * get_input - Function that will gets a line exempting the newline.
 * @vars: struct variable contains arguements.
 *
 * Return: bytes.
 */
ssize_t get_input(var_s  *vars)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t u = 0;
	char **buf_p = &(vars->arg), *b;

	_putchar(BUF_FLUSH);
	u = input_buffer(vars, &buf, &len);
	if (u == -1) /* EOF */
		return (-1);
	if (len)
	{
		y = x;
		b = buf + x;

		conf_chain(vars, buf, &y, x, len);
		while (y < len)
		{
			if (in_chain(vars, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0; /* position and length resetting*/
			vars->cmd_buf_types = CMD_NORM;
		}

		*buf_p = b;
		return (_strlen(b));
	}

	*buf_p = buf;

	return (u);
}

/**
 * read_b - Function that will reads into a buffer.
 * @vars: struct variable contains arguements.
 * @buf: buffer
 * @x: size of buffer
 *
 * Return: u
 */
ssize_t read_b(var_s *vars, char *buf, size_t *x)
{
	ssize_t u = 0;

	if (*x)
		return (0);
	u = read(vars->read_fl, buf, READ_BUF_SIZE);
	if (u >= 0)
		*x = u;

	return (u);
}

/**
 * _getlines - Function that will print the next line of input from STDIN.
 * @vars: struct variable contains arguement.
 * @pt: address of pointer to access buffer.
 * @length: size of pre-allocated pt buffer.
 *
 * Return: p
 */
int _getlines(var_s *vars, char **pt, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t z;
	ssize_t u = 0, p = 0;
	char *b = NULL, *new_b = NULL, *e;

	b = *pt;
	if (b && length)
		p = *length;
	if (x == len)
		x = len = 0;

	u = read_b(vars, buf, &len);
	if (u == -1 || (u == 0 && len == 0))
		return (-1);

	e = _strchr(buf + x, '\n');
	z = e ? 1 + (unsigned int)(e - buf) : len;
	new_b = (char*)_realloc(b, p, p ? p + z : z + 1);
	if (!new_b)
		return (b ? free(b), -1 : -1);
	if (p)
		_strncat(new_b, buf + x, z - x);
	else
		_strncpy(new_b, buf + x, z - x + 1);

	p += z - x;
	x = z;
	b = new_b;
	if (length)
		*length = p;
	*pt = b;

	return (p);
}

/**
 * sig_handle - Function that will print a  blocked Ctrl + C.
 * @sig_num: signal number character.
 *
 * Return: void
 */
void sig_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

