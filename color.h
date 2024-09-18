/******************************* Name    : color.h                 *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 
#ifndef COLORS_H
#define COLORS_H

#include <sys/stat.h>

const char *get_color(const struct stat *file_stat);
void print_colored(const char *name, const struct stat *file_stat);

#endif

