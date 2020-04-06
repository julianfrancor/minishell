#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - function to read a line
 *
 * Return: Always 0.
 */
int main(void)
{
	char *lineptr = NULL;
	size_t n = 1024;
	ssize_t characters_read;

	printf("$ ");

	characters_read = getline(&lineptr, &n, stdin);

	if (characters_read != -1)
	{
		printf("%s", lineptr);
	}

	free(lineptr);
	return(0);
}
