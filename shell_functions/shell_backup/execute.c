#include "shellhead.h"
/**
 * execute - executes the cmdpath given by the user
 * @cmdpath: the cmdpath
 * Return: 0 in success
 */
int execute(char **cmdpath)
{
	int status;
	pid_t pid;

	if (*cmdpath == NULL)
	{
		return (1);
	}
	pid = fork(); /* We will start a Child process with Fork */
	if (pid == 0) /*Child process*/
	{
		if (_strchr(cmdpath[0], '/') != NULL)
		{
			if (execve(cmdpath[0], cmdpath, environ) == -1)
			{
				perror("$ Execution error");
				/*exit(EXIT_FAILURE);*/
				free(cmdpath);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			return (pathrunner(cmdpath));
		}
	}
	else if (pid == -1) /*to check error forking*/
	{
		perror("$ No child process was created");
		free(cmdpath);
		return (1);
	}
	/*Parent process*/
	else
	{
		/*suspends execution of the parent process*/
		 /*until a child specified by pid argument has changed state.*/
		 /*Make the parent wait for any signal from the child*/
		waitpid(-1, &status, 0);
	}
	return (1);
}
