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
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

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
	int cmd_buf_types;
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
int syn_cmd(var_s *, char *);
char *path_access(var_s*, char*, char*);
char *syn_char(char*, int, int);

/* aux_loop.c */
int aux_loop(char **);

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
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit_shell.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* aux_token.c */
char **strtow(char *, char *);
char **strtow_d(char *, char);

/* aux_memo.c */
int aux_free(void **);

/* aux_realloc.c */
char *_memset(char *, char, unsigned int);
void s_free(char **);
void *_realloc_shell(void *, unsigned int, unsigned int);

/* aux_builtin_1.c */
int _ssexit(var_s *);
int _sscd(var_s *);
int _sshelp(var_s *);

/* aux_builtin_2.c */
int _sshistory(var_s *);
int _ssalias(var_s *);
int unset_ali(var_s *, char *);
int set_ali(var_s *, char *);
int print_ali(list_s *node);

/* aux_error_1.c */
int _err_ato(char *);
void get_error(var_s *, char *);
int get_di(int, int);
char *trans_number(long int, int, int);
void delete_comment(char *);

/* aux_list_1.c */
list_s *add_node(list_s **, const char *, int);
list_s *add_end(list_s **, const char *, int);
int del_node(list_s **, unsigned int);
size_t print_ls(const list_s *);
void free_lists(list_s **);

/* aux_list_2.c */
size_t list_length(const list_s);
char **list_strings(list_s *);
list_s *node_begins_at(list_s *, char *, char);
ssize_t get_node(list_s *, list_s *);
size_t print_list(const list_s *);

/* aux_history.c */
char *fetch_history(var_s *vars);
int write_hist(var_s *vars);
int read_hist(var_s *vars);
int build_hlist(var_s *vars, char *buf, int l_count);
int num_history(var_s *vars);

/* aux_variable.c */
int in_chain(var_s *, char *, size_t *);
void conf_chain(var_s *, char *, size_t *, size_t, size_t);
int swap_var(var_s *);
int swap_alias(var_s *);
int swap_string(char **, char *);

/* aux_get_envn.c */
char **get_envn(var_s *);
int _unsetenv(var_s *, char *);
int _setenv(var_s *, char *, char *);

/* aux_environment.c */
char *_getenv(var_s *, const char *);
int _ssenv(var_s *);
int _sssetenv(var_s *);
int _ssunsetenv(var_s *);
int load_envl(var_s *);

/* aux_getvar.c */
void erase_var(var_s *);
void fix_var(var_s *, char **);
void free_var(var_s *, int);

/* aux_getline.c */
int _getlines(var_s *, char **, size_t *);
void sig_handle(int);
ssize_t get_input(var_s *);

/* aux_strint.c */
int responsive(var_s *);
int is_token(char, char *);
int is_text(int);
int _ato(char *);

#endif
