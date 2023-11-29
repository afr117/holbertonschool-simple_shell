CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

SOURCES = shell.c parser.c executor.c helper.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = hsh

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(EXECUTABLE)

