#ifndef SHELLHEAD_H
#define SHELLHEAD_H

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lsh_loop(void)
char *read_line(void);
char **split_line(char *line);
int _lauch(char **args);
int lsh_execute(char **args);

int lsh_num_builtins();
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);



#endif