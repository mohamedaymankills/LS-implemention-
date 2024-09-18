/******************************* Name    : list_unsorted.c         *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "color.h" // Include the colors header

void list_unsorted(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Open the directory specified by the path
    dir = opendir(path);
    if (dir == NULL) { // Error handling if the directory cannot be opened
        perror("opendir");
        return;
    }

    // Read and print directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        if (color_output) {
            // Get file status for color output
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) != -1) { // Check if stat succeeds
                print_colored(entry->d_name, &file_stat); // Print with color
                printf("\n");
            } else {
                // If stat fails, print the name without color
                printf("%s  ", entry->d_name);
            }
        } else {
            // Print without color if not outputting to a terminal
            printf("%s  ", entry->d_name);
        }
    }
    printf("\n"); // Print a newline after listing all entries

    // Clean up: close the directory
    closedir(dir);
}

