#include "header_shell.h"

/**
 *  - Shell function
 *
 * Return: Always 0.
 */
char *read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0;
	size_t bytes_read;

	/*have getline allocate a buffer for us*/
	bytes_read = getline(&line, &bufsize, stdin);
	return line;
}