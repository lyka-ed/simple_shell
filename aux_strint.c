#include "main.h"

/**
 * responsive - Function that will print true when in interactive mode.
 * @vars: struct variable.
 *
 * Return: 1 if successfully activated interactive mode or 0 if failed.
 */
int responsive(var_s *vars)
{

	return (isatty(STDIN_FILENO) && vars->read_fl <= 2);

}

/**
 * is_token - Function that will checks if character is a delimeter/ token.
 * @e: character to check.
 * @delim: the delimeter string.
 *
 * Return: 1 if true or 0 if false.
 */
int is_token(char e, char *delim)
{
	while (*delim)

		if (*delim++ == e)
			return (1);

	return (0);
}

/**
 * _is_text - Function that will checks for text character.
 * @e: input character.
 *
 * Return: 1 if e is alphabet or 0 if failed.
 */
int _is_text(int e)
{
	if ((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _ato - Function to prints a converted  string to integer.
 * @s: converted string.
 *
 * Return: 0 if integer is absent in string or 1 if failed.
 */
int _ato(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

