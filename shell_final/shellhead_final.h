
#ifndef SHELLHEAD_H
#define SHELLHEAD_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFF_SIZE 1024
#define TOK_DELIMITER " \n\r\a\t"
extern char **environ;

char *_getline(void);
int _getchar(void);
char *_getenv(const char *name);
/*----memory_allocators----*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
void *_malloc(unsigned int b);
/*---executer----*/
int execute(char **command, int iterations, char *argv);
/*-----tokenizers---*/
char *_strtok(char *str, const char *delimitador);
char *_strtok_r(char *str, const char *delim, char **saveptr);
char **tokenizer(char *str, const char *delim);
int count_words(char *str_words, const char *delimiter);
unsigned int _strspn(char *s, const char *accept);
unsigned int _strcspn(char *s, const char *reject);
char *_strpbrk(char *s, const char *accept);
char *_strchr(char *s, char c);
/*---- pathfunctions---*/
int pathrunner(char **command, int iterations, char *argv);
char *pathfinder(char *command);
char *pathgetter(char *command);
char *pathcommand(char **result, char *command);
int count_dir(char *str);
/*-----error printer--*/
void command_not_found_handler(char **command, int iterations, char *argv);
void print_number_to_error(int n);
/*----string_fucntion*/
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
/*char *_strchr(char *s, int c);*/
/*Builtins*/
/*int builder(char **cmdpath, int iterations, char *argv);*/
/*int dirchanger(char **args);*/
/*int helper(char **args);*/
char *_getenv(const char *name);
void envbuilt(void);

#endif


