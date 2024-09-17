// colors.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define DEFAULT_COLOR "\033[0m"
#define DIR_COLOR "\033[1;34m"
#define EXEC_COLOR "\033[1;32m"
#define LINK_COLOR "\033[1;36m"
#define SPECIAL_COLOR "\033[1;33m"

// Function to get the color based on the file type
const char *get_color(const struct stat *file_stat) {
    if (S_ISDIR(file_stat->st_mode)) {
        return DIR_COLOR; // Directory color
    } else if (S_ISLNK(file_stat->st_mode)) {
        return LINK_COLOR; // Symbolic link color
    } else if (file_stat->st_mode & S_IXUSR) {
        return EXEC_COLOR; // Executable color
    } else if (S_ISCHR(file_stat->st_mode) || S_ISBLK(file_stat->st_mode)) {
        return SPECIAL_COLOR; // Special files (character/block devices)
    }
    return DEFAULT_COLOR; // Default color for other file types
}

// Function to print the file name with color
void print_colored(const char *name, const struct stat *file_stat) {
    const char *color = get_color(file_stat);
    printf("%s%s%s", color, name, DEFAULT_COLOR);
}

