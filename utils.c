/******************************* Name    : utils.c                 *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <ctype.h>
#include <string.h>
#include "utils.h"

// Converts a string to lowercase
void to_lowercase(char *str) {
    for (char *p = str; *p; ++p) {
        *p = tolower((unsigned char)*p); // Convert each character to lowercase
    }
}

// Compares two entries in a case-insensitive manner
int compare_entries(const void *a, const void *b) {
    const char *name1 = *(const char **)a; // Dereference void pointers to get the strings
    const char *name2 = *(const char **)b;
    char lower_name1[NAME_MAX]; // Buffer to hold lowercase version of name1
    char lower_name2[NAME_MAX]; // Buffer to hold lowercase version of name2

    // Copy strings into buffers
    strncpy(lower_name1, name1, NAME_MAX);
    strncpy(lower_name2, name2, NAME_MAX);
    
    // Ensure buffers are null-terminated
    lower_name1[NAME_MAX - 1] = '\0';
    lower_name2[NAME_MAX - 1] = '\0';

    // Convert both names to lowercase
    to_lowercase(lower_name1);
    to_lowercase(lower_name2);

    // Compare the lowercase versions of the names
    return strcmp(lower_name1, lower_name2);
}

