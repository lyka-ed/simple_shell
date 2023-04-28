#include "main.h"

/**
 * _err_ato - Function that will print converted string to integer.
 * @p: string to be converted.
 *
 * Return: 0 if no integer in string or -1 if failed.
 */
int _err_ato(char *p)
{
	int x = 0;
	unsigned long int r_sult = 0;

	if (*p == '+')
		p++;
	for (x = 0;  p[x] != '\0'; x++)
	{
		if (p[x] >= '0' && p[x] <= '9')
		{
			r_sult *= 10;
			r_sult += (p[x] - '0');
			if (r_sult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (r_sult);
}

/**
 * get_error - Fuction that will print an error message.
 * @vars: struct variable contains arguements.
 * @e_str: string containing specified error type
 *
 * Return: 0 if no numbers  appears in string or -1 if failed.
 */
void get_error(var_s *vars, char *e_str)
{
	_post(vars->f_name);
	_post(": ");
	get_di(vars->l_count, STDERR_FILENO);
	_post(": ");
	_post(vars->argv[0]);
	_post(": ");
	_post(e_str);
}

/**
 * get_di - Function that will  print a integer in decimal form in base 10.
 * @input: input character.
 * @fl: the filedescriptor to write to
 *
 * Return: printed character numbers.
 */
int get_di(int input, int fl)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs_, current;

	if (fl == STDERR_FILENO)
		__putchar = _postchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			count++;
		}
		current %= x;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * trans_number - Function that will print converter function.
 * @num: integer value.
 * @b_rock: base character.
 * @flags: argument flags.
 *
 * Return: the converted string.
 */
char *trans_number(long int num, int b_rock, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pt;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do	{
		*--pt = array[n % b_rock];
		n /= b_rock;
	} while (n != 0);

	if (sign)
		*--pt = sign;

	return (pt);
}

/**
 * delete_comment - Function that will substitues for the
 * first instance of '#' with '\0'.
 * @buf: address access string that needs modification.
 *
 * Return: Nothing 0.
 */
void delete_comment(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
