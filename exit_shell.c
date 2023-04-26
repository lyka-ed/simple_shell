#include "main.h"

/**
 * *_strncpy - Function that copies string character.
 * @dist: string destination that will be copied.
 * @rsc: string source.
 * @n: number of character copied.
 *
 * Return: string character thatbis concatenated.
 */
char *_strncpy(char *dist, char *rsc, int n)
{
	int x, y;
	char *s = dist;

	x = 0;

	while (rsc[x] != '\0' && x < n - 1)
	{
		dist[x] = rsc[x];
		x++;
	}

	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dist[y] = '\0';
			y++;
		}
	}

	return (s);
}

/**
 * *_strncat - Function that prints two concatenated strings.
 * @dist: destination of first string.
 * @rsc:  string source.
 * @n: number of byte used.
 *
 * Return: two concatenated strings.
 */
char *_strncat(char *dist, char *rsc, int n)
{
	int x, y;
	char *s = dist;

	x = 0;
	y = 0;

	while (dist[x] != '\0')
		x++;
	while (rsc[y] != '\0' && y < n)
	{
		dist[x] = rsc[y];
		x++;
		y++;
	}

	if (y < n)
		dist[x] = '\0';

	return (s);
}

/**
 * *_strchr - Function to print located string character.
 * @s: string to be parsed.
 * @c: character.
 *
 * Return: pointer to access memory area.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
