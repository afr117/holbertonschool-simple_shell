#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOKEN_DELIMITERS " \t\r\n\a"
#define PROGRAM_NAME "hsh" /* Replace "hsh" with the name of your shell */

/* Function prototypes */
char *read_line(void);
char **tokenize_input(char *input);
char **split_commands(char *input);
int execute_commands(char **commands);
int is_builtin(char *command);
void handle_builtin(char **args);
int execute_external(char **args);

#endif /* SHELL_H */
