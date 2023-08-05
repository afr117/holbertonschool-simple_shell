#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* Function to read a line of input */
char *lsh_read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/* Function to split a line into individual commands */
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

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

/* Function to find the command's full path in the PATH */
char *find_command(char *command) {
    /* Implement the logic to find the command in the PATH here */
    /* Return the full path of the command if found, or NULL if not found */
    /* You can use the "access" function to check if a file exists */
    /* You'll need to tokenize the PATH environment variable and iterate over the directories */

    /* Temporarily suppress the unused parameter warning */
    (void)command;

    return NULL;
}

/* Function to execute the commands */
int lsh_execute(char **commands) {
    pid_t pid;
    int status;

    char *command_path = find_command(commands[0]);
    if (!command_path) {
        fprintf(stderr, "shell: command not found: %s\n", commands[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(command_path, commands) == -1) {
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

    free(command_path);
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

