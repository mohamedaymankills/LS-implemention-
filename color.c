/******************************* Name    : color.c                 *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <stdio.h>     // Standard I/O functions
#include <stdlib.h>    // Standard library functions
#include <sys/stat.h>  // File status functions and macros

// Define color codes for different file types
#define DEFAULT_COLOR "\033[0m"       // Default color (reset to terminal's default)
#define DIR_COLOR "\033[1;34m"        // Color for directories (bold blue)
#define EXEC_COLOR "\033[1;32m"       // Color for executable files (bold green)
#define LINK_COLOR "\033[1;36m"       // Color for symbolic links (bold cyan)
#define SPECIAL_COLOR "\033[1;33m"    // Color for special files (bold yellow)

// Function to get the color based on the file type
const char *get_color(const struct stat *file_stat) {
    if (S_ISDIR(file_stat->st_mode)) {           // Check if the file is a directory
        return DIR_COLOR;                        // Return the color for directories
    } else if (S_ISLNK(file_stat->st_mode)) {    // Check if the file is a symbolic link
        return LINK_COLOR;                       // Return the color for symbolic links
    } else if (file_stat->st_mode & S_IXUSR) {   // Check if the file is executable by the user
        return EXEC_COLOR;                       // Return the color for executables
    } else if (S_ISCHR(file_stat->st_mode) || S_ISBLK(file_stat->st_mode)) {  // Check if the file is a character or block device
        return SPECIAL_COLOR;                    // Return the color for special files
    }
    return DEFAULT_COLOR;                        // Default color for other file types
}

// Function to print the file name with color
void print_colored(const char *name, const struct stat *file_stat) {
    const char *color = get_color(file_stat);    // Get the appropriate color for the file
    printf("%s%s%s", color, name, DEFAULT_COLOR); // Print the file name with the color and reset to default color
}

