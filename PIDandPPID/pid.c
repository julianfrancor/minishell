#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_childpid, my_parentpid;

	/*To get the PID (Process Identification) of a parent process*/
	my_childpid = getpid();
	printf("Child: %u\n", my_childpid);

	/*I'm trying a sleep function, that will put to sleep the process for 2
	seconds in this case, and it will delay the continuation of the process*/
	sleep(2);

	/*To get the PID of a parent process*/
	my_parentpid = getppid();
	printf("Parent: %u\n", my_parentpid);
	return (0);
}
/*
UID       PID   PPID  C STIME  TTY       TIME     CMD
vagrant  10911 10893  0 23:19 pts/2    00:00:00 /bin/bash
*/
