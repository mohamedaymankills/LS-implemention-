// list_inode.c
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#define INITIAL_CAPACITY 10

typedef struct {
    ino_t inode;
    char name[NAME_MAX];
} FileEntry;

// Convert a string to lowercase
void to_lowercase(char *str) {
    for (char *p = str; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }
}

// Comparator function for qsort, case-insensitive
int compare_entries(const void *a, const void *b) {
    const FileEntry *entry1 = (const FileEntry *)a;
    const FileEntry *entry2 = (const FileEntry *)b;
    char name1[NAME_MAX];
    char name2[NAME_MAX];

    // Make copies of the names to convert to lowercase
    strncpy(name1, entry1->name, NAME_MAX);
    strncpy(name2, entry2->name, NAME_MAX);
    name1[NAME_MAX - 1] = '\0';
    name2[NAME_MAX - 1] = '\0';

    to_lowercase(name1);
    to_lowercase(name2);

    // Compare names case-insensitively
    return strcmp(name1, name2);
}

void list_inode(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    FileEntry *entries = NULL;
    size_t capacity = INITIAL_CAPACITY;
    size_t size = 0;

    // Allocate initial memory for entries
    entries = malloc(capacity * sizeof(FileEntry));
    if (entries == NULL) {
        perror("malloc");
        return;
    }

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        free(entries);
        return;
    }

    // Read directory entries and store them
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Allocate more space if necessary
        if (size >= capacity) {
            capacity *= 2;
            entries = realloc(entries, capacity * sizeof(FileEntry));
            if (entries == NULL) {
                perror("realloc");
                closedir(dir);
                return;
            }
        }

        // Construct the full path to the file
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Get file status
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Store the entry
        entries[size].inode = file_stat.st_ino;
        strncpy(entries[size].name, entry->d_name, NAME_MAX);
        entries[size].name[NAME_MAX - 1] = '\0'; // Ensure null termination
        size++;
    }

    // Close the directory
    closedir(dir);

    // Sort entries alphabetically by filename, case-insensitively
    qsort(entries, size, sizeof(FileEntry), compare_entries);

    // Print the sorted entries
    for (size_t i = 0; i < size; i++) {
        printf("%lu %s\n", entries[i].inode, entries[i].name);
    }

    // Free allocated memory
    free(entries);
}

