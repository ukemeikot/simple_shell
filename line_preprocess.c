#include "shell.h"
/**
  * process_buf - process the received string to include special characters
  *@buf: the input buffer;
  *Return: the processed buffer
  */

char *process_buf(char *buf)
{
	char *new_buffer;
	int index;
	int length, a;

	length = strlen(buf);
	new_buffer = malloc(2 * (sizeof(char)) * length + 1);
	if (!new_buffer)
		return (NULL);
	index = 0;
	for (a = 0; a < length; a++)
	{
		if (buf[a] == '|' && a < length - 1 && buf[a + 1] == '|')
		{
			new_buffer[index++] = ' ';
			new_buffer[index++] = '|';
			new_buffer[index++] = '|';
			new_buffer[index++] = ' ';
			a++;
		}
		else if (buf[a] == '&' && a < length - 1 && buf[a + 1] == '&')
		{
			new_buffer[index++] = ' ';
			new_buffer[index++] = '&';
			new_buffer[index++] = '&';
			new_buffer[index++] = ' ';
			a++;
		}
		else if (buf[a] == ';' || buf[a] == '|' || buf[a] == '&')
		{
			new_buffer[index++] = ' ';
			new_buffer[index++] = buf[a];
			new_buffer[index++] = ' ';
		}
		else
			new_buffer[index++] = buf[a];
	}
	new_buffer[index] = '\0';
	free(buf);
	return (new_buffer);
}
