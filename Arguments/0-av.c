
#include <stdio.h>
#include <unistd.h>

/**
 * main - program that prints all the arguments,
 * without using ac.
 *
 * Return: Always 0.
 */

int main(int __attribute__((unused))ac, char **av)
{
	while (*av)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}