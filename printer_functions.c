#include "shell.h"

/**
 * str_print - prints string to the standard output
 * @str: the string whose content is to be printed to
 * standard output.
 * @newline: helps to set if newline will be printed to
 * standard output of not.
 * Return: nothing
 */
void str_print(char *str, int newline)
{
	int a;

	if (str == NULL)
		str = "(nil)";
	while (str[a] != '\0')
	{
		write(STDOUT_FILENO, &str[a], 1);
		a++;
	}
	if (newline == 0)
		write(STDOUT_FILENO, "\n", 1);
}
/**
 * char_print - prints character to the screen.
 * @charac: the character to be printed
 * Return: nothing
 */
int char_print(char *charac)
{
	return (write(1, &charac, 1));
}
/**
 * prompt_user - prints the user prompt to the screen
 */
void prompt_user(void)
{
	size_t size;
	char dir[300];
	char pwd[200];

	size = 200;
	strcpy(dir, "uk_faith");
	getcwd(pwd, size);
	strcat(dir, pwd);
	strcat(dir, "$ ");
	write(STDOUT_FILENO, dir, _strlen(dir));
}

