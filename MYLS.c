#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void list_directory(const char *path, int show_all) {
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
        // If -a flag is not present, skip hidden files (which start with a dot)
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int show_all = 0;  // Flag for the -a option
    const char *path = ".";  // Default path is current directory

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_all = 1;  // Enable showing hidden files
        } else {
            path = argv[i];  // Treat other arguments as the directory path
        }
    }

    // List the directory contents
    list_directory(path, show_all);

    return 0;
}

