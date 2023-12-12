iPartner Project Simple Shell
By Alfred Rosado and Britt Herman

Introduction
This is an implementation of a Linux shell written in C language.

Project details
Welcome to the Mandalorian Simple Shell project!! This program is a simple shell that can be compiled and launched from the command line.

How to Compile
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

Syntax
When using this shell, the syntax for running any command follows the familiar syntax when running a command in any other shell.

Builtin Commands
This shell supports a variety of commands:

alias - create or list an alias

cd - change directory

env - list the current environment variables

exit - exit the shell

history - display the command history for the current shell session

setenv - sets an environment variable

unsetenv - unsets an environment variable

Run the shell
Clone this directory and cd into it.
Run the command cc  shell.c -o shell.
Run ./shell.
Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
In order to exit, run exit.# Simple Shell - Custom UNIX Command-Line Interpreter

## Description

Simple Shell is a custom UNIX command-line interpreter that provides basic functionalities for executing commands, handling built-in commands, and supporting interactive and non-interactive modes.

## Supported Commands

The Simple Shell supports the following built-in commands:

- `exit`: Exit the shell.
- `cd`: Change the current working directory.

For external commands, the shell can execute any valid UNIX command available in your system.
 
A simple shell program, starting from version 0.1 and progressing through subsequent versions (0.2, 0.3, and so on).
Why is this important?

Creating a shell is a fundamental exercise in operating systems and systems programming. It helps you understand how shells work, how they interpret commands, and how they interact with the operating system. It also involves handling various aspects of process creation, execution, and error handling.
What can we use it for?

A simple shell can be used for basic command-line interactions. Users can execute simple commands, and the shell will provide a prompt for further input. It's a simplified version of the shells used in Unix-like operating systems. While your shell may not have all the features of a fully-fledged shell (such as bash), it serves as a foundation for understanding the underlying concepts and mechanisms involved in command-line interpretation and execution.
In summary, the project helps you gain practical experience in systems programming, understand how shells function, and provides a platform for learning about process execution and management in a Unix-like environment.

------------------------------------------------------------------------------------

This `makefile` is a set of instructions for the `make` utility, telling it how to build your program. Here's a brief breakdown:

1. **Variables:**
   - `CC = gcc`: Sets the compiler to be used (gcc).
   - `CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89`: Flags for the compiler, enabling various warning messages and setting the C standard.

2. **File Lists:**
   - `SOURCES = shell.c parser.c executor.c helper.c`: List of source code files.
   - `OBJECTS = $(SOURCES:.c=.o)`: List of object files to be created from source files.

3. **Main Target (`all`):**
   - `all: $(EXECUTABLE)`: This is the default target. It depends on `$(EXECUTABLE)`, so when you run `make all`, it will ensure that the executable is built.

4. **Build Rule (`$(EXECUTABLE)`):**
   - `$(EXECUTABLE): $(OBJECTS)`: The executable depends on the object files. If any of the object files change, it will trigger a rebuild.
   - `$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)`: The actual command to link the object files and create the executable.

5. **Object File Rule (`%.o: %.c`):**
   - `%.o: %.c`: This is a pattern rule. It says that for any `.c` file, there's a corresponding `.o` file. The command below is used to compile each `.c` file into a `.o` file.
   - `$(CC) $(CFLAGS) -c $<`: The compiler is instructed to compile a source file into an object file.

6. **Cleaning Rules (`clean` and `fclean`):**
   - `clean`: Removes the object files (`$(OBJECTS)`).
   - `fclean: clean`: Additionally removes the executable (`$(EXECUTABLE)`).

So, when you run `make`, it will build the executable `hsh` using the specified compiler and flags. The `clean` and `fclean` targets help you clean up by removing either just the object files or both the object files and the executable.

--------------------------------------------------------------------------------------------

executor.c:
This code, residing in `executor.c`, is part of a shell program and focuses on the execution of commands. Here's a brief explanation:

1. **`is_builtin` Function:**
   - Purpose: Checks if a given command is a built-in shell command.
   - Parameters: `char *command` - the command to check.
   - Returns: `1` if the command is built-in (`cd` or `exit`), otherwise `0`.
   - Note: It uses `strcmp` to compare the command with known built-in commands.

2. **`handle_builtin` Function:**
   - Purpose: Executes the built-in shell command.
   - Parameters: `char **args` - arguments for the built-in command.
   - Returns: Nothing.
   - Note: It checks the command (`args[0]`) and performs corresponding built-in actions. For example, handling the `cd` command involves changing the directory using `args[1]`.

3. **`execute_external` Function:**
   - Purpose: Executes an external command using fork and execve.
   - Parameters: `char **args` - arguments for the external command.
   - Returns: The exit status of the executed command (currently a placeholder value of `0`).
   - Note: The function is currently a placeholder, marked parameters as unused, and needs implementation to handle the actual execution of external commands using fork and execve.

4. **`execute_commands` Function:**
   - Purpose: Executes multiple commands using pipes and fork.
   - Parameters: `char **commands` - an array of commands to execute.
   - Returns: The exit status of the last executed command (currently a placeholder value of `0`).
   - Note: Similar to `execute_external`, this function is a placeholder and requires implementation for executing multiple commands using pipes and fork.

In summary, this code provides the foundation for handling built-in commands (`cd` and `exit`) and placeholders for executing external commands and multiple commands using pipes and fork. The actual implementation for executing external commands and handling pipes is expected to be added in the future.

--------------------------------------------------------------------------------------------

helper.c: 
Certainly! This code, residing in `helper.c`, provides some helper functions for handling input in a shell program. Here's a brief explanation:

1. **`read_line` Function:**
   - **Purpose:** Reads a line of input from the user in interactive mode.
   - **Return:** The read input line or `NULL` on failure.
   - **Note:** The actual implementation to read a line from the user in interactive mode is not provided. Currently, it returns `NULL`, indicating the need for implementation.

2. **`read_line_from_file` Function:**
   - **Purpose:** Reads a line from a file.
   - **Parameters:** `FILE *stream` - The file stream to read from.
   - **Return:** The read input line from the file or `NULL` on failure.
   - **Note:** The function has a parameter `stream` representing the file stream, but the actual implementation to read a line from the file is not provided. It returns `NULL` as a placeholder.

3. **`_strdup` Function:**
   - **Purpose:** Duplicates a string.
   - **Parameters:** `char *str` - The string to duplicate.
   - **Return:** The duplicated string or `NULL` on failure.
   - **Note:** The function takes a string (`str`) and is intended to duplicate it. However, the implementation is not provided, and it currently returns `NULL`. The parameter `str` is marked as unused.

In summary, this code establishes the structure for functions related to reading input lines, both from the user interactively and from a file. Additionally, it includes a placeholder for a function to duplicate strings. The actual implementations for these functions need to be added to complete their functionality.

----------------------------------------------------------------------------------------------

man_1_simple_shell;
This is a manual page (man page) for a custom UNIX command-line interpreter called `simple_shell`. It provides information on how to use the shell, its features, limitations, and details for reporting bugs. Here's a brief overview:

1. **Header Section (`.TH`):**
   - Defines the title, section number, date, and version of the man page.

2. **Name Section (`.SH NAME`):**
   - States the name and purpose of the command-line interpreter (`simple_shell`).

3. **Synopsis Section (`.SH SYNOPSIS`):**
   - Shows a brief usage example of the command (`simple_shell`).

4. **Description Section (`.SH DESCRIPTION`):**
   - Provides an overview of what `simple_shell` is, including its basic functionalities.

5. **Usage Section (`.SH USAGE`):**
   - Describes how to use the shell in interactive mode and provides examples of commands.

6. **Commands Section (`.SH COMMANDS`):**
   - Lists and briefly describes the supported commands (`exit` and `cd`).

7. **Interactive Mode Section (`.SH INTERACTIVE MODE`):**
   - Explains how to run `simple_shell` in interactive mode, providing examples.

8. **Non-Interactive Mode Section (`.SH NON-INTERACTIVE MODE`):**
   - Explains how to run `simple_shell` in non-interactive mode, with examples using input redirection and pipes.

9. **Supported Features Section (`.SH SUPPORTED FEATURES`):**
   - Lists the features supported by `simple_shell`, such as execution of external commands, handling command separation, input/output redirection, pipelines, background execution, and error messages.

10. **Limitations Section (`.SH LIMITATIONS`):**
    - Describes the limitations of the shell, including the lack of support for environment variables, handling quotes or escape characters, and potential issues with parsing complex commands.

11. **Authors Section (`.SH AUTHORS`):**
    - Credits the authors of the `simple_shell` program.

12. **Reporting Bugs Section (`.SH REPORTING BUGS`):**
    - Instructs users on how to report bugs and provides a placeholder email address.

13. **Copyright Section (`.SH COPYRIGHT`):**
    - States the copyright information, license terms, and disclaimers for the software.

In summary, this manual page serves as comprehensive documentation for the `simple_shell` command-line interpreter, covering its usage, features, limitations, and bug reporting information.

------------------------------------------------------------------------------------------------

parser.c
This code, located in `parser.c`, defines a function named `split_commands` that splits an input string into separate commands using space and tab as delimiters. Here's a brief explanation:

1. **Macro Definition:**
   - `#define TOKEN_BUFSIZE 64`: Sets the buffer size for tokens.
   - `#define COMMAND_BUFSIZE 64`: Sets the buffer size for commands.
   - `#define TOKEN_DELIMITERS " \t\r\n\a"`: Defines delimiters for tokenizing the input string.

2. **Function `split_commands`:**
   - **Parameters:** `char *input` - The input string to be split into commands.
   - **Return:** An array of strings containing separate commands. The last element of the array is set to `NULL`. Returns `NULL` on failure.
   - **Explanation:**
     - Declares and initializes variables, including the buffer size and a pointer to the commands array.
     - Allocates memory for the commands array using `malloc`.
     - Uses `strtok` to tokenize the input string based on the defined delimiters.
     - Dynamically reallocates memory if the number of commands exceeds the current buffer size.
     - Stores each token (command) in the commands array.
     - Sets the last element of the array to `NULL` to indicate the end of commands.
     - Returns the array of commands.

3. **Error Handling:**
   - Checks for memory allocation errors using `malloc` and `realloc`.
   - Prints an error message and exits with `EXIT_FAILURE` in case of allocation failure.

In summary, this code provides a function that takes an input string, splits it into separate commands using specified delimiters, and returns an array of strings containing these commands. The function handles dynamic memory allocation and reallocation to accommodate various input sizes.

--------------------------------------------------------------------------------------------


shell.c;
This code represents a simple shell program in C. Here's a brief explanation:

1. **Header Files:**
   - Includes necessary header files (`stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `sys/types.h`, `sys/wait.h`) for standard input/output, dynamic memory, string manipulation, and process-related functions.

2. **Macro Definition:**
   - `#define LSH_TOK_BUFSIZE 64`: Sets the buffer size for tokens.

3. **Function Prototypes:**
   - `lsh_read_line`: Reads a line of input from the user.
   - `lsh_split_line`: Splits a line into tokens.
   - `lsh_execute`: Executes the commands.

4. **Main Function (`main`):**
   - Enters a loop (`while (status)`) for the shell to continuously prompt the user.
   - Prompts the user with `($)`.
   - Calls `lsh_read_line` to read a line of input from the user.
   - Calls `lsh_split_line` to split the input line into commands.
   - Forks a new process to execute the commands using `execvp`.
   - Waits for the child process to complete using `waitpid`.
   - Frees allocated memory after execution.

5. **`lsh_read_line` Function:**
   - Reads a line of input from the user using `getline`.
   - Returns the input line.

6. **`lsh_split_line` Function:**
   - Splits a line into tokens using `strtok`.
   - Tokens are separated by spaces (simplified delimiter).
   - Dynamically allocates memory for tokens and reallocates as needed.
   - Returns an array of tokens.

7. **Error Handling:**
   - Checks for memory allocation errors using `malloc` and `realloc`.
   - Prints an error message and exits with `EXIT_FAILURE` in case of allocation failure.

8. **Comments:**
   - Contains comments for clarification and readability.

In summary, this code defines a simple shell that continuously prompts the user for commands. It reads user input, splits it into commands, and executes them in a child process while the parent waits for completion. The shell supports basic functionality and uses dynamic memory allocation for tokens.

------------------------------------------------------------------------------------------

shell.h;
This code defines a header file named `shell.h` for a shell program. Here's a brief explanation:

1. **Header Guards:**
   - `#ifndef SHELL_H` and `#define SHELL_H`: These lines are used for include guards to prevent the header file from being included more than once in the same translation unit.

2. **Included Header Files:**
   - Includes necessary header files (`stdio.h`, `stdlib.h`, `unistd.h`, `sys/wait.h`) for standard input/output, dynamic memory, and process-related functions.

3. **Macro Definitions:**
   - `TOKEN_DELIMITERS " \t\r\n\a"`: Defines delimiters for tokenizing input strings.
   - `PROGRAM_NAME "hsh"`: Defines the program name as "hsh." This can be replaced with the actual name of the shell.

4. **Function Prototypes:**
   - `char *read_line(void)`: Prototype for a function to read a line of input.
   - `char **tokenize_input(char *input)`: Prototype for a function to tokenize input.
   - `char **split_commands(char *input)`: Prototype for a function to split commands.
   - `int execute_commands(char **commands)`: Prototype for a function to execute commands.
   - `int is_builtin(char *command)`: Prototype for a function to check if a command is a built-in.
   - `void handle_builtin(char **args)`: Prototype for a function to handle built-in commands.
   - `int execute_external(char **args)`: Prototype for a function to execute external commands.

5. **Function Prototypes for External Use:**
   - These function prototypes allow other parts of the program to use these functions without having to define their implementation details at this point.

6. **Header File Closing:**
   - `#endif /* SHELL_H */`: Closes the header file with the end of the include guard.

In summary, this header file defines macros, includes necessary headers, and provides function prototypes for various functionalities of a shell program. It's meant to be included in other source files of the shell program to provide consistency and easy access to shared functionality.

## Authors

- Alfred Rosado <6666@holbertonschool.com>
  Britt Herman <6640@holbertsonschool.com


