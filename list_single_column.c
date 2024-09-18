/******************************* Name    : list_single_column.c    *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "color.h" // Include the colors header

void list_single_column(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Read and print directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if show_all is not set
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Print each file and directory name
        if (color_output) {
            // Print with color
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) != -1) {
                print_colored(entry->d_name, &file_stat);
                printf("\n");
            } else {
                printf("%s\n", entry->d_name);
            }
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    // Clean up
    closedir(dir);
}

