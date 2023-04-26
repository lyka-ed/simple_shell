#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/**
 * **strtow - Function that will print strings splited into words
 * repeated delimiters ignored.
 * @str: string character.
 * @del: delimeter string.
 *
 * Return: pointer to access array of string character or NULL if fail.
 */
char **strtow(char *str, char *del)
{
	int x, y, z, w, num_w = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (is_delimeter(str[x], del) && (is_delimeter(str[x + 1],
						del) || !str[x + 1]))
			num_w++;

	if (num_w == 0)
		return (NULL);
	s = malloc((1 + num_w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_w; y++)
	{
		while (is_delimeter(str[x], del))
			x++;
		z = 0;
		while (!is_delimeter(str[x + z], del) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < z; w++)
			s[y][w] = str[x++];
		s[y][w] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow_d - Function that helps split a string words.
 * @str: string character.
 * @del: delimeter string.
 *
 * Return: pointer to access array of strings or Nothing 0 (NULL).
 */
char **strtow_d(char *str, char del)
{
	int x, y, z, w, num_w = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != del && str[x + 1] == del) ||
		    (str[x] != del && !str[x + 1]) || str[x + 1] == del)
			num_w++;
	if (num_w == 0)
		return (NULL);
	s = malloc((1 + num_w) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, y = 0; y < num_w; y++)
	{
		while (str[x] == del && str[x] != del)
			x++;
		z = 0;
		while (str[x + z] != del && str[x + z] && str[x + z] != del)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < z; w++)
			s[y][w] = str[x++];
		s[y][w] = 0;
	}
	s[y] = NULL;
	return (s);
}
