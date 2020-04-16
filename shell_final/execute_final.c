#include "shellhead_final.h"

/**
 * execute - executes the commnad given by the user
 * @command: all the command parsed by tokens
 * @iterations: number of iterations of the program
 * stored in an array of pointers.
 * @argv: array of strings
 * Return: 0 in success
 */
int execute(char **command, int iterations, char *argv)
{
	int status;
	pid_t pid;

	if (*command == NULL)
		return (1);

	pid = fork(); /* We will start a Child process with Fork */
	if (pid == 0) /*Child process*/
	{
		/*If slashes, shell doesn't use PATH to find the executable file.*/
		if (_strchr(command[0], '/') != NULL)
		{
			if (execve(command[0], command, environ) == -1)
			{
				perror("$ Execution error");
				free(command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/*If not slashes the shell looks for the executable file in PATH*/
			return (pathrunner(command, iterations, argv));
		}
	}
	else if (pid == -1) /*to check error forking*/
	{
		perror("$ No child process was created");
		free(command);
		return (1);
	}
	/*Parent process*/
	else
	{
		 /*Make the parent wait for any signal from the child*/
		waitpid(-1, &status, 0);
	}
	return (1);
}
