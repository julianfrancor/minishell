

#include "shellhead_final.h"



/**
 * envbuilt - function to print the enviroment var
 * Return: nothing
 */
void envbuilt(void)
{

	int i = 0;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
	}

}

/**
 * _getenv - get the enviroment variable from environ
 * @name: the name of the env var
 * Return: the pointer of the var.
 */
char *_getenv(const char *name)
{
	char *tok, *s, *tmpenv;
	int i = 0;
	const char *delim = "=";

	while (environ[i])
	{
		/* avoids the environ var */
		tmpenv = _strdup(environ[i]);
		/* parse the full path */
		tok = _strtok(tmpenv, delim);
		if (strcmp(name, tok) == 0)
		{
			tok = _strtok(NULL, delim);
			/* avoid valgrind error */
			s = _strdup(tok);
			free(tmpenv);
			return (s);
		}
		free(tmpenv);
		i++;
	}
	return (NULL);
}
