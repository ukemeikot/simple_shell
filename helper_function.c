#include "main.h"

/**
 * _strlen - function that returns length of the string
 * @s: parameter
 * Return: return count
 */

int _strlen(char *s)
{
	int i;
	int count = 0;

	for (i = 0; s[i] != '\0'; i++)
	count++;
	return (count);
}
