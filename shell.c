#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *find_command(char *command) {
    char *path = getenv("PATH");
    char *dir, *full_path;

    while ((dir = strtok(path, ":"))) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path) {
            perror("shell");
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            return full_path;
        }

        free(full_path);
        path = NULL;
    }

    return NULL;
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

int lsh_execute(char **commands) {
    pid_t pid;
    int status;
    char *command_path = find_command(commands[0]);

    if (command_path == NULL) {
        fprintf(stderr, "Command not found: %s\n", commands[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        if (execvp(command_path, commands) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        waitpid(pid, &status, 0);
    }

    free(command_path);
    return 1;
}

int main(void) {
    char *line;
    char **commands;
    int status = 1;

    while (status) {
        printf("($) ");
        line = lsh_read_line();
        if (!line)
            break;

        commands = lsh_split_line(line);
        if (commands) {
            status = lsh_execute(commands);
            free(commands);
        }
        free(line);
    }

    return (0);
}

