// list_all.c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>  // For isatty()
#include "color.h"  // Include the colors header

void list_all(const char *path, int show_all) {
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

        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (color_output) {
            print_colored(entry->d_name, &file_stat);
        } else {
            printf("%s", entry->d_name);
        }
        printf("\n");
    }

    // Clean up
    closedir(dir);
}

