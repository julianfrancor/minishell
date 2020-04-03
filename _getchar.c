#include <stdlib.h>
#include <stdio.h>
#include <unistad.h>

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 1024
#endif

/**
 * _getchar - function that reads the next character from stream and returns it
* as an unsigned char cast to an int, or EOF on end of file or error.
 * @ac: is the number of items in av
 * @av: is a NULL terminated array of strings
 * Return: Always 0.
 */


char *lsh_read_line(void)
{
	int bufsize = LSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer) {
	fprintf(stderr, "lsh: allocation error\n");
	exit(EXIT_FAILURE);
	}

	while (1) {
	// Read a character
	c = getchar();

	// If we hit EOF, replace it with a null character and return.
	if (c == EOF || c == '\n') {
		buffer[position] = '\0';
		return buffer;
	} else {
		buffer[position] = c;
	}
	position++;

	// If we have exceeded the buffer, reallocate.
	if (position >= bufsize) {
		bufsize += LSH_RL_BUFSIZE;
		buffer = realloc(buffer, bufsize);
		if (!buffer) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
		}
	}
	}
}