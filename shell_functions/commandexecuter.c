#include "shellhead.h"

/**
 * pathrunner - finds and runs the command given by the user
 * @cmdpath: command to be found.
 * Return: 0 in success
 */
int pathrunner(char **cmdpath)
{
	char *defpath;
	int status;

	if (strcmp("env", cmdpath[0]) == 0 || strcmp("printenv", cmdpath[0]) == 0)
		envbuilt();
	if (strcmp("exit", cmdpath[0]) == 0)
	{
		free(cmdpath[0]);
		free(cmdpath);
		exit(EXIT_SUCCESS);
	}
	defpath = pathfinder(cmdpath[0]);
	if (defpath == NULL)
	{
		perror("$ Command not found, type again...");
		return (1);
	}
	else
	{
		cmdpath[0] = defpath;
		status = execve(cmdpath[0], cmdpath, NULL);
		if (status == -1)
		{
			free(defpath);
			perror("$ Error in execution");
			/*exit(EXIT_FAILURE);*/
			exit(EXIT_FAILURE);
		}
		free(defpath);
		/*exit(EXIT_SUCCESS);*/
		return (0);
	}
}
