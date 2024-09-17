// list.h
#ifndef LIST_H
#define LIST_H

void list_all(const char *path, int show_all);
void list_long(const char *path, int show_all);
void list_time(const char *path, int show_all);
void list_creation(const char *path, int show_all);
void list_access(const char *path, int show_all);
void list_inode(const char *path, int show_all);
void list_directory(const char *path);
void list_unsorted(const char *path);
void list_single_column(const char *path, int show_all); // Add declaration for list_single_column

#endif

