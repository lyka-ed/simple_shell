#include "main.h"

/**
 * _postchar - Function that will enable writing of character c to stderr.
 * @c: character that will be entered.
 *
 * Return: 1 if successful or -1 if there is error.
 */
int _postchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}

	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _post - Function tha will prints a string character.
 * @str: string character.
 *
 * Return: Nothing 0.
 */
void _post(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_postchar(str[x]);
		x++;
	}
}

/**
 * _postfl - Function that will print character c to given fl.
 * @c: character printed.
 * @fl: file that will be written in.
 *
 * Return: 1 if successful or -1 if there is error.
 */
int _postfl(char c, int fl)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fl, buf, x);
		x = 0;
	}

	if (c != BUF_FLUSH)
		buf[x++] = c;

	return (1);
}

/**
 * _postsfl - Function that will prints an input string character.
 * @str: string character printed.
 * @fl: file to be entered.
 *
 * Return: string char number post.
 */
int _postsfl(char *str, int fl)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _postfl(*str++, fl);
	}

	return (x);
}


