#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _strlen - Function that will print length of a string character.
 * @s: string length.
 *
 * Return: integer length of string.
 */
int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;

	return (x);
}

/**
 * _strcmp - Function that will print the comparison of two string character..
 * @s1: string one.
 * @s2: string two.
 *
 * Return: if s1 < s2 return -1 or if s1 > s2 return 1
 * else if s1 == s2 return 0.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begin_at - Function that will checks if pin starts with hays.
 * @hay_s: string character.
 * @pin: substring.
 *
 * Return: address to access char or Nothing 0.
 */
char *begin_at(const char *hay_s, const char *pin)
{
	while (*pin)
		if (*pin++ != *hay_s++)
			return (NULL);

	return ((char *)hay_s);
}

/**
 * _strcat - Function to prints a concatenated two string character.
 * @dist: destination of string.
 * @rsc: source of string.
 *
 * Return: pointer to access destination buffer.
 */
char *_strcat(char *dist, char *rsc)
{
	char *ate = dist;

	while (*dist)
		dist++;
	while (*rsc)
		*dist++ = *rsc++;

	*dist = *rsc;

	return (ate);
}
