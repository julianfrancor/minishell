#include "header_shell.h"

/**
 * main - Shell function
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	/*Load config files, if any.*/

	/*Run command loop.*/
	lsh_loop();

	/*Perform any shutdown/cleanup.*/

	return (EXIT_SUCCESS);
}