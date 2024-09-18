// list_all.c
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>  // For isatty()
#include "color.h"   // Include the colors header
#include "sorting.h" // Include the sorting header

void list_all(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Collect directory entries
    char **entries = NULL;
    int num_entries = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if show_all is not set
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Allocate memory for entries
        entries = realloc(entries, sizeof(char *) * (num_entries + 1));
        if (entries == NULL) {
            perror("realloc");
            closedir(dir);
            return;
        }

        // Duplicate the entry name and add to the list
        entries[num_entries] = strdup(entry->d_name);
        if (entries[num_entries] == NULL) {
            perror("strdup");
            closedir(dir);
            return;
        }
        num_entries++;
    }

    // Sort the entries using case-insensitive comparison
    sort_entries(entries, num_entries);

    // Print the sorted entries
    for (int i = 0; i < num_entries; i++) {
        if (color_output) {
            // Get file stat for color output
            struct stat file_stat;
            if (stat(entries[i], &file_stat) == -1) {
                perror("stat");
                continue;
            }
            print_colored(entries[i], &file_stat);
        } else {
            printf("%s", entries[i]);
        }
        printf("\n");
        free(entries[i]);  // Free the duplicated string
    }

    // Clean up
    free(entries);
    closedir(dir);
}

