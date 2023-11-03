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

/*Macro definition of the shell prompt message*/
#define PROMPT_M "($): "
#define TRUE 1

/*printing functions*/
void str_print(char *str, int newline);
int char_print(char *charac);
void prompt_user(void);
void handle_child(char **tokens, char *file, char **env, int *ret_code);
/*Helper functions*/
int _strlen(char *str);
int count_token(char *buffer, char *separator);
char **tokenize(char *buffer);
void free_mem(char **tokens);
void error_handler(char *file, char *arguments, int err_no);
 char *int_to_str(int count);
#endif
