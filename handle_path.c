#include "shell.h"
/**
  *path_handler - handles the path condition.
  *@tokens: the tokens to e passed
  *@env: the environment variable
  *@status: the status code
  *@file: the filename
  */

void path_handler(char **tokens, char **env, int *status, char *file)
{
	struct stat buf;
	char *path, **path_tokens, *sep = ":";
	static int n = 1;

	path = NULL;
	path_tokens = NULL;
	if (builtin_command(tokens, file, env, status) != -50)
		return;
	else if (stat(tokens[0], &buf) == 0)
	{
		handle_child(tokens, file, env, status);
		return;
	}
	path = get_path();
	if (path == NULL)
	{
		*status = 127;
		error_handler(file, tokens[0], n);
		return;
	}
	path_tokens = tokenize(path, sep);
	if (path_builder(path_tokens, tokens, file, status, env) == 0)
		return;
	if (!isatty(STDIN_FILENO))
		n++;
	error_handler(file, tokens[0], n);
	free_mem(path_tokens);
	*status = 127;
}

/**
  *get_path - gets the environent path
  *Return: returns the path
  */

char *get_path(void)
{
	int i;
	char *path, *tmp;

	i = 0;
	tmp = NULL;
	path = NULL;
	while (environ[i])
	{
		path = _strnstr(environ[i], "PATH=", 5);
		if (path == NULL)
			i++;
		else
		{
			path = path + 5;
			tmp = malloc(sizeof(char) * (_strlen(path) + 1));
			strcpy(tmp, path);
			return (tmp);
		}
	}
	return (tmp);
}

/**
  *path_builder - builds path
  *@pt: path tokens
  *@tk: tokens
  *@file: the file
  *@status: the status code
  *@env: enviroment
  *Return: 1 on success and 0 on failure
  */

int path_builder(char **pt, char **tk, char *file, int *status, char **env)
{
	char *tmp;
	int len = 0, i;
	struct stat buf;

	tmp = NULL;
	for (i = 0; pt[i]; i++)
	{
		len = _strlen(pt[i]) + _strlen(tk[0]) + 2;
		tmp = malloc(sizeof(char) * len);
		if (tmp == NULL)
			break;
		strcpy(tmp, pt[i]);
		strcat(tmp, "/");
		strcat(tmp, tk[0]);
		if (stat(tmp, &buf) == 0)
		{
			free_mem(pt);
			free(tk[0]);
			tk[0] = tmp;
			handle_child(tk, file, env, status);
			return (0);
		}
		free(tmp);
		tmp = NULL;
	}
	return (1);
}
