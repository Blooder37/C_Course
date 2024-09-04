# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Linker flags for ncurses
LDFLAGS = -lncurses -DNCURSES_STATIC

# Source files
SRCS = main.c queue.c snakeFunctions.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = snake_game

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# Clean up
clean:
	del $(OBJS) $(EXEC)
