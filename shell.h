#ifndef SHELL_H
#define SHELL_H

/*Inclusion of the required header files*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>
#include <string.h>
/*Macro definition of the shell prompt message*/
#define PROMPT_M "UK_FAITH$ "
#define TRUE 1
#define BUFFER 1024

/*printing functions*/
extern char **environ;
void str_print(char *str, int newline);
int char_print(char *charac);
void prompt_user(void);
void handle_child(char **tokens, char *file, char **env, int *ret_code);
int cd_handle(char **tokens, char *dir_name, char **env, int *n);
int cd_2_home(char *dir_name);
char *my_getenv_val(char *name);
void cd_error(char *dname, char **tokens, int err_n, char *msg);
int cd_2_path(char *dir_name, char *path);
int cd_previous(char *dir_name);
int process_command(char **tokens, char **env, int *status, char *argv);
int path_builder(char **pt, char **tk, char *file, int *status, char **env);
/*Helper functions*/
char *handle_sp_char(char **tokens);
int _strlen(char *str);
int count_token(char *buffer, char *separator);
char **tokenize(char *buffer, char *sep);
void free_mem(char **tokens);
void error_handler(char *file, char *arguments, int err_no);
char *int_to_str(int count);
void env_err_handler(char *file, char *message);
void env_err_handler(char *file, char *message);
void path_handler(char **tokens, char **env, int *status, char *file);
int flusher(char **tokens);
char *get_path(void);
char *_strnstr(char *haystack, char *needle, int n);
int handle_unsetenv(char **token, char *file, char **env, int *n);
int handle_setenv(char **token, char *file, char **env, int *n);
/**
 * struct builtin - blueprint for builtin command function pointer
 * @cmd: command
 * @builtin_func: function pointer
 */

typedef struct builtin
{
	char *cmd;
	int (*builtin_func)(char **, char *, char **, int *);
} builtin_cmd;
int my_unsetenv(char *name);
char *my_getenv(char *name);
int set_env(char *name, char *value, int overwrite);
char **dynamic_env(char **env);
int my_putenv(char *new_env);
int exit_handle(char **token, char *file, char **env, int *n);
int builtin_command(char **tokens, char *filename, char **env, int *n);
int _atoi(char *s);
void handle_exit_error(char *filename, char **tk, int n, char *msg);
int env_handle(char **token, char *file, char **env, int *n);
ssize_t get_line(char **line, size_t *size, int file_d);
int overflow(int *d, int *b, char *bf, int *f, char *l, int *lp, size_t *s);
unsigned int is_delim(char c, char *delim);
char *my_strtok(char *str, char *delim);
void helper(char **tokens, char *files, char **env, int *status, char *tmp);
char *process_buf(char *buf);

#endif
