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
	char *path, **path_tokens, *sep = ":", *tmp, *cmd;
	int i = 0, len = 0;
	static int n = 1;

	tmp = path = NULL;
	path_tokens = NULL;
	if (builtin_command(tokens, file, env, status) == 0)
		return;
	if (stat(tokens[0], &buf) == 0)
	{
		handle_child(tokens, file, env, status);
		return;
	}
	cmd = tokens[0];
	path = get_path();
	path_tokens = tokenize(path, sep);
	for (i = 0; path_tokens[i]; i++)
	{
		len = _strlen(path_tokens[i]) + _strlen(cmd) + 2;
		tmp = malloc(sizeof(char) * len);
		if (tmp == NULL)
			break;
		strcpy(tmp, path_tokens[i]);
		strcat(tmp, "/");
		strcat(tmp, cmd);
		if (stat(tmp, &buf) == 0)
		{
			free_mem(path_tokens);
			free(tokens[0]);
			tokens[0] = tmp;
			handle_child(tokens, file, env, status);
			return;
		}
		free(tmp);
		tmp = NULL;
	}
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
