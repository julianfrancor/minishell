#include "shellhead.h"

/**
 * pathfinder - function to find the path of environment var
 * @command: command to be used in the shell
 * Return: the path found.
 */
char *pathfinder(char *command)
{
	char **cmdpath;
	char *result;

	/*it gets the path*/
	cmdpath = pathgetter();
	/*concat the commmand with the path*/
	result = pathcommand(cmdpath, command);
	return (result);
}

/**
 * pathgetter - function to extract the full path of environment var
 * Return: the path found.
 */
char **pathgetter(void)
{
	char *ptrenv, *tok, **result;
	unsigned int words = 0, i = 0;

	ptrenv = _getenv("PATH");

	words = count_dir(ptrenv);
	result = _calloc(words + 1, sizeof(char *));
	if (result == NULL)
	{
		perror("Error: memory allocation failed");
		return (NULL);
	}
	tok = _strtok(ptrenv, ":"); /* missing a line */
	*result = tok;
	for (i = 1; i < words; i++) /*i starts at one */
	{
		tok = _strtok(NULL, ":"); /*might be inverted */
		*(result + i) = tok;
	}
	*(result + i) = NULL;
	return (result);
}

/**
 * pathcommand - function to concatenate the path with the command
 * @result: command path found
 * @command: command given by the user
 * Return: the path found
 */
char *pathcommand(char **result, char *command)
{
	char *pathcomplete;
	int ffile = 0, lencom = 0, lenre = 0;

	if (command == NULL || result == NULL)
	{
		return (NULL);
	}

	while (*result != NULL)
	{
		lencom = _strlen(command);
		lenre =  _strlen(*result);
		pathcomplete = _calloc(lencom + 2 + lenre, sizeof(char));
		if (pathcomplete == NULL)
		{
			perror("Error allocating memory");
			free(result);
			return (NULL);
		}
		strcat(pathcomplete, *result);
		strcat(pathcomplete, "/");
		strcat(pathcomplete, command);

		ffile = access(pathcomplete, F_OK);
		if (ffile != -1)
		{
			return (pathcomplete);
		}
		free(pathcomplete); /* might be result */
		result++;
	}
	return (NULL);
}

/**
 * count_dir - function that counts the amount of directories.
 * @str: the full path to be counted.
 * Return: the amount of directories
 */
int count_dir(char *str)
{
	int i = 0, words = 0;

	for (i = 0; str[i]; i++)
	{
	if (str[i] != ':' && (str[i + 1] == ':' || str[i + 1] == '\0'))
		words++;
	}
	return (words + 1);
}
