#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * list_length - Write a function that determines that length of linked list.
 * @p: Show pointer of the first node.
 * Return: size of list.
 */
size_t list_length(const list_s *p)
{
	size_t x = 0;

	while (p)
	{
		p = p->next;
		x++;
	}
	return (x);
}

/**
 * list_strings - Write a function that shows of arrays of strings from a list.
 * @p: Show pointer of the first node.
 * Return: array of strings.
 */
char **list_strings(list_s *p)
{
	list_s *node = p;
	size_t x = list_length(p), y;
	char **strs;
	char *str;

	if (!p || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list -A function that prints all elements of a list_t linked list.
 * @p: Show pointer of the first node.
 * Return: size of list.
 */
size_t print_list(const list_s *p)
{
	size_t x = 0;

	while (p)
	{
		_puts(trans_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		x++;
	}
	return (x);
}

/**
 * node_begins_at - A function to returns node whose string starts with prefix.
 * @node: node to the string.
 * @prefix: string to match.
 * @c: the next character after prefix to match.
 * Return: match node or null.
 */
list_s *node_begins_at(list_s *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begin_at(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node - Write a function that gets the index of a node.
 * @p: Show pointer of the first node.
 * @node: pointer to the node.
 * Return: index of node or -1
 */
ssize_t get_node(list_s *p, list_s *node)
{
	size_t x = 0;

	while (p)
	{
		if (p == node)
			return (x);
		p = p->next;
		x++;
	}
	return (-1);
}
