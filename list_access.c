// list_access.c
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>

// Structure to hold file information
struct file_info {
    char *name;
    time_t access_time;
};

// Function to compare files by access time for qsort
int compare_access_time(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    return (file_b->access_time - file_a->access_time); // Descending order
}

void list_access(const char *path, int show_all) {
    DIR *dir;
    struct dirent *entry;
    struct file_info *files = NULL;
    int file_count = 0;
    int capacity = 10;

    // Allocate initial memory for storing file information
    files = malloc(capacity * sizeof(struct file_info));

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Read and store directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_all is true
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

        // Get file access time
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Store file information
        if (file_count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(struct file_info));
        }
        files[file_count].name = strdup(entry->d_name);
        files[file_count].access_time = file_stat.st_atime;
        file_count++;
    }

    // Sort files by access time
    qsort(files, file_count, sizeof(struct file_info), compare_access_time);

    // Print files
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i].name);
        free(files[i].name);
    }

    // Clean up
    free(files);
    closedir(dir);
}

