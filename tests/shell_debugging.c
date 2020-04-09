#ifndef SHELLHEAD_H
#define SHELLHEAD_H

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **_flags(char *buffer, ssize_t characters_read);

#endif

/**
 * flag - separates the command line and the flags
 * @buffer: pointer that sets the line
 * @characters_read:
 * Return: the flags
 */
char **_flags(char *buffer, ssize_t characters_read)
{
	char **flag;
	int i = 0, j = 0;

	char *token = strtok(buffer, " ");
	flag = malloc(sizeof(char *));
	*flag = malloc(sizeof(char) * characters_read);
	if (!flag)
	{
		for(j = 0; flag[j]; j++)
			free(flag[j]);
		free(flag);
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		flag[i] = token;
		token = strtok(NULL, " ");
		i++;

	}

	flag[i] = NULL;
	flag[i - 1] = strtok(flag[i - 1], "\n");

	return(flag);
}

/**
 * main - Shell function
 *
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL, **args = NULL;
	size_t n = 17, i = 0, k = 0;
	ssize_t characters_read;
	pid_t pid;

	while (1)
	{
		/*Printing our prompt*/
		printf("$ ");
		buffer = (char *)malloc(n);
		if (!buffer)
		{
			free(buffer);
			continue;
		}
		/*Using getline() to get whatever the user typed*/
		characters_read = getline(&buffer, &n, stdin);
		/*Checking is we read the line right*/
		if (characters_read == -1)
		{
			free(buffer);
			perror("Error: Bad arguments in getline() function");
			exit(EXIT_FAILURE);
		}
		while (buffer[k] != '\n' && buffer[k] != '\0' && buffer[k] != ' ')
			k++;
		/* We will start a Child process with Fork */
		pid = fork();
		/*to check error forking*/
		if (pid == -1)
		{
			free(buffer);
			perror("Error: No child process was created");
			exit(0);
		}
		/*Child process*/
		else if (pid == 0)
		{
			args = malloc(sizeof(char *) * k);
			*args = malloc(sizeof(char) * characters_read);
			if (*args == NULL)
			{
				for(i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				continue;
			}
			args = _flags(buffer, characters_read);
			if (args[0] == '\0')
			{
				for(i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				continue;
			}
			else
			{
				if (execve(args[0], args, NULL) == -1)
				{
					perror("Error: Execution errorOScar");
					exit(EXIT_FAILURE);
				}
				for(i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				exit(0);
			}
		}
			/*Parent process*/
		else
		{
			/*Make the parent wait for any signal from the child*/
			wait(NULL);
		}
		free(buffer);
	}
	free(buffer);
	return(0);
}