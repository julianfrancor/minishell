#include "shellhead.h"

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
		/*Handle the comments*/
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
