// list_inode.c
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "color.h" // Include the colors header

void list_inode(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Read and print directory entries with their inode numbers
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        if (color_output) {
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) == -1) {
                perror("stat");
                continue;
            }
            print_colored(entry->d_name, &file_stat);
            printf("\n");
        } else {
            printf("%lu %s\n", entry->d_ino, entry->d_name); // Print inode number and file name without color
        }
    }

    // Close the directory
    closedir(dir);
}

