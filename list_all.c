/******************************* Name    : list_all.c                  *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <stdio.h>       // Standard I/O functions
#include <string.h>      // String manipulation functions
#include <dirent.h>      // Directory entry functions
#include <sys/stat.h>    // File status functions and macros
#include <stdlib.h>      // Standard library functions
#include <unistd.h>      // POSIX operating system API, including isatty()
#include "color.h"       // Include the colors header for colored output
#include "sorting.h"     // Include the sorting header for sorting entries

// Function to list all files in a directory with optional color output and sorting
void list_all(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal to enable color

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir"); // Print error if directory cannot be opened
        return;
    }

    // Collect directory entries
    char **entries = NULL; // Pointer to hold the list of entries
    int num_entries = 0;   // Number of entries found
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if show_all is not set
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Allocate memory for entries
        entries = realloc(entries, sizeof(char *) * (num_entries + 1)); // Resize the entries array
        if (entries == NULL) {
            perror("realloc"); // Print error if memory allocation fails
            closedir(dir);
            return;
        }

        // Duplicate the entry name and add to the list
        entries[num_entries] = strdup(entry->d_name); // Copy the entry name to the list
        if (entries[num_entries] == NULL) {
            perror("strdup"); // Print error if string duplication fails
            closedir(dir);
            return;
        }
        num_entries++;
    }

    // Sort the entries using case-insensitive comparison
    sort_entries(entries, num_entries); // Sort the entries alphabetically

    // Print the sorted entries
    for (int i = 0; i < num_entries; i++) {
        if (color_output) { // If terminal supports color output
            // Get file stat for color output
            struct stat file_stat;
            if (stat(entries[i], &file_stat) == -1) {
                perror("stat"); // Print error if file status cannot be retrieved
                continue;
            }
            print_colored(entries[i], &file_stat); // Print the file name with color
        } else {
            printf("%s", entries[i]); // Print the file name without color
        }
        printf("\n"); // New line after each file name
        free(entries[i]);  // Free the duplicated string
    }

    // Clean up
    free(entries);    // Free the allocated memory for entries
    closedir(dir);    // Close the directory stream
}

