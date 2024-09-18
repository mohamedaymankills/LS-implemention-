/******************************* Name    : utils.h                 *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define NAME_MAX 255  // Maximum length of a filename

// Convert a string to lowercase
void to_lowercase(char *str);

// Comparator function for qsort, case-insensitive
int compare_entries(const void *a, const void *b);

#endif // UTILS_H

