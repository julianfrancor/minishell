#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "_shell.h"

#ifndef BUFF_SIZE 
#define BUFF_SIZE 1024
#endif
/**
 * main - functionc to read a line
 *
 * Return: Always 0.
 */
int main(void)
{
	char *lineptr = NULL;
	size_t n = BUFF_SIZE;
	ssize_t characters_read;

	printf("$ ");

	characters_read = _getline(&lineptr, &n, stdin);
	if (characters_read != -1)
	{
		printf("%s", lineptr);
	}

	free(lineptr);
	return(0);
}
