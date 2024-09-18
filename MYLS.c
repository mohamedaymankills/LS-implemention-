/******************************* Name    : MYLS.c                  *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/  

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "list.h" // Include header for listing functions

// Function to print usage information
void print_usage() {
    printf("Usage: myls [options] [path]\n");
    printf("Options:\n");
    printf("  -a       Include hidden files\n");
    printf("  -d       List directories themselves, not their contents\n");
    printf("  -i       Print the index number of each file\n");
    printf("  -l       Use a long listing format\n");
    printf("  -1       List one file per line\n");
    printf("  -t       Sort by modification time\n");
    printf("  -u       Sort by last access time\n");
    printf("  -c       Sort by creation time (if supported)\n");
    printf("  -f       Do not sort, list entries as they appear\n");
    printf("  -h       Show this help message\n");
}

// Main function
int main(int argc, char *argv[]) {
    int opt;
    int show_all = 0;           // -a: Flag to include hidden files
    int list_directory_only = 0;// -d: Flag to list directories only
    int show_inode = 0;         // -i: Flag to print inode numbers
    int long_listing = 0;       // -l: Flag for long listing format
    int single_column = 0;      // -1: Flag to list files in a single column
    int sort_by_time = 0;       // -t: Flag to sort by modification time
    int sort_by_access = 0;     // -u: Flag to sort by last access time
    int sort_by_creation = 0;   // -c: Flag to sort by creation time
    int unsorted = 0;           // -f: Flag to list entries as they appear
    char *path = ".";           // Default path is the current directory

    // Parse command line options
    while ((opt = getopt(argc, argv, "adil1tucfh")) != -1) {
        switch (opt) {
            case 'a':
                show_all = 1; // Include hidden files
                break;
            case 'd':
                list_directory_only = 1; // List directories themselves
                break;
            case 'i':
                show_inode = 1; // Print inode numbers
                break;
            case 'l':
                long_listing = 1; // Long listing format
                break;
            case '1':
                single_column = 1; // Single column format
                break;
            case 't':
                sort_by_time = 1; // Sort by modification time
                break;
            case 'u':
                sort_by_access = 1; // Sort by last access time
                break;
            case 'c':
                sort_by_creation = 1; // Sort by creation time
                break;
            case 'f':
                unsorted = 1; // Do not sort
                break;
            case 'h':
                print_usage(); // Print help message
                exit(EXIT_SUCCESS);
            default:
                print_usage(); // Print help message for invalid options
                exit(EXIT_FAILURE);
        }
    }

    // Get the path argument if provided
    if (optind < argc) {
        path = argv[optind];
    }

    // Execute the appropriate listing function based on options
    if (list_directory_only) {
        list_directory(path); // List directories
    } else if (show_inode) {
        list_inode(path, show_all); // List files with inode numbers
    } else if (long_listing) {
        list_long(path, show_all); // Long listing format
    } else if (single_column) {
        list_single_column(path, show_all); // Single column format
    } else if (sort_by_time) {
        list_time(path, show_all); // Sort by modification time
    } else if (sort_by_access) {
        list_access(path, show_all); // Sort by last access time
    } else if (sort_by_creation) {
        list_creation(path, show_all); // Sort by creation time
    } else if (unsorted) {
        list_unsorted(path); // List entries as they appear
    } else {
        // Default: list all files in default format
        list_all(path, show_all);
    }

    return 0;
}

