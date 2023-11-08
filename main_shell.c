#include "shell.h"

/**
 * main - this is the main shell function
 * @argc: argument counter
 * @argv: the argument vector
 *@env: environment variable
 * Return: 0 on success.
 */

int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	char *buffer;
	size_t size;
	ssize_t rbyte;
	char **tokens, *sep;
	int status = 0;

	sep = "\n\t ";
	environ = dynamic_env(env);
	while (TRUE)
	{
		if (isatty(STDIN_FILENO))
			prompt_user();
		buffer = NULL;
		tokens = NULL;
		rbyte = get_line(&buffer, &size, STDIN_FILENO);
		if (rbyte == 1)
		{
			free(buffer);
			continue;
		}
		if (rbyte == -1)
		{
			free(buffer);
			free_mem(environ);
			exit(EXIT_SUCCESS);
		}
		tokens = tokenize(buffer, sep);
		if (tokens == NULL)
			continue;
		path_handler(tokens, env, &status, argv[0]);
		free_mem(tokens);
	}
	free_mem(environ);
	return (status);
}
