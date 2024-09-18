/******************************* Name    : list_creation.c         *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <dirent.h>       // Directory entry functions
#include <stdio.h>        // Standard I/O functions
#include <stdlib.h>       // Standard library functions
#include <string.h>       // String manipulation functions
#include <sys/stat.h>     // File status functions and macros
#include <sys/types.h>    // Data types used in system calls
#include <unistd.h>       // POSIX operating system API, including isatty()
#include <utime.h>        // File access and modification times
#include "color.h"        // Include the colors header for colored output

// Structure to hold file information
struct file_info {
    char *name;            // Name of the file
    time_t creation_time;  // Creation time of the file
};

// Function to compare files by creation time for qsort
int compare_creation_time(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    return (file_b->creation_time - file_a->creation_time); // Descending order
}

// Function to list files in a directory by creation time
void list_creation(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    struct file_info *files = NULL;  // Pointer to hold the list of file information
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal to enable color
    int file_count = 0;   // Number of files found
    int capacity = 10;    // Initial capacity for file storage

    // Allocate initial memory for storing file information
    files = malloc(capacity * sizeof(struct file_info));

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir"); // Print error if directory cannot be opened
        return;
    }

    // Read and store directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Get file creation time
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat"); // Print error if file status cannot be retrieved
            continue;
        }

        // On Linux, creation time is not directly available; using modification time as a placeholder
        time_t creation_time = file_stat.st_mtime; // Use st_ctime if supported on your system

        // Store file information
        if (file_count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(struct file_info)); // Resize the files array
        }
        files[file_count].name = strdup(entry->d_name); // Copy the file name to the list
        files[file_count].creation_time = creation_time; // Store the creation time
        file_count++;
    }

    // Sort files by creation time
    qsort(files, file_count, sizeof(struct file_info), compare_creation_time); // Sort the files array

    // Print files
    for (int i = 0; i < file_count; i++) {
        if (color_output) { // If terminal supports color output
            struct stat file_stat;
            if (stat(files[i].name, &file_stat) == -1) {
                perror("stat"); // Print error if file status cannot be retrieved
                continue;
            }
            print_colored(files[i].name, &file_stat); // Print the file name with color
        } else {
            printf("%s", files[i].name); // Print the file name without color
        }
        printf("\n"); // New line after each file name
        free(files[i].name); // Free the duplicated string
    }

    // Clean up
    free(files);    // Free the allocated memory for file information
    closedir(dir);  // Close the directory stream
}

