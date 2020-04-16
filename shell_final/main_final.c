#include "shellhead_final.h"

/**
 * controlc - handle to avoid exitting with ctrl+c
 * @s: signal to be evaluated.
 * Return: nothing.
 */
void controlc(int __attribute__ ((unused)) s)
{
	write(1, "\n", 1);
	write(1, "$ ", 2);
	fflush(stdout);
}

/**
 * main - main function of
 * program simple_shell
 * @argc: argument count
 * @argv: array of strings
 * Return: 0 for success
 */
int main(int __attribute__((unused))argc, char **argv)
{
	char *lineptr = NULL, **args;
	int status = 1, iterations = 1;


	if (isatty(STDIN_FILENO) != 0)
	{
		signal(SIGINT, controlc);
		do {
			write(STDOUT_FILENO, "$ ", 2);
			lineptr = _getline();
			iterations++;
			if (lineptr == 0)
			{
				free(lineptr);
				continue;
			}
			args = tokenizer(lineptr, TOK_DELIMITER);
			status = execute(args, iterations, argv[0]);
			free(args);
			free(lineptr);
		} while (status);
	}
	else
	{
		lineptr = _getline();
		if (lineptr == 0)
			free(lineptr);
		args = tokenizer(lineptr, TOK_DELIMITER);
		status = execute(args, iterations, argv[0]);
		free(args);
		free(lineptr);
	}
	return (0);
}
