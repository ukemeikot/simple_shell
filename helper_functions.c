#include "shell.h"

/**
*_strnstr - locate an n-number of substring in a larger string
* @haystack: larger string
* @needle: substring to locate
* @n: number of byte to locate
* Return: pointer to the substring or NULL if not found
*/

char *_strnstr(char *haystack, char *needle, int n)
{
	int i;

	if (needle == NULL)
		return (haystack);
	for (i = 0; i < n && haystack[i]; i++)
	{
		if (haystack[i] != needle[i])
			return (NULL);
	}
	return (haystack);
}
