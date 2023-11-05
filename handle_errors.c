#include "shell.h"
/**
  *error_handler - prints error messages
  *@file: the name of the file
  *@arguments: the arguments
  *@err_no: the error number passed to it.
  */

void error_handler(char *file, char *arguments, int err_no)
{
	char error_m[200];
	char *str_counter;

	strcpy(error_m, file);
	strcat(error_m, ": ");
	str_counter = int_to_str(err_no);
	if (str_counter == NULL)
		str_counter = "1";
	strcat(error_m, str_counter);
	strcat(error_m, ": ");
	strcat(error_m, arguments);
	strcat(error_m, ": ");
	strcat(error_m, "not found\n");
	write(STDERR_FILENO, error_m, strlen(error_m));
	free(str_counter);
}
/**
  *int_to_str - interger to string converter
  *@count: interger to be converted to string
  *Return: the coverted string
  */
char *int_to_str(int count)
{
	int num, tmp, remainder;
	char *str;

	tmp = count;
	for (num = 0; (tmp / 10) > 0; num++)
		tmp /= 10;
	num++;
	str = malloc(sizeof(char) * (num + 1));
	if (str == NULL)
		return (NULL);
	str += num;
	*str = '\0';
	str--;
	while ((count / 10) != 0)
	{
		remainder = count % 10;
		*str = remainder + 48;
		count /= 10;
		str--;
	}
	remainder = count % 10;
	*str = remainder + 48;
	return (str);
}
/**
  *env_err_handler - handles environent error
  *@file: the file
  *@message: the message to be passed
  *Return: void
  */
void env_err_handler(char *file, char *message)
{
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
}
