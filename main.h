#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* Pointer to access an array  to strings called the "environment" */
extern char **environ;

/* Command line */
#define CMD_NORM
#define CMD_OR
#define CMD_AND
#define CMD_CHAIN

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_s;

/**
 * struct variable - Function will have arguements to pass into a another
 * function for an organised prototype for
 * function pointer struct.
 * @arg: getline arguements.
 * @argv: strings array arg.
 * @path: path for current working  command line.
 * @argc: an argument count.
 * @l_count: line count.
 * @err_num: error number of times code for exit function.
 * @l_count_flag: if on count this line of input
 * @f_name: filename.
 * @env: environ.
 * @environ: custom modified copy of environ from env.
 * @history: for  history.
 * @alias: alias node.
 * @env_change: equating that environmet was changed.
 * @status: last status of shell.
 * @cmd_buf: address of pointer to access command line buffer.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @read_fl: read line input.
 * @hist_count: history count.
 */

typedef struct variable
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int l_count;
	int err_num;
	int l_count_flag;
	char *f_name;
	char **environ;
	int env_change;
	int status;
	list_s *env;
	list_s *history;
	list_s *alias;

	/* pointer access address to cmd ; chain buffer, for memory mangement */
	char **cmd_buf;
	/* CMD_type ||, &&, ; */
	int cmd_buf_type;
	int read_fl;
	int hist_count;
} var_s;

#define VARS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Function that will contains a builtin string and
 * its related function
 * @type: the builtin command flag
 * @f: the function
 */
typedef struct builtin
{
        char *type;
        int (*f)(var_s *);
} builtin_s;

/* shell_loop.c */
int sh_file(var_s *, char **);
int get_builtin(var_s *);
void get_cmd(var_s *);
void fork_cmd(var_s *);

/* syn_anly */
int syn_cmd(var_s *, char **);
char *path_access(var_s*, char*, char*);
char *syn_char(char*, int, int);

/* simple_loop.c */
int simple_loop(char **);

/* error_handler.c  */
void _post(char *);
int _postchar(char);
int _postfl(char c, int fl);
int _postsfl(char *str, int fl);

/* aux_string_1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_at(const char *, const char *);
char *_strcat(char *, char *);

/* aux_string_2.c */
char *_strcpy(char *, char *);
char *strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit_shell.c */
char *_strchr(char *, char *);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);

/* aux_token.c */
char **strtow(char *, char *);
char **strow_d(char *, char);

/* aux_memo.c */
int aux_free(void **);




#endif
