#include "main.h"

/**
 * _ssexit - Function that will exits simple shell.
 * @vars: struct variable.
 *
 * Return: exits shell with status code if vars.argv[0] != "exit".
 */
int _ssexit(var_s *vars)
{
	int con_exit;

	if (vars->argv[1])
	{
		con_exit = _err_ato(vars->argv[1]);
		if (con_exit == -1)
		{
			vars->status = 2;
			get_error(vars, "Invalid number: ");
			_post(vars->argv[1]);
			_postchar('\n');
			return (1);
		}
		vars->err_num = _err_ato(vars->argv[1]);
		return (-2);
	}
	vars->err_num = -1;

	return (-2);
}

/**
 * _sscd - Function that will make  changes to the current working directory.
 * @vars: struct variable that contan function arguements.
 *
 * Return: Nothing 0.
 */
int _sscd(var_s *vars)
{
	char *s, *dir, buffer[1024];
	int chdir_asap;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failed here<<\n");
	if (!vars->argv[1])
	{
		dir = _getenv(vars, "HOME=");
		if (!dir)
			chdir_asap = /* TODO: what is this? */
				chdir((dir = _getenv(vars, "PWD=")) ? dir : "/");
		else
			chdir_asap = chdir(dir);
	}
	else if (_strcmp(vars->argv[1], "-") == 0)
	{
		if (!_getenv(vars, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(vars, "OLDPWD=")), _putchar('\n');
		chdir_asap = /* TODO: what should this be? */
			chdir((dir = _getenv(vars, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_asap = chdir(vars->argv[1]);
	if (chdir_asap == -1)
	{
		get_error(vars, "Cannot cd to ");
		_post(vars->argv[1]), _postchar('\n');
	}
	else
	{
		_setenv(vars, "OLDPWD", _getenv(vars, "PWD="));
		_setenv(vars, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _sshelp - Function thatwill provide help in the current working directory.
 * @vars: Struct variable contain needed arguemenst.
 *
 * Return: Nothing 0
 */
int _sshelp(var_s *vars)
{
	char **arg_ray;

	arg_ray = vars->argv;
	_puts("Help!! Function ain't working yet. \n");
	if (0)
		_puts(*arg_ray);

	return (0);
}

