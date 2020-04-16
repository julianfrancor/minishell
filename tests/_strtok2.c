


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
		if (str[i] != delim)
		{
			for (j = i, letters = 0; str[j] != delim && str[j] != '\0'; j++)
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
