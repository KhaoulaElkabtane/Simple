#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/Write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for comand chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number () */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline () */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: field number
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int num;
	char  *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit ()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD type ||, &&,  ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL,\
	NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* hsh.c */
int shell_loop(info_t *, char **);
int fbuil(info_t *);
void path_command(info_t *);
void fcmd(info_t *);

/* path.c */
int fnct_cmd(info_t *, char *);
char *fnct_dup(char *, int, int);
char *creat_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void er_puts(char *);
int erputchar(char);
int _puts(char *str, int file);
int _putwrit(char ch, int file);

/* string_functions.c */
int _strlength(char *);
int _strcomparison(char *, char *);
char *startWith(const char *, const char *);
char *str_cat(char *, char *);

/* string_functions2.c */
char *_strcopy(char *, char *);
char *_strduplication(const char *);
void _strputs(char *);
int _putchar(char);

/* string_functions3.c */
char *_strcopy2(char *, char *, int);
char *_strconcatenate(char *, char *, int);
char *_strcharacter(char *, char);

/* string_functions4 .c */
char **_strwords(char *, char *);
char **_strwords2(char *, char);

/* memory_functions */
char *_memoryfle(char *, char, unsigned int);
void _free(char **);
void *_malloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int _freemalloc(void **);

/* more_funcions.c */
int _reactive(info_t *);
int _strdelimeter(char, char *);
int _alphabetic(int);
int _strconvert(char *);

/* move.functions2.c */
int _convertsti(char *);
void _fnct_error(info_t *, char *);
int _decimal(int, int);
char *str_convertion(long int, int, int);
void _rvcomments(char *);

/* builtin_emulators */
int exit_fun(info_t *);
int cd_directory(info_t *);
int fnct_help(info_t *);

/* builtin_emulators2 */
int cmd_history(info_t *);
int remove_alias(info_t *, char *);
int _alias(info_t *);

/* getline.c */
ssize_t put_buffer(info_t *, char **, size_t *);
int next_line(info_t *, char **, size_t *);
void fnct_handler(int);
ssize_t input_(info_t *);
ssize_t readbuffer(info_t *info, char *buffer, size_t *var);

/* info.c */
void free_info(info_t *);
void _setinis(info_t *, char **);
void lib_info(info_t *, int);

/* env.c */
char *get_envirenement(info_t *, const char *);
int _envirenement(info_t *);
int new_envirenement(info_t *);
int remove_envirenement(info_t *);
int penv_list(info_t *);

/* env2.c */
char **_environ(info_t *);
int rem_envirenement(info_t *, char *);
int new_env(info_t *, char *, char *);

/* file_io_function.c */
char *history_file(info_t *info);
int creat_history(info_t *info);
int rhistory(info_t *info);
int history_list(info_t *info, char *buffer, int coun);
int num_history(info_t *info);

/* liststr.c */
list_t *_node(list_t **, const char *, int);
list_t *_nend(list_t **, const char *, int);
size_t list_str(const list_t *);
int node_index(list_t **, unsigned int);
void l_free(list_t **);

/* liststr2.c */
size_t l_length(const list_t *);
char **list_string(list_t *);
size_t _list(const list_t *);
list_t *_nstart(list_t *, char *, char);
size_t gnode(list_t *, list_t *);

/* chain.c */
int my_chain(info_t *, char *, size_t *);
void chain_ck(info_t *, char *, size_t *, size_t, size_t);
int _realias(info_t *);
int var_replacing(info_t *);
int str_replacing(char **, char *);

#endif

