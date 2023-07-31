#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define TOKEN_BUFSIZE 64
#define COMMAND_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char **split_commands(char *input)
{
    int i = 0; /* Move variable declaration to the beginning */
    int buffer_size = COMMAND_BUFSIZE;
    char **commands = malloc(buffer_size * sizeof(char *));
    char *command;

    if (!commands)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    command = strtok(input, TOKEN_DELIMITERS);

    while (command)
    {
        commands[i] = command;
        i++;

        if (i >= buffer_size)
        {
            buffer_size += COMMAND_BUFSIZE;
            commands = realloc(commands, buffer_size * sizeof(char *));
            if (!commands)
            {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        command = strtok(NULL, TOKEN_DELIMITERS);
    }

    commands[i] = NULL;
    return commands;
}

