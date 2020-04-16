#include "shellhead.h"

/**
 * controlc - handle to avoid exitting with ctrl+c
 * @s: signal to be evaluated.
 * Return: nothing.
 */
void controlc(int __attribute__ ((unused)) s)
{
	write(1, "\n$ ", 3);
	fflush(stdout);
}
/**
 * main - main function of
 * program simple_shell
 * Return: on succes return 0.
 */
int main(void)
{
	char *lineptr = NULL, **args;
	int status = 1;

	signal(SIGINT, controlc);
	if (isatty(STDIN_FILENO) != 0)
	{
		do {
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
		lineptr = _getline();
		if (lineptr == 0)
			free(lineptr);
		args = tokenizer(lineptr, TOK_DELIMITER);
		status = execute(args);
		free(args);
		free(lineptr);
	}
	return (0);
}
