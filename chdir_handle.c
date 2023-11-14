#include "shell.h"
/**
  *cd_handle - handles cd functions
  *@tokens: the parsed tokens
  *@dir_name: the directory name
  *@env: environment varaiable
  *@n: the status code
  *Return: the status code
  */
int cd_handle(char **tokens, char *dir_name, char **env, int *n)
{
	size_t size;
	char dir[200];
	static int error_n = 1;
	char *err_m = "Can't cd to";

	(void)env;
	size = 200;
	if (!tokens[1])
	{
		*n = cd_2_home(dir_name);
		if (*n == -2)
		{
			*n = -1;
			cd_error(dir_name, tokens, error_n, err_m);
		}
	}
	else if (strcmp(tokens[1], "-") == 0)
	{
		*n = cd_previous(dir_name);
		if (*n == 0)
		{
			if (getcwd(dir, size) == NULL)
			{
				cd_error(dir_name, tokens, error_n, err_m);
				*n = -1;
				return (*n);
			}
			write(STDOUT_FILENO, dir, _strlen(dir));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		*n = cd_2_path(dir_name, tokens[1]);
	if (*n == -2)
		cd_error(dir_name, tokens, error_n, err_m);
	if (*n == -1)
		env_err_handler(dir_name, "Invalid path");
	return (*n);
}
/**
  *cd_error - prints change directory errors
  *@dname: the directory name
  *@tokens: the tokens to be parsed
  *@err_n: the error number
  *@msg: the error message
  *Return: nothing
  */

void cd_error(char *dname, char **tokens, int err_n, char *msg)
{
	char err[150];
	char *str_count;

	strcpy(err, dname);
	strcat(err, ": ");
	str_count = int_to_str(err_n);
	if (str_count == NULL)
		str_count = "1";
	strcat(err, str_count);
	strcat(err, tokens[0]);
	strcat(err, ": ");
	strcat(err, msg);
	strcat(err, " ");
	strcat(err, tokens[1]);
	strcat(err, "\n");
	write(STDERR_FILENO, err, _strlen(err));
	free(str_count);
}
/**
  *cd_2_home - changes directory to home
  *@dir_name: the directory name
  *Return: 0 on success, -1 on failure and -2 on special failure
  */
int cd_2_home(char *dir_name)
{
	size_t size = 200;
	char dir[200];
	char home[200];
	char *tmp;

	tmp = my_getenv_val("HOME");
	strcpy(home, tmp);
	if (getcwd(dir, size) == NULL)
		return (-2);
	if ((set_env("PWD", home, 1)) == -1)
	{
		env_err_handler(dir_name, "Invalid path");
		return (-1);
	}
	if ((set_env("OLDPWD", dir, 1)) == -1)
	{
		env_err_handler(dir_name, "Invalid Path");
		return (-1);
	}
	if (chdir(home) == -1)
		return (-2);
	return (0);
}

/**
  *my_getenv_val - gets the environment value
  *@name: the diectory name
  *Return: the environment variable
  */

char *my_getenv_val(char *name)
{
	char *environment;

	environment = my_getenv(name);
	environment = strchr(environment, '=');
	environment++;
	return (environment);
}

/**
  *cd_2_path - changes directory to the path provided.#
  *@dir_name: the directory name
  *@path: the path to be changed to
  *Return: 0 on success, -1 on failure and -2 on special failure
  */

int cd_2_path(char *dir_name, char *path)
{
	size_t size;
	char oldpwd[300], pwd[300];

	(void)dir_name;
	size = 300;
	if (getcwd(oldpwd, size) == NULL)
		return (-2);
	if (chdir(path) == -1)
		return (-2);
	if (set_env("OLDPWD", oldpwd, 1) == -1)
		return (-1);
	if (getcwd(pwd, size) == NULL)
		return (-1);
	if (set_env("PWD", pwd, 1) == -1)
		return (-1);
	return (0);
}
