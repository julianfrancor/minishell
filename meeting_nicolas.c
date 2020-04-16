#ifndef SHELLHEAD_H
#define SHELLHEAD_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 1024
#define TOK_DELIMITER " \n\r\a\t"
extern char **environ;

char *_getline(void);
int _getchar(void);
char *_getenv(const char *name);
/*----memory_allocators----*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
void *_malloc(unsigned int b);
/*---executer----*/
int execute(char **args);
/*-----tokenizers---*/
char *_strtok(char *str, const char *delimitador);
char *_strtok_r(char *str, const char *delim, char **saveptr);
char **tokenizer(char *str, const char *delim);
int count_words(char *str_words, const char *delimiter);
unsigned int _strspn(char *s, const char *accept);
unsigned int _strcspn(char *s, const char *reject);
char *_strpbrk(char *s, const char *accept);
char *_strchr(char *s, char c);
/*---- pathfunctions---*/
int pathrunner(char **args);
char *pathfinder(char *command);
char **pathgetter(void);
char *pathcommand(char **result, char *command);
/*----string_fucntion*/
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
/*char *_strcat(char *dest, char *src);*/
/*char *_strchr(char *s, int c);*/
char *_getenv(const char *name);

#endif

/**
 * main - main function of
 * program simple_shell
 * Return: on succes return 0.
 */
int main(void)
{
	char *lineptr = NULL, **args;
	int status = 0;

	if(isatty(STDIN_FILENO))
	{
		do {
			/*prints prompt*/
			
				write(STDOUT_FILENO, "$ ", 2);

			lineptr = _getline();
			if (lineptr == 0)
			{
				free(lineptr);
				continue;
			}
			args = tokenizer(lineptr, TOK_DELIMITER);
			status = execute(args);
			free(args);
			free(lineptr);
			lineptr = NULL;
		} while (status);
	}
	else
	{
		/* code */
	}
	
	return (0);
}

/**
 * _getchar - function to read
 * characters form the STDIN_FILENO
 * Return: the character read as an
 * unsigned char cast to an int or
 * EOF on end of file or error.
 */
int _getchar(void)
{
	ssize_t file_descriptor = 0, file_position = 0;
	char temp_buffer[1], *read_char;

	/*READ, char from the STDIN_FILENO*/
	file_position = read(file_descriptor, temp_buffer, 1);
	/*When read fails, -1 is returned, and errno is set appropriately.*/
	if (file_position == -1)
	{
		perror("$ Error reading from Standard Input");
		return (0);
	}
	else if (file_position > 0)
	{
		read_char = temp_buffer;
		return ((int)*read_char);
	}
	/*When we hit End-of-file,*/
	return (EOF);
}

/**
 * _getline - function to reads a line
 * form the STDIN_FILENO and holds it in a buffer.
 * Return: a buffer with the chars read form
 * the command line or
 */
char *_getline(void)
{
	char *buffer = "";
	unsigned int buffsize = BUFF_SIZE, buffsize_new = 0, i = 0;
	int chars_read;

	buffer = (char *)_calloc(buffsize + 1, sizeof(char));
	if (!buffer)
	{ perror("$ Error allocating memory");
		return (NULL); }
	while (1)
	{
		chars_read = _getchar();
		/*To manage the Ctrl + D command and exit the program*/
		if (chars_read == EOF)
		{ free(buffer);
			exit(EXIT_SUCCESS); }
		/*User hits enter and handle the spaces followed by a new line*/
		else if (chars_read == '\n')
		{ buffer[i] = '\0';
			return (buffer); }
		buffer[i] = chars_read;
		if (chars_read == '#')
			buffer[i] = 0;
		i++;
		if (i >= buffsize)
		{
			buffsize_new = buffsize + BUFF_SIZE;
			buffer = _realloc(buffer, buffsize, buffsize_new);
			buffsize = buffsize_new;
			if (!buffer)
			{ free(buffer);
				perror("$ Error reallocating memory");
				exit(EXIT_FAILURE); }
		}
	}
	return (buffer);
}

/**
 * tokenizer - function that splits
 * a string into tokens and place them
 * in a double pointer.
 * @str: input string to be parsed
 * @delim: array of delimiters of type constant char
 * Return: double pointer or NULL if it fails.
 */
char **tokenizer(char *str, const char *delim)
{
	static char *str_holder;
	char **array = NULL, *token_holder = NULL;
	int words = 0, i = 0;
	/*First: Malloc to the pointers. How many words we have in that full string*/
	words = count_words(str, delim);
	if (words == 0)
		return (0);
	/*Allocating space for the words we have and one space null at the end*/
	array = (char **)_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	token_holder = _strtok_r(str, delim, &str_holder);
	while (token_holder != NULL)
	{
		array[i] = token_holder;
		token_holder = _strtok_r(NULL, delim, &str_holder);
		i++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * strtok - function that
 * splits a string into words.
 * @str: string to be parsed
 * @delimitador: array of delimiters
 * Return: char
 */
char *_strtok(char *str, const char *delimitador)
{
	static char *str_holder;
	char *token = NULL;

	token = _strtok_r(str, delimitador, &str_holder);
	return(token);
}

/**
 * _strtok_r - function that
 * breaks a string into a sequence of zero or more nonempty tokens.
 * is a reentrant version strtok().
 * @str: string to be parsed.
 * @delim: array of delimiters
 * @saveptr: pointer to a char * variable that is used internally
 * by strtok_r() in order to maintain context between successive
 * calls that parse the same string.
 * Return: pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *token = NULL;

	if (str == '\0')
		str = *saveptr;
	/*here we are moving the first pointer, the number of bytes
	that had a coincidence with the delimiters.*/
	str += _strspn(str, delim);
	if(*str != '\0')
	{
		/*Here we take the first pointer to a token*/
		token = str;
		/*here we are moving the pointer, the number of bytes
		that didn't match with the delimiters, so we can skip the token*/
		str += _strcspn(str, delim);
		if (*str != '\0')
		{
			/*here we set null to the string to terminate the token*/
			*str++ = '\0';
		}
	}
	*saveptr = str;

	return (token);
}

/**
 * count_words - function that
 * counts the words in a string
 * @str_words: the string to be parsed
 * @delimiter: the delimiters
 * Return: int
 */
int count_words(char *str_words, const char *delimiter)
{
	int palabras = 0;

	do {
		str_words = _strpbrk(str_words, delimiter);
		/*skip the delimiter*/
		if(str_words)
			str_words += _strspn(str_words, delimiter);
		/*Increment the word counter*/
		palabras++;
	} while(str_words && *str_words);

	return (palabras);
}

/**
 * _strspn - function that
 * gets the length of a prefix substring.
 * this function will count the number of delimiters in our string
 * @s: string is char
 * @accept: substring is char to compare
 * Return: unsigned int
 */
unsigned int _strspn(char *s, const char *accept)
	{
	unsigned int i, j, cont = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		j = 0;
		while (accept[j] != 0)
		{
			if (s[i] == accept[j])
			{
				cont++;
				break;
			}
			j++;
		}
		if (accept[j] == '\0')
			break;
	}
	return (cont);
	}

/**
 * _strcspn - function calculates the length of the initial segment
 * of s which consists entirely of bytes not in reject.
 * This function will count the letters
 * @s: string is char
 * @reject: substring is char to compare
 * Return: unsigned int
 */
unsigned int _strcspn(char *s, const char *reject)
{
	unsigned int i, j, cont = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		j = 0;
		while (reject[j] != 0)
		{
			if (s[i] == reject[j])
			{
				return (cont);
			}
			j++;
		}
		cont++;
	}
	return (cont);
}

/**
 * _strpbrk - function that
 * searches a string for any of a set of bytes.
 * @s: string is char
 * @accept: substring is char to compare
 * Return: unsigned int
 */
char *_strpbrk(char *s, const char *accept)
{
	unsigned int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				return (&s[i]);
			}
		}
	}
	if (s[i] == 0)
	{
		return (0);
	}
	return (&s[i]);
}

/**
 * _strchr - function that
 * locates a character in a string.
 * @s: pointer is char
 * @c: variable is char
 * Return: char
 */
char *_strchr(char *s, char c)
{
	int len, i;
	len = 0;

	/*finding the lenght of the string*/
	while (s[len] != '\0')
	{
		len++;
	}
	/*finding the position of c in *s */
	for (i = 0; i <= len; i++)
	{
		if (s[i] == c)
		{
			s = &s[i];
			/*once you find the first c break*/
			break;
		}
			/*here we are setting the whole string as NULL*/
		else if (s[i] == 0)
		{
			s = 0;
		}
	}
	return (s);
}

/**
 * execute - executes the arguments given by the user
 * @arguments: the arguments
 * Return: 0 in success
 */
int execute(char **arguments)
{
	int status;
	pid_t pid;

	if (*arguments == NULL)
	{
		return (1);
	}
	pid = fork(); /* We will start a Child process with Fork */
	if (pid == 0) /*Child process*/
	{
		if (_strchr(arguments[0], '/') != NULL)
		{
			if (execve(arguments[0], arguments, environ) == -1)
			{
				perror("$ Execution error");
				/*exit(EXIT_FAILURE);*/
				return (0);
			}
		}
		else
		{
			return (pathrunner(arguments));
		}
	}
	else if (pid == -1) /*to check error forking*/
	{
		perror("$ No child process was created");
		return (1);
	}
	/*Parent process*/
	else
	{
		/*suspends execution of the parent process*/
		 /*until a child specified by pid argument has changed state.*/
		 /*Make the parent wait for any signal from the child*/
		waitpid(-1, &status, 0);
	}
	return (1);
}

/**
 * pathrunner - finds and runs the command given by the user
 * @arguments: command to be found.
 * Return: 0 in success
 */
int pathrunner(char **arguments)
{
	char *defpath;
	int status;

	defpath = pathfinder(arguments[0]);
	if (defpath == NULL)
	{
		perror("$ Command not found, type again...");
		return (0);
	}
	else
	{
		arguments[0] = defpath;
		status = execve(arguments[0], arguments, NULL);
		if (status == -1)
		{
			free(defpath);
			perror("$ Error in execution");
			return (0);
			/*exit(EXIT_FAILURE);*/
		}
		free(defpath);
		/*exit(EXIT_SUCCESS);*/
		return (0);
	}
}

/**
 * pathfinder - function to find the path of environment var
 * @command: command to be used in the shell
 * Return: the path found.
 */
char *pathfinder(char *command)
{
	char **cmdpath = pathgetter(); /*it gets the path*/
	char *result;

	result = pathcommand(cmdpath, command); /*concat the commmand with the path*/
	return (result);
}

/**
 * pathcommand - function to concatenate the path with the command
 * @result: command path found
 * @command: command given by the user
 * Return: the path found
 */
char *pathcommand(char **result, char *command)
{
	char *pathcomplete;
	int ffile, lencom, lenre;

	if (command == NULL || result == NULL)
	{
		return (NULL);
	}

	while (*result != NULL)
	{
		lencom = _strlen(command);
		lenre =  _strlen(*result);
		pathcomplete = _calloc(lencom + 2 + lenre, sizeof(char));
		if (pathcomplete == NULL)
		{
			perror("Error allocating memory");
			return (NULL);
		}
		strcat(pathcomplete, *result);
		strcat(pathcomplete, "/");
		strcat(pathcomplete, command);

		ffile = access(pathcomplete, F_OK);
		if (ffile != -1)
		{
			return (pathcomplete);
		}
		free(pathcomplete); /* might be result */
		result++;
	}
	return (NULL);
}
/**
 * count_dir - function that counts the amount of directories.
 * @str: the full path to be counted.
 * Return: the amount of directories
 */
int count_dir(char *str)
{
	int i = 0, words = 0;

	for (i = 0; str[i]; i++)
	{
	if (str[i] != ':' && (str[i + 1] == ':' || str[i + 1] == '\0'))
		words++;
	}
	return (words + 1);
}
/**
 * pathgetter - function to extract the full path of environment var
 * Return: the path found.
 */
char **pathgetter(void)
{
	char *ptrenv, *tok, **result;
	unsigned int words, i;

	ptrenv = _getenv("PATH");
	/*
	*if (ptrenv == NULL)
	*return (NULL);
	*/
	words = count_dir(ptrenv);
	result = _calloc(words + 1, sizeof(char *));
	if (result == NULL)
	{
		perror("Error: memory allocation failed");
		return (NULL);
	}
	tok = _strtok(ptrenv, ":"); /* missing a line */
	*result = tok;
	for (i = 1; i < words; i++) /*i starts at one */
	{
		tok = _strtok(NULL, ":"); /*might be inverted */
		*(result + i) = tok;
	}
	*(result + i) = NULL;
	return (result);
}

/**
 * _getenv - get the enviroment variable from environ
 * @name: the name of the env var
 * Return: the pointer of the var.
 */
char *_getenv(const char *name)
{
	char *tok, *s;
	int i = 0;
	char *tmpenv;
	const char *delim = "=";

	i = 0;
	while (environ[i])
	{
		/* avoids the environ var */
		tmpenv = _strdup(environ[i]);
		/* parse the full path */
		tok = _strtok(tmpenv, delim);
		if (strcmp(name, tok) == 0)
		{
			tok = _strtok(NULL, delim);
			/* avoid valgrind error */
			s = _strdup(tok);
			/*free(tmpenv);*/
			return (s);
		}
		free(tmpenv);
		i++;
	}
	return (NULL);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: the size of the char
 * Return: a pointer of char
 */
char *_strdup(char *str)
{
	char *ar;
	unsigned int i, j, len = 0;

	if (str == NULL)
	{
		return (NULL);
	}
	for (j = 0; str[j] != '\0'; j++)
	{
		len++;
	}
	len++;
	ar = malloc(len * sizeof(char));
	if (ar == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < len; i++)
	{
		ar[i] = str[i];
	}
	return (ar);
}
/**
 * _strcmp - function to compare two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: the copier pointer
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	for (i = 0; (s1[i] == s2[i]) && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
	}
	return (s1[i] - s2[i]);
}

/**
* _strcpy - writes the character c to stdout
* @dest: The character to print
* @src: source of char
* Return: string copied
*/
char *_strcpy(char *dest, char *src)
{
	int r;

	for (r = 0; src[r] != '\0'; r++)
	{
		dest[r] = src[r];
	}
	dest[r] = '\0';
	return (dest);
}

/**
 * _strcat - write a function that concatenates two strings
 * @dest: destiny string
 * @src: source string
 * Return: string concatenated
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	dest[i++] = '/';
	while ((dest[i++] = src[j++]) != '\0')
	{
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strlen - function to counts the amount of characters in a string
 * @s: The character to be counted
 * Return: number of characters.
 */
int _strlen(char *s)
{
	int leng = 0;

	while (*s != '\0')
	{
		s++;
		leng++;
	}
	return (leng);
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
	{ p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		free(ptr);
		return (p2); }
	if (new_size == 0 && ptr != NULL)
	{ free(ptr);
		return (NULL); }
	if (old_size > new_size)
	{ p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		for (i = 0; i < new_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2); }
	if (new_size > old_size)
	{ p2 = (char *)_calloc(new_size, sizeof(char));
		if(!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		for (i = 0; i < old_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2); }
	return (ptr);
}
