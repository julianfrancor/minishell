#include "shellhead_final.h"

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
