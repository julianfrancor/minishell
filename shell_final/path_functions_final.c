#include "shellhead_final.h"

/**
 * pathrunner - finds and runs the command given by the user
 * @command: command to be found.
 * @iterations: number of interations of the shell program
 * @argv: command passed through the prompt
 * Return: 0 in success
 */
int pathrunner(char **command, int iterations, char *argv)
{
	char *fullpath_name;
	int status;

	/*check if the command given is not the built-in env or printenv*/
	if (strcmp("env", command[0]) == 0 || strcmp("printenv", command[0]) == 0)
		envbuilt();
	/*string comparison to check the command given is not the built-in exit*/
	if (strcmp("exit", command[0]) == 0)
	{
		free(command[0]);
		free(command);
		exit(EXIT_SUCCESS);
	}
	fullpath_name = pathfinder(command[0]);
	/*if the command couldn't be found, or pathfinder failed to find the path*/
	if (fullpath_name == NULL)
	{
		/*Command not found*/
		command_not_found_handler(command, iterations, argv);
		/*free (command); status = 127;*/
		return (1);
	}
	else
	{
		command[0] = fullpath_name;
		status = execve(command[0], command, environ);
		if (status == -1)
		{
			free(fullpath_name);
			perror("$ Error in execution");
			free(command[0]);
			free(command);
			exit(EXIT_FAILURE);
		}
		free(fullpath_name);
		exit(EXIT_SUCCESS);
	}
}

/**
 * pathfinder - function to find the path of environment var
 * @command: command to be used in the shell
 * Return: the path found.
 */
char *pathfinder(char *command)
{
	char *cmdpath;

	/*it gets the path*/
	cmdpath = pathgetter(command);
	/*concat the commmand with the path*/
	/*result = pathcommand(cmdpath, command);*/
	return (cmdpath);
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
	struct stat comparison_stat;
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
		_strcat(pathcomplete, *result);
		_strcat(pathcomplete, "/");
		_strcat(pathcomplete, command);

		ffile = stat(pathcomplete, &comparison_stat);
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
/**
 * pathgetter - function to extract the full path of environment var
 * @command: command to be found
 * Return: the path found.
 */
char *pathgetter(char *command)
{
	char *ptrenv, *tok, *result;
	struct stat string_comparison;

	ptrenv = _getenv("PATH");
	tok = _strtok(ptrenv, ":");
	while (tok != NULL)
	{
		result = _calloc(_strlen(tok) + 3 + _strlen(command), sizeof(char *));
		_strcpy(result, tok);
		_strcat(result, command);
		if (stat(result, &string_comparison) == 0)
		{
			free(ptrenv);
			return (result);
		}
		tok = _strtok(NULL, ":");
		free(result);
	}
	free(ptrenv);
	return (NULL);
}
