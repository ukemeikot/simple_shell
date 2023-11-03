#include "shell.h"

/**
 * main - this is the main shell function
 * @argc: argument counter
 * @argv: the argument vector
 * Return: 0 on success.
 */

int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	char *buffer;
	size_t size;
	ssize_t rbyte;
	char **tokens;
	int status = 0;

	while (TRUE)
	{
		if (isatty(STDIN_FILENO))
			prompt_user();
		buffer = NULL;
		tokens = NULL;
		rbyte = getline(&buffer, &size, stdin);
		if (rbyte == 1)	
		{
			free(buffer);
			continue;
		}
		if (rbyte == -1)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		tokens = tokenize(buffer);
		if (tokens == NULL)
			continue;
		handle_child(tokens, argv[0], env, &status);
		free_mem(tokens);
	}
	return (status);
}
