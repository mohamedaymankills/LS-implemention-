/******************************* Name    : list_directory.c        *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <stdio.h>        // Standard I/O functions
#include <sys/stat.h>     // File status functions and macros
#include <unistd.h>       // POSIX operating system API, including isatty() and STDOUT_FILENO
#include "color.h"        // Include the colors header for color support

// Function to list the specified directory
void list_directory(const char *path) {
    struct stat path_stat;  // Structure to hold file status information
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal to enable color

    // Get information about the specified path
    if (stat(path, &path_stat) == -1) {
        perror("stat"); // Print error if file status cannot be retrieved
        return;
    }

    // Check if the path is a directory
    if (S_ISDIR(path_stat.st_mode)) {
        // If it's a directory, print its name
        if (color_output) {
            print_colored(path, &path_stat); // Print directory name with color
            printf("\n");
        } else {
            printf("%s\n", path); // Print directory name without color
        }
    } else {
        // If it's not a directory, print an error
        fprintf(stderr, "%s is not a directory\n", path);
    }
}

