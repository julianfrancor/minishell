#include "shellhead_final.h"

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
	int len = 0, i;

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
