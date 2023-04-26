#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * *_memset - Write a function that set the memory by a constant.
 * @s: pointer to access memory.
 * @b: access byte for *s.
 * @n: byte size.
 *
 * Return: pointer to access memory.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;

	return (s);
}

/**
 * s_free - Write a function that enable string of strings to be free.
 * @ss: string of strings.
 *
 * Return: Nothin 0.
 */
void s_free(char **ss)
{
	char **h = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);

	free(h);
}

/**
 * _realloc_shell - Write a function that reallocates memory block.
 * @pt: pointer that will access old allocated memory.
 * @old_v: size of old block.
 * @new_v: size of new block.
 *
 * Return: pointer that accessed the old block.
 */
void *_realloc_shell(void *pt, unsigned int old_v, unsigned int new_v)
{
	char *b;

	if (!pt)
		return (malloc(new_v));
	if (!new_v)
		return (free(pt), NULL);
	if (new_v == old_v)
		return (pt);

	b = malloc(new_v);
	if (!b)
		return (NULL);

	old_v = old_v < new_v ? old_v : new_v;
	while (old_v--)
		b[old_v] = ((char *)pt)[old_v];
	free(pt);
	return (b);
}
