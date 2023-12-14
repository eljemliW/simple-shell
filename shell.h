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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @number: the number field
 * @string: a string
 * @nxt: points to the next node
 */
typedef struct liststring
{
	int number;
	char *string;
	struct liststring *nxt;
} list;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@argstr: a string generated from getline containing arguements
 *@argarr: an array of strings generated from arg
 *@strpath: a string path for the current command
 *@argcount: the argument count
 *@line_counter: the error count
 *@err_number: the error code for exit()s
 *@linecount_fl: if on count this line of input
 *@filname: the program filename
 *@environ: linked list local copy of environ
 *@environmnt: custom modified copy of environ from LL env
 *@historyn: the history node
 *@aliasn: the alias node
 *@environ_changed: on if environ was changed
 *@statuscmd: the return status of the last exec'd command
 *@comand_buf: address of pointer to cmd_buf, on if chaining
 *@comand_buf_type: CMD_type ||, &&, ;
 *@readfdinput: the fd from which to read line input
 *@histcounter: the history line number count
 */
typedef struct passinfo
{
	char *argstr;
	char **argarr;
	char *strpath;
	int argcount;
	unsigned int line_counter;
	int err_number;
	int linecount_fl;
	char *filname;
	list *environ;
	list *historyn;
	list *aliasn;
	char **environmnt;
	int environ_changed;
	int statuscmd;

	char **comand_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int comand_buf_type; /* CMD_type ||, &&, ; */
	int readfdinput;
	int histcounter;
} info;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info *);
} builtin_t;


int hsh(info *, char **);
int find_builtin(info *);
void find_cmd(info *);
void fork_cmd(info *);

int is_cmd(info *, char *);
char *dup_chars(char *, int, int);
char *find_path(info *, char *, char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlenght(char *);
int _stringcmp(char *, char *);
char *_begin_with(const char *, const char *);
char *_stringcat(char *, char *);

char *_stringcpy(char *, char *);
char *_stringdup(const char *);
void _putstr(char *);
int _putcharacter(char);

char *_stringncpy(char *, char *, int);
char *_stringncat(char *, char *, int);
char *_stringchr(char *, char);

char **stringtow(char *, char *);
char **stringtow2(char *, char);

char *_memoryset(char *, char, unsigned int);
void  cfree(char **);
void *_realoc(void *, unsigned int, unsigned int);

int afree(void **);

int interact(info *);
int is_delimeter(char, char *);
int _isalphabetic(int);
int _atoint(char *);

int _erratoint(char *);
void print_errormess(info *, char *);
int print_decimal(int, int);
char *convert_num(long int, int, int);
void remove_cmnts(char *);

int _myexit(info *);
int _mycd(info *);
int _myhelp(info *);

int _myhistory(info *);
int _myalias(info *);

ssize_t get_input(info *);
int _getline(info *, char **, size_t *);
void sigintHandler(int);

void clear_info(info *);
void set_info(info *, char **);
void free_info(info *, int);

char *_getenv(info *, const char *);
int _myenv(info *);
int _mysetenv(info *);
int _myunsetenv(info *);
int populate_env_list(info *);

char **get_environ(info *);
int _unsetenv(info *, char *);
int _setenv(info *, char *, char *);

char *get_history_file(info *info);
int write_history(info *info);
int read_history(info *info);
int build_history_list(info *inf, char *buffer, int linecounter);
int renumber_history(info *inf);

list *add_node(list **, const char *, int);
list *add_node_end(list **, const char *, int);
size_t print_list_str(const list *);
int delete_node_at_index(list **, unsigned int);
void free_list(list **);

size_t list_len(const list *);
char **list_to_strings(list *);
size_t print_list(const list *);
list *node_starts_with(list *, char *, char);
ssize_t get_node_index(list *, list *);

int is_chain(info *, char *, size_t *);
void check_chain(info *, char *, size_t *, size_t, size_t);
int replace_alias(info *);
int replace_vars(info *);
int replace_string(char **, char *);

#endif

