#include "shellhead_final.h"

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
 * _strtok - function that
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
	return (token);
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
	/*here we are moving the first pointer, the number of bytes*/
	/*that had a coincidence with the delimiters.*/
	str += _strspn(str, delim);
	if (*str != '\0')
	{
		/*Here we take the first pointer to a token*/
		token = str;
		/*here we are moving the pointer, the number of bytes*/
		/*that didn't match with the delimiters, so we can skip the token*/
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
		if (str_words)
			str_words += _strspn(str_words, delimiter);
		/*Increment the word counter*/
		palabras++;
	} while (str_words && *str_words);

	return (palabras);
}
