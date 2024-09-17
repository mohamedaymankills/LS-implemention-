// list_unsorted.c
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void list_unsorted(const char *path) {
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
        // Print each file and directory name
        printf("%s  ", entry->d_name);
    }
    printf("\n");

    // Clean up
    closedir(dir);
}

