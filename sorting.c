// sorting.c
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"

// Case-insensitive comparison function
int case_insensitive_compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Function to sort directory entries
void sort_entries(char **entries, int num_entries) {
    qsort(entries, num_entries, sizeof(char *), case_insensitive_compare);
}

