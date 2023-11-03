#include "shell.h"

/**
 * _strlen - determines the length of a string
 * @str: the string whose length is to be determined
 * Return: the number of characters in the string
 */

int _strlen(char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}

	return (length);
}
