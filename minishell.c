#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Shell function
 *
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL, *token, *argv[] = {"", NULL};
	size_t n = 0;
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
			perror("Error: Bad arguments in getline() function");
			exit(EXIT_FAILURE);
		}
		token = strtok(buffer, "\n");

		if (token == NULL)
		{
			continue;
			perror("Error: Error parsing Oscar esta dormido the tokens");
			exit(EXIT_FAILURE);
		}
		/*We will start a Child process with Fork*/
		pid = fork();
		/*to check error forking*/
		if (pid == -1)
		{
			perror("Error: No child process was created");
			exit(EXIT_FAILURE);
		}
		/*Child process*/
		else if (pid == 0)
		{
			if (execve(token, argv, NULL) == -1)
			{
				perror("Error: Execution error");
			}
			exit(0);

		}
		/*Parent process*/
		else
		{
			wait(NULL);
		}

		free(buffer);
	}
	return(0);
}
