/******************************* Name    : list_time.c             *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "color.h" // Include the colors header

// Structure to hold file information, including name and modification time
struct file_info {
    char *name;     // File name
    time_t mod_time; // File modification time
};

// Function to compare files by modification time for qsort
// Sorts in descending order (most recently modified files first)
int compare_mod_time(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    return (file_b->mod_time - file_a->mod_time); // Return difference in modification times
}

void list_time(const char *path, int show_hidden) {
    DIR *dir;
    struct dirent *entry;
    struct file_info *files = NULL; // Array to hold file information
    int file_count = 0; // Number of files found
    int capacity = 10; // Initial capacity for the files array
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Allocate initial memory for storing file information
    files = malloc(capacity * sizeof(struct file_info));
    if (files == NULL) { // Error handling for memory allocation
        perror("malloc");
        return;
    }

    // Open the directory specified by the path
    dir = opendir(path);
    if (dir == NULL) { // Error handling if the directory cannot be opened
        perror("opendir");
        free(files);
        return;
    }

    // Read and store directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".." (current and parent directory references)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_hidden is true
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        // Get file modification time using stat
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) { // Error handling for stat
            perror("stat");
            continue;
        }

        // Store file information (name and modification time)
        if (file_count >= capacity) { // If current capacity is exceeded, double the capacity
            capacity *= 2;
            files = realloc(files, capacity * sizeof(struct file_info));
            if (files == NULL) { // Error handling for memory reallocation
                perror("realloc");
                closedir(dir);
                return;
            }
        }
        files[file_count].name = strdup(entry->d_name); // Duplicate the file name
        if (files[file_count].name == NULL) { // Error handling for strdup
            perror("strdup");
            continue;
        }
        files[file_count].mod_time = file_stat.st_mtime; // Store modification time
        file_count++;
    }

    // Sort files by modification time using qsort
    qsort(files, file_count, sizeof(struct file_info), compare_mod_time);

    // Print files, using color if the output is a terminal
    for (int i = 0; i < file_count; i++) {
        if (color_output) {
            // Print with color
            struct stat file_stat;
            if (stat(files[i].name, &file_stat) != -1) { // Re-check file status for color coding
                print_colored(files[i].name, &file_stat);
                printf("\n");
            } else {
                printf("%s\n", files[i].name); // Print without color if stat fails
            }
        } else {
            printf("%s\n", files[i].name); // Print without color
        }
        free(files[i].name); // Free the duplicated string
    }

    // Clean up: free allocated memory and close directory
    free(files);
    closedir(dir);
}

