/******************************* Name    : sorting.c               *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"

// Case-insensitive comparison function
// Compares two strings in a case-insensitive manner
int case_insensitive_compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a; // Dereference void pointers to char pointers
    const char *str2 = *(const char **)b;

    // Compare characters in a case-insensitive manner
    while (*str1 && *str2) {
        // Convert characters to lowercase for comparison
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
        }
        str1++;
        str2++;
    }
    // If strings are of different lengths, return difference in length
    return *str1 - *str2;
}

// Function to sort directory entries
// Uses qsort with a case-insensitive comparison function
void sort_entries(char **entries, int num_entries) {
    qsort(entries, num_entries, sizeof(char *), case_insensitive_compare);
}

