/* shell.c */

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - Entry point of the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **commands;
	int status = 1; /* Shell status (1: active, 0: exit) */

	while (status)
	{
		printf("($) ");
		line = read_line(); /* Read input line */
		if (!line)
			break;

		commands = split_commands(line); /* Split input into commands */

		if (commands)
		{
			status = execute_commands(commands); /* Execute commands */
			free(commands);
		}
		free(line);
	}

	return (0);
}

