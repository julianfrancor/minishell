# Simple Shell

Writing our own Simple Shell

#### [Simple Shell](https://intranet.hbtn.io/projects/235)

## General Information

 - PID & PPID
 - Arguments
 - Executing a program
 - Creating processes
 - Wait
 - File information
 - Environment

## Basic lifetime of a shell

A shell does three main things in its lifetime.
```
 - Initialize: In this step, a typical shell would read and execute its configuration files.
 These change aspects of the shell’s behavior.

 - Interpret: Next, the shell reads commands from stdin (which could be interactive, or a
 file) and executes them.
	*	Read: Read the command from standard input.
	*	Parse: Separate the command string into a program and arguments.
	*	Execute: Run the parsed command.

 - Terminate: After its commands are executed, the shell executes a shutdown command
 frees up the memory, and terminates.
```
## Basic loop of a shell

The basic logic of the program: the shell has a loop that handle commands in three steps:

	*	Read: Read the command from standard input. (getline())
	*	Parse: Separate the command string into a program and arguments. (strtok())
	*	Execute: Run the parsed command. (fork() & execve())


##  Prerequisites

You need to install this software
```
- VirtualBox - Virtual Machine
- Vagrant
- Ubuntu trusty 64
- Emacs
- Vim/Vi
- VSCode
```

##  Authors

[GitHub - Julian Franco Rua](https://github.com/julianfrancor)

[GitHub - Oscar Henao Hidalgo](https://github.com/davehh1211)