// list_all.c
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void list_all(const char *path, int show_hidden) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip files that start with a dot unless show_hidden is true
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

