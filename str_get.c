#include "shell.h"

/**
 * get_line - get a line of byte from a file
 * @line: where to store the data
 * @file_d: where to read the data from
 * @size: size of buffer
 * Return: read data from buffer up until newline
 */

ssize_t get_line(char **line, size_t *size, int file_d)
{
	int number = 256, lp = 0, rt, c;
	static char buffer[BUFFER];
	static int dp = 1, bs = 1;

	if (*line == NULL)
		*line = malloc(sizeof(char) * number);
	if (*line == NULL)
		return (-1);
	if (dp >=  bs)
	{
		bs = read(file_d, buffer, BUFFER - 1);
		if (bs <= 0)
		{
			(*line)[lp] = '\0';
			*size = lp;
			return (-1);
		}
		dp = 0;
	}
	c = buffer[dp++];
	while (c != '\n')
	{
		(*line)[lp++] = c;
		if (lp >= (number - 10))
		{
			number = number + 256;
			*line = realloc(*line, number);
			if (*line == NULL)
				return (-1);
		}
		rt = overflow(&dp, &bs, buffer, &file_d, *line, &lp, size);
		if (rt != -100)
			return (rt);
		c = buffer[dp++];
	}
	(*line)[lp++] = '\n';
	(*line)[lp] = '\0';
	*size = lp;
	return (*size);
}

/**
 * overflow - check if buffer has overflowed
 * @d: data position
 * @b: byte size
 * @bf: buffer
 * @f: file descriptor
 * @l: line buffer
 * @lp: line position
 * @s: line buffer size
 * Return: integer
 */

int overflow(int *d, int *b, char *bf, int *f, char *l, int *lp, size_t *s)
{
	if (*d >= *b)
	{
		*b = read(*f, bf, 1023);
		if (*b <= 0)
		{
			l[*lp] = '\0';
			*s = *lp;
			return (*s);
		}
		*d = 0;
	}
	return (-100);
}

/**
*is_delim - checks for delimeter
*@c: characters
*@delim: delimeters passed
*Return: 1 if delimeter or 0 otherwise
*/
unsigned int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}
/**
*my_strtok - tokenizes a string
*@str: source string
*@delim: delimter string
*Return: pointer to the first token
*/
char *my_strtok(char *str, char *delim)
{
	static char *token;
	char *end = NULL;

	if (str != NULL)
	{
		token = str;
	}
	while (*token && strchr(delim, *token))
		token++;
	if (*token == '\0')
	{
		return (NULL);
	}
	end = token;
	while (*token && !strchr(delim, *token))
		token++;
	if (*token)
	{
		*token = '\0';
		token++;
	}
	return (end);
}
