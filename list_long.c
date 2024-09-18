// list_long.c
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "color.h"   // Include the colors header
#include "sorting.h" // Include the sorting header

void list_long(const char *path, int show_hidden) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int color_output = isatty(STDOUT_FILENO); // Check if output is a terminal

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Collect directory entries
    char **entries = NULL;
    int num_entries = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_hidden is true
        if (!show_hidden && entry->d_name[0] == '.') {
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

    // Print the sorted entries in long format
    for (int i = 0; i < num_entries; i++) {
        // Get the file status
        if (stat(entries[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Print file type and permissions
        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

        // Number of links
        printf(" %ld", file_stat.st_nlink);

        // Owner and group
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf(" %s %s", pw ? pw->pw_name : "-", gr ? gr->gr_name : "-");

        // File size
        printf(" %5ld", file_stat.st_size);

        // Modification time
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s", time_str);

        // File name
        if (color_output) {
            print_colored(entries[i], &file_stat);
        } else {
            printf(" %s", entries[i]);
        }
        printf("\n");
        free(entries[i]);  // Free the duplicated string
    }

    // Clean up
    free(entries);
    closedir(dir);
}

