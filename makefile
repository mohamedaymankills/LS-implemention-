# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = MYLS

# Source files
SRCS = MYLS.c list_all.c list_long.c list_time.c list_creation.c \
       list_access.c list_inode.c list_directory.c list_unsorted.c \
       list_single_column.c color.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# .PHONY ensures that make doesn't confuse the clean target with a file named clean
.PHONY: all clean

