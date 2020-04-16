#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 2

char *_getline(void);
/*int _strcmp(char *s1, char *s2);*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
void *_malloc(unsigned int b);
char **_strtok(char *str, const char *delim);
int execute(char **args);



/**
 * main - function to read a line
 *
 * Return: Always 0.
 */
int main(void)
{
	char *lineptr = NULL, **args;
	int k = 0, status = 0;

	while (status == 0)
	{
		write(STDOUT_FILENO,"$ ", 2);

		lineptr = _getline();
		if (lineptr == 0)
		{
			free(lineptr);
			continue;
		}
		args = _strtok(lineptr, " ");
		status = execute(args);
		for (k = 0; args[k]; k++)
			free(args[k]);
		free(args);
		free(lineptr);
	}

	/*for (k = 0; args[k]; k++)
			free(args[k]);
		free(args[k]);
		free(args);
		free(lineptr);
		lineptr = NULL;*/
	return (0);
}

/**
 * _getline - function to read a line
 *
 * Return: Always 0.
 */

char *_getline(void)
{
	char *buffer = "";
	unsigned int buffsize = BUFF_SIZE, buffsize_new = 0, i = 0;
	int chars_read = 0;

	buffer = (char *)_calloc(buffsize + 1, sizeof(char));
	if (!buffer)
	{
		perror("$ Error allocating memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		chars_read = _getc(stdin);
		/*To manage the Ctrl + D command and exit the program*/
		if (i == 0 && (chars_read == EOF))
		{
			free(buffer);
			exit(0);
		}
		/*Feature to handle memory frees when user hits enter*/
		if (i == 0 && (chars_read == '\n'))
		{
			free(buffer);
			return (0);
		}
		

		/*with we want handle the spaces followed by a new line*/
		/*if (i == 0 && (chars_read == '\n' || chars_read == ' '))
		{
			free(buffer);
			return (0);
		}*/
		/*when EOF replace it with a null character and return.*/
		if (chars_read == '\n' || chars_read == EOF)
		{
			buffer[i] = '\0';
			return (buffer);
		}
		buffer[i] = chars_read;
		i++;

		/*Aqui modeifique esta condicion Profe*/
		if ((i >= buffsize) && (chars_read != '\n'))
		{
			buffsize_new = buffsize + BUFF_SIZE;
			buffer = _realloc(buffer, buffsize, buffsize_new);
			buffsize = buffsize_new;
			if (!buffer)
			{
				free(buffer);
				perror("$ Error allocating memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * count_words - function that
 * counts the words in a string
 * @str_words: char
 * Return: int
 */
int count_words(char *str_words)
{
	int i = 0, palabras = 0;

	for (i = 0; str_words[i]; i++)
	{
		/*counting the number of words in the str*/
		if (str_words[i] != ' ' &&
		(str_words[i + 1] == ' ' || str_words[i + 1] == '\0'))
			palabras++;
	}
	return (palabras);
}

/**
 * strtok - function that
 * splits a string into words.
 * @str: char
 * Return: char
 */
char **_strtok(char *str, const char *delim)
{
	int i = 0, j = 0, words = 0, letters = 0, k = 0, q = 0;
	char **array = NULL;

	if (str[0] == 0 || str == NULL)
		return (NULL);
/*PRIMERO: MALLOC A LOS PUNTEROS how many words we have in that full string*/
	words = count_words(str);
	if (words == 0)
		return (NULL);
	/*Allocating space for the words we have and one space null at the end*/
	array = (char **)_calloc((words + 1), sizeof(char *));
	if (!array)
	{
		return (NULL);
	}
/*SEGUNDO: MALLOC A LETRAS EN DE CADA PUNTERO, letters we have on each word*/
	for (i = 0; (str[i] != 0) && (k < words); i++)
	{
		if (strcmp((const char)str[i], (const char)delim) != 0)
		{
			for (j = i, letters = 0; str[j] != *delim && str[j] != '\0'; j++)
			{
				letters++;
			}
			array[k] = (char *)_calloc((letters + 1), sizeof(char));
			if (!array[k])
			{
				for (k = k - 1; k >= 0; k++)
					free(array[k]);
				free(array);
				return (0);
			}
			for (q = 0; q < letters; q++, i++)
				array[k][q] = str[i];
			array[k++][q] = '\0';
		}
	}
	array[k] = '\0';
	return (array);
}

/**
 * execute - function to execute a program
 *
 * Return: Always 0.
 */

int execute(char **arguments)
{
	int k = 0;
	pid_t pid;

	/* We will start a Child process with Fork */
	pid = fork();
	/*to check error forking*/
	if (pid == -1)
	{
		for (k = 0; arguments[k]; k++)
			free(arguments[k]);
		free(arguments);
		perror("$ No child process was created");
		return (1);
	}
	/*Child process*/
	else if (pid == 0)
	{
		if (execve(arguments[0], arguments, NULL) == -1)
		{
			perror("$ Execution error");
			exit(EXIT_FAILURE);
		}
			for (k = 0; arguments[k]; k++)
				free(arguments[k]);
			free(arguments);
			exit(EXIT_SUCCESS);
	}
	/*Parent process*/
	else
	{
	/*Make the parent wait for any signal from the child*/
		wait(NULL);
	}
	return(0);
}

/**
 * _realloc - function that
 * function that creates an array of integers.
 * @ptr: void pointer
 * @old_size: unsigned int
 * @new_size: unsigned int
 * Return: void
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p2 = NULL, *aux = "";
	unsigned int i = 0;

	aux = ptr;
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{
			perror("$ Error in memory allocation");
			return (ptr);
		}
		free(ptr);
		return (p2);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (old_size > new_size)
	{
		p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{
			perror("$ Error in memory allocation");
			return (ptr);
		}
		for (i = 0; i < new_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2);
	}
	if (new_size > old_size)
	{
		p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{
			perror("$ Error in memory allocation");
			return (ptr);
		}
		for (i = 0; i < old_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2);
	}
	return (ptr);
}

/**
 * _calloc - function that
 * allocates memory for an array, using malloc
 * The _calloc function allocates memory for an array of nmemb elements
 * of size bytes each and returns a pointer to the allocated memory.
 * @nmemb: number of elements
 * @size: size of each element
 * Return: void
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;
	unsigned int i = 0;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = _malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	for (i = 0; i < (nmemb * size); i++)
	{
		ptr[i] = 0;
	}
	return (ptr);
}

/**
 * _malloc - function that
 * allocates memory using malloc.
 * and checkes if the allocation fails.
 * if so, terminates with exit 98.
 * @b: unsigned int parametrer
 * Return: void
 */

void *_malloc(unsigned int b)
{
	char *ptr;

	ptr = malloc(sizeof(char) * b);
	if (!ptr)
	{
		exit(98);
	}
	return (ptr);
}

/**
 * _strcmp - function that compares two strings.
 * @s1: input is array
 * @s2: input is array
 * Return: char
 */

/*int _strcmp(char *s1, char *s2)
{
	int i, j;

	i = 0;

	while (s1[i] != 0 || s2[i] != 0)
	{
		j = s1[i] - s2[i];
		if (j != 0)
		{
			return (j);
		}
	i++;
	}

	return (j);
}*/
