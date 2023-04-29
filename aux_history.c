#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/**
 * fetch_history - gets the history file
 * @vars: parameter struct
 *
 * Return: allocated string containg history file
 */

char *fetch_history(var_s *vars)
{
	char *buf, *dir;

	dir = _getenv(vars, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @vars: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(var_s *vars)
{
	ssize_t fl;
	char *filename = fetch_history(vars);
	list_s *node = NULL;

	if (!filename)
		return (-1);

	fl = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fl == -1)
		return (-1);
	for (node = vars->history; node; node = node->next)
	{
		_puts(node->str, fl);
		_puts('\n', fl);
	}
	_puts(BUF_FLUSH, fl);
	close(fl);
	return (1);
}

/**
 * read_hist - Write a function that reads history from file.
 * @vars: the parameter struct.
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(var_s *vars)
{
	int x, last = 0, linecount = 0;
	ssize_t fl, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = fetch_history(vars);

	if (!filename)
		return (0);

	fl = open(filename, O_RDONLY);
	free(filename);
	if (fl == -1)
		return (0);
	if (!fstat(fl, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fl, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fl);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_hlist(vars, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_hlist(vars, buf + last, linecount++);
	free(buf);
	vars->hist_count = linecount;
	while (vars->hist_count-- >= HIST_MAX)
		del_node(&(vars->history), 0);
	num_history(vars);
	return (vars->hist_count);
}

/**
 * build_hist - A function that adds entry to a history linked list
 * @vars: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @l_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hlist(var_s *vars, char *buf, int l_count)
{
	list_s *node = NULL;

	if (vars->history)
		node = vars->history;
	add_node(&node, buf, l_count);

	if (!vars->history)
		vars->history = node;
	return (0);
}

/**
 * num_history - renumbers the history linked list after changes
 * @vars: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int num_history(var_s *vars)
{
	list_s *node = vars->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (vars->hist_count = x);
}
