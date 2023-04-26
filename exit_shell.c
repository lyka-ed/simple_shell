#include "main.h"

/**
 * *_strncpy - Function that copies string character.
 * @dest: string destination that will be copied.
 * @src: string source.
 * @n: number of character copied.
 *
 * Return: string character thatbis concatenated.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;

	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}

	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}

	return (s);
}

/**
 * *_strncat - Function that prints two concatenated strings.
 * @dest: destination of first string.
 * @src:  string source.
 * @n: number of byte used.
 *
 * Return: two concatenated strings.
 */
char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;

	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}

	if (y < n)
		dest[x] = '\0';

	return (s);
}

/**
 * *_strchr - Function to print located string character.
 * @s: string to be parsed.
 * @c: character.
 *
 * Return: pointer to access memory area.
 */
char * _strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
