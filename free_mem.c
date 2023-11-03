#include "shell.h"

/**
*free_mem - frees memory
*@tokens: the tokens
Return: nothing
*/

void free_mem(char **tokens)
{
	char **tokens_c;

	if (tokens == NULL)
		return;
	tokens_c = tokens;
	while (*tokens_c)
	{
		free(*tokens_c);
		tokens_c++;
	}
	free(tokens);
}
