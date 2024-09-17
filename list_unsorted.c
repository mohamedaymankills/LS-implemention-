// list_unsorted.c
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "color.h" // Include the colors header

void list_unsorted(const char *path, int show_all) {
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
        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        if (color_output) {
            // Get file status for color output
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) != -1) {
                print_colored(entry->d_name, &file_stat);
                printf("\n");
            } else {
                printf("%s  ", entry->d_name);
            }
        } else {
            // Print without color
            printf("%s  ", entry->d_name);
        }
    }
    printf("\n");

    // Clean up
    closedir(dir);
}

