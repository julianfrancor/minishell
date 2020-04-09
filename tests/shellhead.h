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

char **_flags(char *buffer, ssize_t characters_read);

#endif
