#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64

char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **commands, char *full_path);

int main(void) {
    char *line;
    char **commands;
    int status = 1; /* Shell status (1: active, 0: exit) */
    int i; /* Declare 'i' outside of the loop in C89 */
    char *path, *token, *full_path;
    int found = 0;
    pid_t pid;
    int exec_status;

    while (status) {
        printf("($) ");
        line = lsh_read_line();
        if (!line)
            break;

        commands = lsh_split_line(line);
        if (commands) {
            path = getenv("PATH");
            found = 0;
            
            token = strtok(path, ":");
            while (token) {
                full_path = malloc(strlen(token) + strlen(commands[0]) + 2);
                if (full_path) {
                    strcpy(full_path, token);
                    strcat(full_path, "/");
                    strcat(full_path, commands[0]);

                    if (access(full_path, X_OK) == 0) {
                        found = 1;
                        pid = fork();
                        if (pid == 0) {
                            /* Child process */
                            exec_status = lsh_execute(commands, full_path);
                            if (exec_status == -1) {
                                fprintf(stderr, "shell: %s: execution error\n", commands[0]);
                            }
                            exit(EXIT_FAILURE);
                        } else if (pid < 0) {
                            /* Error forking */
                            perror("shell");
                        } else {
                            /* Parent process */
                            waitpid(pid, &exec_status, 0);
                        }
                        break;
                    }
                    
                    free(full_path);
                }
                token = strtok(NULL, ":");
            }
            
            if (!found) {
                fprintf(stderr, "shell: %s: command not found\n", commands[0]);
            }

            for (i = 0; commands[i] != NULL; i++) {
                free(commands[i]); /* Free each command */
            }
            free(commands);
        }
        free(line);
    }

    return 0;
}

int lsh_execute(char **commands, char *full_path) {
    if (execvp(full_path, commands) == -1) {
        perror("shell");
        return -1;
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

    token = strtok(line, " \t\r\n\a"); /* Simplified delimiter */
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

        token = strtok(NULL, " \t\r\n\a"); /* Simplified delimiter */
    }
    tokens[position] = NULL;
    return tokens;
}

