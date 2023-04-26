#include "main.h"

/**
 * syn_cmd - Function that will proof that file is an executable command.
 * @vars: struct variable.
 * @path: path address to file.
 *
 * Return: if successful 1 or 0 if fail.
 */
int syn_cmd(var_s *vars, char *path)
{
	struct stat at;

	(void)vars;

	if (!path || stat(path, &at))
		return (0);
	if (at.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * syn_char - Function that will print a duplicated character.
 * @strp: string path.
 * @begin: index begin
 * @end: index end.
 *
 * Return: pointer to new buffer
 */
char *syn_char(char *strp, int begin, int end)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = begin; x < end; x++)
		if (strp[x] != ':')
			buf[y++] = strp[x];
	buf[y] = 0;

	return (buf);
}

/**
 * path_access - Function that will access cmd in path.
 * @vars: struct variable.
 * @strp: string path.
 * @cmd: command line to be found.
 *
 * Return: path address to access cmd or Nothing 0 (NULL).
 */
char *path_access(var_s *vars, char *strp, char *cmd)
{
	int x = 0, initial_p = 0;
	char *path;

	if (!strp)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_at(cmd, "./"))
	{
		if (syn_cmd(vars, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strp[x] || strp[x] == ':')
		{
			path = syn_char(strp, initial_p, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (syn_cmd(vars, path))
				return (path);
			if (!strp[x])
				break;

			initial_p = x;
		}

		x++;
	}

	return (NULL);
}

