#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * main - function to read a line
 *
 * Return: Always 0.
 */
int main(void)
{
	char *builtins = NULL;
	char *builtins_path = {"/bin/"};
	size_t n = 1024;
	ssize_t characters_read;

	printf("$ ");

	characters_read = getline(&builtins, &n, stdin);

	if (characters_read != -1)
	{
		printf("%s", builtins);
		builtins_path = strcat(builtins_path, builtins);
	}



	execve()
	
	free(builtins);
	return(0);
}