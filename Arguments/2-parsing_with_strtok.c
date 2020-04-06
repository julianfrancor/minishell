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
	ssize_t bytes_read;
	size_t size = 0;
	char *buffer;
	char *token;
	char **_flags;
	int i = 0;

	/*print the prompt*/
	printf ("$ ");
	/*Allocating memory for the buffer*/
	buffer = (char *)malloc(size);

	/*Reading the line and storing it in the buffer*/
	bytes_read = getline (&buffer, &size, stdin);
	if (bytes_read == -1)
		perror("Error reading line");

	token = strtok(buffer, " ");

	/*Allocating space to store the pointers to the first char of the strings (the flags)*/
	_flags = malloc(sizeof(char *));
	/*Allocating space to store the strings themselves*/
	*_flags = (char *)malloc(sizeof(char)* bytes_read);
	
	/*loop to allocate the pointer of each argument within the _flags*/
	while (token != NULL)
	{
		_flags[i] = token;
		/*When we pass a NULL to the strtok, we basically are saing
		'hey remember were you left off on the last one*/
		printf("tokens printed later on: [%p] ---> %s]\n", token, token);
		token = strtok(NULL, " ");
		i++;
	}
	/*Every time that we parse, the strtok put a new-line.
	here we are removing the new-line to every single parsed argument*/
	_flags[i - 1] = strtok(_flags[i - 1], "\n");
	/*Changing the new-line for a null*/
	_flags[i] = NULL;
	
	while(*_flags)
	{
		printf("%s", *_flags);
		_flags++;
	}
	printf("\n");
	return (0);
}

