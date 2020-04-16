#include "shellhead.h"
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
		if (!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		free(ptr);
		return (p2); }
	if (new_size == 0 && ptr != NULL)
	{ free(ptr);
		return (NULL); }
	if (old_size > new_size)
	{ p2 = (char *)_calloc(new_size, sizeof(char));
		if (!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		for (i = 0; i < new_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2); }
	if (new_size > old_size)
	{ p2 = (char *)_calloc(new_size, sizeof(char));
		if (!p2)
		{ perror("$ Error in memory allocation");
			return (ptr); }
		for (i = 0; i < old_size; i++)
			p2[i] = aux[i];
		free(ptr);
		return (p2); }
	return (ptr);
}
