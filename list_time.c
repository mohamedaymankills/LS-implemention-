// list_time.c
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Structure to hold file information
struct file_info {
    char *name;
    time_t mod_time;
};

// Function to compare files by modification time for qsort
int compare_mod_time(const void *a, const void *b) {
    struct file_info *file_a = (struct file_info *)a;
    struct file_info *file_b = (struct file_info *)b;
    return (file_b->mod_time - file_a->mod_time); // Descending order
}

void list_time(const char *path) {
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
        // Get file modification time
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
        files[file_count].mod_time = file_stat.st_mtime;
        file_count++;
    }

    // Sort files by modification time
    qsort(files, file_count, sizeof(struct file_info), compare_mod_time);

    // Print files
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i].name);
        free(files[i].name);
    }

    // Clean up
    free(files);
    closedir(dir);
}

