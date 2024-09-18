# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = MYLS

# Source files
SRCS = MYLS.c list_all.c list_long.c list_time.c list_creation.c \
       list_access.c list_inode.c list_directory.c list_unsorted.c \
       list_single_column.c color.c sorting.c

# Default target
all: $(TARGET)

# Link the source files directly to create the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)

# .PHONY ensures that make doesn't confuse the clean target with a file named clean
.PHONY: all clean

