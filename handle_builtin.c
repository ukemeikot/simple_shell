#include "shell.h"
/**
 * builtin_command - builtin handler
 * @tokens: tokens array
 * @filename: executable filename
 * @env: environemnt variable
 * @n: return code
 * Return: 0 - success (-2) - not a builtin command
 */

int builtin_command(char **tokens, char *filename, char **env, int *n)
{
	int builtin_len, m, i;
	builtin_cmd builtin[] = {
		{"exit", exit_handle},
		{"env", env_handle},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", cd_handle},
		{NULL, NULL}
	};

	builtin_len = 6;
	for (i = 0; i < builtin_len && builtin[i].cmd != NULL;  i++)
	{
		if (strcmp(builtin[i].cmd, tokens[0]) == 0)
		{
			m = builtin[i].builtin_func(tokens, filename, env, n);
			return (m);
		}
	}
	return (-50);
}

/**
  *handle_exit_error - hndles exit error
 * @filename: execution file name
 * @tk: argument
 * @msg: message to display
 * @n: number of times a child process fail to execute a command
 * Return: void
 */

void handle_exit_error(char *filename, char **tk, int n, char *msg)
{
	char error[100];
	char *count_str;

	strcpy(error, filename);
	strcat(error, ": ");
	count_str = int_to_str(n);
	if (count_str == NULL)
		count_str = "1";
	strcat(error, count_str);
	strcat(error, ": ");
	strcat(error, tk[0]);
	strcat(error, ": ");
	strcat(error, msg);
	strcat(error, ": ");
	strcat(error, tk[1]);
	strcat(error, "\n");
	write(STDERR_FILENO, error, strlen(error));
	free(count_str);
}

/**
 * exit_handle - handle_exit condition
 * @token: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int exit_handle(char **token, char *file, char **env, int *n)
{
	int status;
	static int error_n = 1;
	(void)env;

	if (token[1] == NULL)
	{
		free_mem(token);
		free_mem(environ);
		exit(*n);
	}
	status = _atoi(token[1]);
	if (status < 0)
	{
		handle_exit_error(file, token, error_n, "Illegal number");
		error_n++;
		*n = 2;
	}
	else
		*n = status;
	free_mem(token);
	free_mem(environ);
	exit(*n);
}

/**
 * env_handle - handle environment
 * @token: tokens to be parsed.
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int env_handle(char **token, char *file, char **env, int *n)
{
	int length, a;
	(void)env;

	for (a = 0; environ[a]; a++)
	{
		length = strlen(environ[a]);
		if (write(STDOUT_FILENO, environ[a], length) == -1)
		{
			*n = -1;
			perror(file);
			free_mem(token);
			return (*n);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	*n = 0;
	return (0);
}
