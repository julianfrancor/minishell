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
	char *lineptr;
	size_t n = 0;
	ssize_t characters_read;

	while (1)
	{
		lineptr = malloc(sizeof(char));

		/*Print the prompt*/
		printf("$ ");
		/*Read the line that the user typed */
		characters_read = getline(&lineptr, &n, stdin);
		/*Checking if this getline fails*/
		if (characters_read != -1)
		{
			/*setting the tail of the buffer written by getline to NULL
			instead of line break (\n)*/
			/*while (lineptr[i])
			{
				i++;
			}*/
			
			lineptr = strtok(lineptr, "\n");
			printf("hola %s]\n", lineptr);
			printf("Getline function returned: %lu\n", characters_read);
			printf("n: %lu\n", n);
		}
		
		free(lineptr);
	}
	return(0);
}
