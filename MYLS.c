// main.c
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]) {
    int show_all = 0;      // Flag for the -a option
    int long_format = 0;   // Flag for the -l option
    int sort_by_time = 0;  // Flag for the -t option
    int sort_by_creation = 0; // Flag for the -c option
    const char *path = ".";  // Default path is the current directory

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_all = 1;  // Enable showing hidden files
        } else if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;  // Enable long listing format
        } else if (strcmp(argv[i], "-t") == 0) {
            sort_by_time = 1;  // Enable sorting by modification time
        } else if (strcmp(argv[i], "-c") == 0) {
            sort_by_creation = 1;  // Enable sorting by creation time
        } else {
            path = argv[i];  // Treat other arguments as the directory path
        }
    }

    // Execute the corresponding option
    if (long_format) {
        list_long(path, show_all);
    } else if (sort_by_creation) {
        list_creation(path, show_all);
    } else if (sort_by_time) {
        list_time(path, show_all);
    } else {
        list_all(path, show_all);
    }

    return 0;
}

