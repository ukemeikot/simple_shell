#include "shell.h"
/**
  *handle_setenv - handles set enviroment function
  *@token: the token to be passed
  *@file: the file name
  *@env: the environment variable
  *@n: the status
  *Return: the status of the program
  */

int handle_setenv(char **token, char *file, char **env, int *n)
{
	(void)env;

	if (token[1] == NULL || (token[1] != NULL && token[2] == NULL))
	{
		env_err_handler(file, "Invalid argument");
		return (*n);
	}
	if (set_env(token[1], token[2], 1) == -1)
	{
		env_err_handler(file, "Invalid argument");
		*n = -1;
		return (*n);
	}
	*n = 0;
	return (*n);
}

/**
 * handle_unsetenv - unset an environment variable
 * @token: tokens
 * @file: filename
 * @env: environment
 * @n: status code
 * Return: 0 - success
 */

int handle_unsetenv(char **token, char *file, char **env, int *n)
{
	(void)env;

	if (token[1] == NULL)
	{
		env_err_handler(file, "Invalid argument");
		return (*n);
	}
	if (my_unsetenv(token[1]) == -1)
	{
		error_handler(file, token[0], *n);
		*n = -1;
		return (*n);
	}
	*n = 0;
	return (*n);
}
