#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


extern char **environ;

/**
 * main - function to read a line
 *
 * Return: Always 0.
 */
int main(void)
{
	int i = 0;

	while(environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return(0);
}