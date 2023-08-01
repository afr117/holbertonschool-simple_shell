#include <stdio.h>
#include <string.h>
#include "shell.h"

/* Placeholder implementation for checking if the command is a built-in */
int is_builtin(char *command)
{
    // Check if the given command is a built-in shell command
    if (strcmp(command, "cd") == 0 || strcmp(command, "exit") == 0)
    {
        return (1); // Return 1 if the command is built-in
    }
    return (0); // Return 0 if the command is not built-in
}

/* Placeholder implementation for handling built-in commands */
void handle_builtin(char **args)
{
    // Handle the execution of built-in shell commands
    // Add more built-in commands if needed

    if (strcmp(args[0], "cd") == 0)
    {
        /* Implement 'cd' command */
        /* Use 'args[1]' to access the directory to change to */
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        /* Implement 'exit' command */
        /* Use 'args[1]' to access the exit status if provided */
    }
}

/* Placeholder implementation for executing external commands */
int execute_external(char **args)
{
    // Marking the parameter as unused to avoid the warning
    (void)args;

    /* Implement code to execute external commands using fork and execve */
    /* Return the exit status of the executed command */
    return (0); // Placeholder return value
}

/* Function to execute commands received from the user */
int execute_commands(char **commands)
{
    // Marking the parameter as unused to avoid the warning
    (void)commands;

    /* Implement code to execute multiple commands using pipes and fork */
    /* Return the exit status of the last executed command */
    return (0); // Placeholder return value
}

