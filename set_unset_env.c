#include "shell.h"
/**
 * my_getenv - check if an environment variable exist
 * @name: name of the environment variable
 * Return: 1 (exist) 0 (does not exist)
 */

char *my_getenv(char *name)
{
	int a;
	char *environment;

	for (a = 0; environ[a]; a++)
	{
		environment = _strnstr(environ[a], name, _strlen(name));
		if (environment)
			return (environment);
	}
	return (NULL);
}
/**
 * set_env - set an environment variable
 * @name: name of environment variable
 * @value: value of environment variable
 * @overwrite: overwites the environment variable.
 * Return: (0) - success : (-1) - on error
 */

int set_env(char *name, char *value, int overwrite)
{
	char *new_env;
	int size;

	if (name == NULL || value == NULL)
		return (-1);
	size = strlen(name) + strlen(value) + 2;
	new_env = malloc(sizeof(char) * size);
	if (new_env == NULL)
		return (-1);
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);
	strcat(new_env, "\0");
	if (my_getenv(name) == NULL)
	{
		if (my_putenv(new_env) == -1)
			return (-1);
	}
	else
	{
		if (overwrite == 0)
			free(new_env);
		else
		{
			if (my_unsetenv(name) == -1)
				return (-1);
			if (my_putenv(new_env) == -1)
				return (-1);
		}
	}
	return (0);
}

/**
 * my_putenv - put an environment variable into a list of env variables
 * @new_env: name of the env variable
 * Return: (0) - success, (-1) - error
 */

int my_putenv(char *new_env)
{
	int a, b;
	char **array, *tmp, **tmp1;

	for (a = 0; environ[a] != NULL; a++)
		;
	array = malloc(sizeof(char *) * (a + 2));
	if (array == NULL)
	{
		free(new_env);
		return (-1);
	}
	for (a = 0; environ[a]; a++)
	{
		tmp = strdup(environ[a]);
		if (tmp == NULL)
		{
			for (b = a - 1; b >= 0; b--)
				free(array[b]);
			free_mem(array);
			free(new_env);
			return (-1);
		}
		array[a] = tmp;
	}
	array[a] = new_env;
	a++;
	array[a] = NULL;
	tmp1 = environ;
	environ = array;
	free_mem(tmp1);
	return (0);
}

/**
 * dynamic_env - allocate memory for env and make it resizable
 * @env: environment variable
 * Return: pointer to redesign environment variable
 */

char **dynamic_env(char **env)
{
	int a, b;
	char *tmp;
	char **env_array;

	for (a = 0; env[a]; a++)
		;
	env_array = malloc(sizeof(char *) * (a + 1));
	if (env_array == NULL)
		return (NULL);
	for (a = 0; env[a]; a++)
	{
		tmp = strdup(env[a]);
		if (tmp == NULL)
		{
			for (b = a - 1; b >= 0; b--)
				free(env_array[b]);
			free_mem(env_array);
			return (NULL);
		}
		env_array[a] = tmp;
	}
	env_array[a] = NULL;
	return (env_array);
}

/**
 *my_unsetenv - remove an environ variable
 * @name: name of the environment variable to remove
 * Return: 0 -if successful, -1 - on failure
 */

int my_unsetenv(char *name)
{
	int a, b;

	for (a = 0; environ[a]; a++)
		;
	if (my_getenv(name) == NULL)
		return (-1);
	for (a = 0; environ[a]; a++)
	{
		if (_strnstr(environ[a], name, strlen(name)))
		{
			free(environ[a]);
			environ[a] = NULL;
			for (b = a; environ[b + 1]; b++)
				environ[b] = environ[b + 1];
			environ[b] = NULL;
		}
	}
	return (0);
}
