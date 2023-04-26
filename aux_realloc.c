#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 **_memset - Write a function that set the memory by a costant.
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the size of byte required.
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * s_free - Write a function that enable string of strings.
 * @ss: string of strings.
 */
void s_free(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc_shell - Write a function that reallocates a block of memory.
 * @ptr: Pointer directed to the old memory allocation.
 * @old_size: byte size of old block.
 * @new_size: byte size of new block.
 * Return: pointer to da ol'block nameen.
 */
void *_realloc_shell(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
