// main.c
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]) {
    int show_all = 0;        // Flag for the -a option
    int long_format = 0;     // Flag for the -l option
    int sort_by_time = 0;    // Flag for the -t option
    int sort_by_creation = 0; // Flag for the -c option
    int sort_by_access = 0;  // Flag for the -u option
    int show_inode = 0;      // Flag for the -i option
    int list_dir_name = 0;   // Flag for the -d option
    int no_sort = 0;         // Flag for the -f option
    int single_column = 0;   // Flag for the -1 option
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
        } else if (strcmp(argv[i], "-u") == 0) {
            sort_by_access = 1;  // Enable sorting by access time
        } else if (strcmp(argv[i], "-i") == 0) {
            show_inode = 1;  // Enable displaying inode numbers
        } else if (strcmp(argv[i], "-d") == 0) {
            list_dir_name = 1;  // Enable listing directory names only
        } else if (strcmp(argv[i], "-f") == 0) {
            no_sort = 1;  // Enable no sorting and showing all files
        } else if (strcmp(argv[i], "-1") == 0) {
            single_column = 1;  // Enable single column listing
        } else {
            path = argv[i];  // Treat other arguments as the directory path
        }
    }

    // Execute the corresponding option
    if (single_column) {
        list_single_column(path, show_all);
    } else if (no_sort) {
        list_unsorted(path);
    } else if (list_dir_name) {
        list_directory(path);
    } else if (long_format) {
        list_long(path, show_all);
    } else if (sort_by_creation) {
        list_creation(path, show_all);
    } else if (sort_by_access) {
        list_access(path, show_all);
    } else if (sort_by_time) {
        list_time(path, show_all);
    } else if (show_inode) {
        list_inode(path, show_all);
    } else {
        list_all(path, show_all);
    }

    return 0;
}

