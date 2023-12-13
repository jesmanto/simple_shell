#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
extern char **environ;
extern void free(void *__ptr) __THROW;
void show_prompt(void);
int compare_env_variables(const void *a, const void *b);
int execute_if_abs_path(const char *command, char *const args[]);
int execute_search_path(const char *command, char *const args[]);
int launch_command(const char *command_line);
char *_getenv(const char *cmd_name);
int execute_env(void);
int launch_env(void);
void print_error(const char *cmd_line, const char *message, int line_number);
int search_command_in_path(const char *command, char *command_path);
void handle_exit_command(const char *command_line);
char *_strdup(const char *str);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delim);
int setenv_command(const char *command_line);
int unsetenv_command(const char *command_line);
int cd_previous(void);
int cd_home(void);
int cd_command(const char *command_line);
#endif
