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
	char *new_buf;
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
		new_buf = process_buf(buffer);
		tokens = tokenize(new_buf, sep);
		if (tokens == NULL)
			continue;
		process_command(tokens, env, &status, argv[0]);
		free_mem(tokens);
	}
	free_mem(environ);
	return (status);
}

/**
  *handle_sp_char - handles processing with special tokens
  *@tokens: the tokens to be processed
  *Return: the pointer to the special character
  */

char *handle_sp_char(char **tokens)
{
	char *special_chars = ";||&&";
	char *sp_char;
	int a = 0;

	while (tokens[a])
	{
		sp_char = strstr(special_chars, tokens[a]);
		if (sp_char)
			return (sp_char);
		a++;
	}
	return (NULL);
}
/**
  *process_command - processes commands
  *@tokens: tokens
  *@env: environment
  *@status: the status code
  *@argv: arguments
  *Return: 0 at the end of the loop
  */
int process_command(char **tokens, char **env, int *status, char *argv)
{
	char *sp_chars = ";||&&", *checked_char, **new_tk, **tk = tokens;
	int count = 0, a, prev;

	checked_char = handle_sp_char(tokens);
	if (!checked_char)
		path_handler(tokens, env, status, argv);
	else
	{
		for (count = 0; tk[count]; count++)
		{
			prev = count;
			while (tk[count] && !strstr(sp_chars, tk[count]))
				count++;
			new_tk = malloc(sizeof(char *) * ((count - prev) + 1));
			for (a = 0; a < (count - prev); a++)
				new_tk[a] = strdup(tk[prev + a]);
			new_tk[a] = NULL;
			checked_char = tk[count];
			path_handler(new_tk, env, status, argv);
			if (checked_char != NULL)
			{
				if (strcmp(checked_char, "||") == 0)
				{
					if (*status == 0)
						return (flusher(new_tk));

				}
				else if (strcmp(checked_char, "&&") == 0)
				{
					if (*status != 0)
						return (flusher(new_tk));
				}
			}
			else
				return (flusher(new_tk));
			free_mem(new_tk);
		}
	}
	return (0);
}
/**
  *flusher - flushes memory
  *@tokens: the tokens
  *Return: 1 on success
  */
int flusher(char **tokens)
{
	free_mem(tokens);
	return (1);
}

