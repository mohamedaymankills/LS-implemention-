// list_long.c
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include "color.h" // Include the colors header

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

    while ((entry = readdir(dir)) != NULL) {
        // Skip entries that are "." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Skip hidden files unless show_hidden is true
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        // Get the file status
        if (stat(entry->d_name, &file_stat) == -1) {
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
        printf(" %s %s", pw->pw_name, gr->gr_name);

        // File size
        printf(" %5ld", file_stat.st_size);

        // Modification time
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s", time_str);

        // File name
        if (color_output) {
            print_colored(entry->d_name, &file_stat);
            printf("\n");
        } else {
            printf(" %s\n", entry->d_name );
        }
    }

    closedir(dir);
}

