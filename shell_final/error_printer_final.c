#include "shellhead_final.h"

/**
 * command_not_found_handler- function that prints error message
 * when the command is not found
 * @command: command not found.
 * @iterations: number of interations of the shell program
 * @argv: command passed through the prompt
 * Return: void
 */
void command_not_found_handler(char **command, int iterations, char *argv)
{
	write(STDERR_FILENO, argv, _strlen(argv));
	write(STDERR_FILENO, ": ", 2);
	print_number_to_error(iterations);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command[0], _strlen(command[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * print_number_to_error- function that
* prints an integer casted to char
* @n: input is an intiger
* Return: void
*/
void print_number_to_error(int n)
{
	char number[2];

	while (n / 10)
	{
		print_number_to_error(n / 10);
		break;
	}
	number[0] = ((n % 10) + '0');
	number[1] = '\0';
	write(STDERR_FILENO, number, 1);
}
