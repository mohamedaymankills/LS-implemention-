// list_single_column.c
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void list_single_column(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;

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
        // Print each file and directory name in a single column
        printf("%s\n", entry->d_name);
    }

    // Clean up
    closedir(dir);
}

