#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - function that splits a string and returns an array of each word of the string.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *lineptr = NULL, *token;
	size_t n = 1024;
	ssize_t characters_read;

	printf("$ ");

	characters_read = getline(&lineptr, &n, stdin);
	if (characters_read != -1)
	{
		token = strtok(lineptr, " ");
		/* Keep printing tokens while one of the
		delimiters present in str[]*/
		while (token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, " \n");
		}
	}

	free(lineptr);
	return(0);
}