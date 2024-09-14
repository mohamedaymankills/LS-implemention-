#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *file_name) {
    struct stat file_stat;
    if (stat(file_name, &file_stat) == -1) {
        perror("stat");
        return;
    }

    // File type and permissions
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
    printf(" %s\n", file_name);
}

void list_directory(const char *path, int show_all, int long_format) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Read and print directory entries
    while ((entry = readdir(dir)) != NULL) {
        // If -a flag is not present, skip hidden files
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }
        if (long_format) {
            print_file_info(entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int show_all = 0;      // Flag for the -a option
    int long_format = 0;   // Flag for the -l option
    const char *path = ".";  // Default path is current directory

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_all = 1;  // Enable showing hidden files
        } else if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;  // Enable long listing format
        } else {
            path = argv[i];  // Treat other arguments as the directory path
        }
    }

    // List the directory contents
    list_directory(path, show_all, long_format);

    return 0;
}

