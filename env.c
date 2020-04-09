#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * main - function to read a line
 *
 * Return: Always 0.
 */
int main(int ac, char  **av, char **env)
{
	int i = 0, j = 0, k = 0;

	while(k < ac)
	{
		printf("%s\n", av[k]);
		k++;
	}

	while(environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	printf("\n");
	while(env[j] != NULL)
	{
		printf("%s\n", env[j]);
		j++;
	}

	return(0);
}
