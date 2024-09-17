// list_directory.c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h> // Include unistd.h for isatty and STDOUT_FILENO
#include "color.h" // Include the colors header for color support

void list_directory(const char *path) {
    struct stat path_stat;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Get information about the specified path
    if (stat(path, &path_stat) == -1) {
        perror("stat");
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

