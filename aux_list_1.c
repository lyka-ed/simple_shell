#include "main.h"

/**
 * add_node - Function that will add  node to beginning of list.
 * @head: address to access pointer to head.
 * @str: string character.
 * @num: number of node.
 *
 * Return: lists size.
 */
list_s *add_node(list_s **head, const char *str, int num)
{
	list_s *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_s));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_s));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;

	return (new_h);
}

/**
 * add_end - Function that will add a node at end of list.
 * @head: address to access pointer to head.
 * @str: string character.
 * @num: node number.
 *
 * Return: lists size.
 */
list_s *add_end(list_s **head, const char *str, int num)
{
	list_s *new_n, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_n = malloc(sizeof(list_s));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_s));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*head = new_n;

	return (new_n);
}

/**
 * print_ls - Function that will prints only the string character of a list_s.
 * @a: pointer to access node.
 *
 * Return: size of list
 */
size_t print_ls(const list_s *a)
{
	size_t x = 0;

	while (a)
	{
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		x++;
	}

	return (x);
}

/**
 * del_node - Function that will deletes nodes.
 * @head: address to access pointer  node.
 * @index: index deletet node.
 *
 * Return: 1 if successful or 0 if fail.
 */
int del_node(list_s **head, unsigned int index)
{
	list_s *node, *former_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			former_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		former_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_lists -  Function that will free nodes of list.
 * @head_pt: address to access pointer to node.
 *
 * Return:  void.
 */
void free_lists(list_s **head_pt)
{
	list_s *node, *next_n, *head;

	if (!head_pt || !*head_pt)
		return;
	head = *head_pt;
	node = head;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}

	*head_pt = NULL;
}
