#ifndef SHELLHEAD_H
#define SHELLHEAD_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
int execute(char **args);
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
int pathrunner(char **cmdpath);
char *pathfinder(char *command);
char **pathgetter(void);
char *pathcommand(char **result, char *command);
int count_dir(char *str);
/*----string_fucntion*/
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
/*char *_strcat(char *dest, char *src);*/
/*char *_strchr(char *s, int c);*/
char *_getenv(const char *name);
void envbuilt(void);

#endif
