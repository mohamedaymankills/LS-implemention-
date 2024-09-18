/******************************* Name    : list_access.c           *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <dirent.h>      // Directory entry functions
#include <stdio.h>       // Standard I/O functions
#include <stdlib.h>      // Standard library functions
#include <string.h>      // String manipulation functions
#include <sys/stat.h>    // File status functions and macros
#include <sys/types.h>   // Data types used in system calls
#include <unistd.h>      // POSIX operating system API
#include <utime.h>       // File access and modification times
#include "color.h"       // Include the colors header for colored output

// Structure to hold file information
struct file_info {
    char *name;         // File name
    time_t access_time; // Last access time
};

// Function to compare files by access time for qsort
int compare_access_time(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    return (file_b->access_time - file_a->access_time); // Descending order by access time
}

// Function to list files sorted by access time
void list_access(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    struct file_info *files = NULL;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal
    int file_count = 0;   // Number of files
    int capacity = 10;    // Initial capacity for storing file information

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

        // Get file access time
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat"); // Print error if file status cannot be retrieved
            continue;
        }

        // Store file information
        if (file_count >= capacity) {
            capacity *= 2; // Double the capacity if the current capacity is exceeded
            files = realloc(files, capacity * sizeof(struct file_info));
        }
        files[file_count].name = strdup(entry->d_name); // Duplicate the file name
        files[file_count].access_time = file_stat.st_atime; // Store the access time
        file_count++;
    }

    // Sort files by access time
    qsort(files, file_count, sizeof(struct file_info), compare_access_time);

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
        free(files[i].name); // Free the duplicated file name
    }

    // Clean up
    free(files);     // Free the allocated memory for file information
    closedir(dir);   // Close the directory stream
}

