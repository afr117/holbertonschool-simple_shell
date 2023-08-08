#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64

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
            int exec_status = lsh_execute(commands);

            for (i = 0; commands[i] != NULL; i++) {
                free(commands[i]);
            }
            free(commands);

            if (exec_status == 0) {
                break; /* Exit the loop on successful command execution */
            }
        }
        free(line);
    }

    return 0;
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

    token = strtok(line, " \t\n"); /* Updated delimiter */
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n"); /* Updated delimiter */
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_execute(char **commands) {
    pid_t pid;
    int exec_status = 0; /* Return status for successful execution */

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(commands[0], commands) == -1) {
            perror("shell");
            exec_status = 1; /* Set exec_status to indicate failure */
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("shell");
        exec_status = 1; /* Set exec_status to indicate failure */
    } else {
        /* Parent process */
        waitpid(pid, NULL, 0);
    }

    return exec_status;
}

