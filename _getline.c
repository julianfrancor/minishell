#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "_shell.h"

#ifndef BUFF_SIZE 
#define BUFF_SIZE 1024
#endif

/**
 * _getchar - function that reads the next character from stream and returns it
* as an unsigned char cast to an int, or EOF on end of file or error.
 * Return: Always 0.
 */

size_t _getline(char **lineptr, size_t *bufsize, FILE *stdin)
{
	ssize_t i = 0, character;

	/*if *lineptr is NULL, then getline() will allocate a buffer
	for storing the line, which should be freed by the user program.*/
	*lineptr = malloc(sizeof(char) * BUFF_SIZE);
	if (!lineptr)
	{
		dprintf(STDERR_FILENO, "Error: Allocation error\n");
		exit(1);
	}
	do
	{
		/*Here we read a character from the stdin and returns it
		as an unsigned char cast to an int, or EOF on end of file or
		error. getchar() is equivalent to getc(stdin).*/
		character = getc(stdin);

		/*If character reaches the EOF, replace it with a null character
		and return the buffer.*/
		if (character == EOF)
		{
			lineptr[i] = NULL;
			return (character);
		}
		else
		{
			*lineptr[i] = character;
		}
		i++;

		/*if the buffer is not large enough to hold the line, getline()
		resizes it with realloc(3), updating *lineptr and *n as necessary.*/
		if (i >= BUFF_SIZE)
		{
			bufsize += BUFF_SIZE;
			*lineptr = realloc(lineptr, BUFF_SIZE);
			if (!lineptr)
			{
				/*Another way to print the error to the Standard Error*/
				perror("Error: Allocation error\n");
				exit(1);
			}
		}
		/*we want to have a infinite loop, so that is why we ask something obvious*/
	} while (BUFF_SIZE == 1024);
	return (character);
}