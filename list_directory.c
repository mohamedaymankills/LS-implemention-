// list_directory.c
#include <stdio.h>
#include <sys/stat.h>

void list_directory(const char *path) {
    struct stat path_stat;

    // Get information about the specified path
    if (stat(path, &path_stat) == -1) {
        perror("stat");
        return;
    }

    // Check if the path is a directory
    if (S_ISDIR(path_stat.st_mode)) {
        // If it's a directory, print its name
        printf("%s\n", path);
    } else {
        // If it's not a directory, print an error
        fprintf(stderr, "%s is not a directory\n", path);
    }
}

