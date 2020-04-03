#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#ifndef ARG_MAX
#define ARG_MAX
#endif



int main(void)
{
	char **lineptr = NULL;
	size_t n = ARG_MAX;
	ssize_t characters_read;

	characters_read =  = getline(char **lineptr, size_t *n, stdin);

	characters_read =  = getline(, size_t *n, stdin);

	while (characters_read != -1)
	{
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}

	free(line);
	exit(EXIT_SUCCESS);
}

/**
 * main - function that passes the command line arguments
 * @ac: is the number of items in av
 * @av: is a NULL terminated array of strings
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags; mode_t filePerms;
	ssize_t numRead;
	char buf[ARG_MAX];

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s old-file new-file\n", argv[0]);
	/* Open input and output files */
	inputFd = open(argv[1], O_RDONLY);
	if (inputFd == -1)
		errExit("opening file %s", argv[1]);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
	
	outputFd = open(argv[2], openFlags, filePerms);
	if (outputFd == -1)
		errExit("opening file %s", argv[2]);
	
	/* Transfer data until we encounter end of input or an error */
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	if (write(outputFd, buf, numRead) != numRead)
		fatal("couldn't write whole buffer");
	if (numRead == -1)
		errExit("read");
	
	if (close(inputFd) == -1)
		errExit("close input");
	if (close(outputFd) == -1)
		errExit("close output");

	exit(EXIT_SUCCESS);
}