// colors.h
#ifndef COLORS_H
#define COLORS_H

#include <sys/stat.h>

const char *get_color(const struct stat *file_stat);
void print_colored(const char *name, const struct stat *file_stat);

#endif

