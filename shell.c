#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function to read a line of input */
char *lsh_read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/* Function to split a line into individual commands */
char **lsh_split_line(char *line) {
    char **tokens = malloc(64 * sizeof(char *));
    char *token;
    int index = 0;

    if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[index] = token;
        index++;

        if (index >= 64) {
            fprintf(stderr, "shell: too many tokens\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[index] = NULL;
    return tokens;
}

/* Function to execute the commands */
int lsh_execute(char **commands) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(commands[0], commands) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("shell");
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    return 1;
}

int main(void) {
    char *line;
    char **commands;
    int status = 1; /* Shell status (1: active, 0: exit) */

    while (status) {
        printf("($) ");
        line = lsh_read_line(); /* Read input line */
        if (!line)
            break;

        commands = lsh_split_line(line); /* Split input into commands */

        if (commands) {
            status = lsh_execute(commands); /* Execute commands */
            free(commands);
        }
        free(line);
    }

    return (0);
}

