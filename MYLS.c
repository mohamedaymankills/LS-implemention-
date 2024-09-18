/******************************* Name    : MYLS.c                  *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/  
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "list.h"



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

int main(int argc, char *argv[]) {
    int opt;
    int show_all = 0;           // -a
    int list_directory_only = 0;// -d
    int show_inode = 0;         // -i
    int long_listing = 0;       // -l
    int single_column = 0;      // -1
    int sort_by_time = 0;       // -t
    int sort_by_access = 0;     // -u
    int sort_by_creation = 0;   // -c
    int unsorted = 0;           // -f
    char *path = ".";           // Default path is current directory

    // Parse options
    while ((opt = getopt(argc, argv, "adil1tucfh")) != -1) {
        switch (opt) {
            case 'a':
                show_all = 1;
                break;
            case 'd':
                list_directory_only = 1;
                break;
            case 'i':
                show_inode = 1;
                break;
            case 'l':
                long_listing = 1;
                break;
            case '1':
                single_column = 1;
                break;
            case 't':
                sort_by_time = 1;
                break;
            case 'u':
                sort_by_access = 1;
                break;
            case 'c':
                sort_by_creation = 1;
                break;
            case 'f':
                unsorted = 1;
                break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    // Get the path argument if provided
    if (optind < argc) {
        path = argv[optind];
    }

    // Execute the appropriate listing function based on options
    if (list_directory_only) {
        list_directory(path);
    } else if (show_inode) {
        list_inode(path, show_all);
    } else if (long_listing) {
        list_long(path, show_all);
    } else if (single_column) {
        list_single_column(path, show_all);
    } else if (sort_by_time) {
        list_time(path, show_all);
    } else if (sort_by_access) {
        list_access(path, show_all);
    } else if (sort_by_creation) {
        list_creation(path, show_all);
    } else if (unsorted) {
        list_unsorted(path);
    } else {
        // Default: list all files
        list_all(path, show_all);
    }

    return 0;
}

