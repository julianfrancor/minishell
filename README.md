
# Basic lifetime of a shell

## A shell does three main things in its lifetime.

 - Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.

 - Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
	*	Read: Read the command from standard input.
	*	Parse: Separate the command string into a program and arguments.
	*	Execute: Run the parsed command.

 - Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

## Basic loop of a shell

So we’ve taken care of how the program should start up. Now, for the basic program logic: what does the shell do during its loop? Well, a simple way to handle commands is with three steps:

Read: Read the command from standard input.
Parse: Separate the command string into a program and arguments.
Execute: Run the parsed command.