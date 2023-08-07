#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **commands);

int main(void) {
    char *line;
    char **commands;
    int status = 1; /* Shell status (1: active, 0: exit) */
    int i; /* Declare 'i' outside of the loop in C89 */

    while (status) {
        printf("($) ");
        line = lsh_read_line();
        if (!line)
            break;

        commands = lsh_split_line(line);
        if (commands) {
            pid_t pid;
            int exec_status;

            pid = fork();
            if (pid == 0) {
                /* Child process */
                if (execvp(commands[0], commands) == -1) {
                    perror("shell");
                    exit(EXIT_FAILURE); /* Important: Exit the child process on error */
                }
            } else if (pid < 0) {
                /* Error forking */
                perror("shell");
            } else {
                /* Parent process */
                waitpid(pid, &exec_status, 0);
            }

            /* Free memory allocated for commands */
            for (i = 0; commands[i] != NULL; i++) {
                free(commands[i]);
            }
            free(commands);
        }
        free(line);
    }

    return 0; /* Return 0 to indicate successful completion */
}

char *lsh_read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **lsh_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = strdup(token); /* Duplicate the token */
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

