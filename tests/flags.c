#include "shellhead.h"
/**
 * flag - separates the command line and the flags
 * @buffer: pointer that sets the line
 * @characters_read:  
 * Return: the flags
 */
char **_flags(char *buffer, ssize_t characters_read)
{
	char **flag;
	int i = 0, j = 0;

	char *token = strtok(buffer, " ");
	flag = malloc(sizeof(char *) * 20);
	*flag = malloc(sizeof(char) * characters_read);
	if (!flag)
	{
		for(j = 0; flag[j]; j++)
			free(flag[j]);
		free(flag);
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		flag[i] = token;
		token = strtok(NULL, " ");
		i++;
		
	}
		
	flag[i] = NULL;
	flag[i - 1] = strtok(flag[i - 1], "\n");

	return(flag);
}
