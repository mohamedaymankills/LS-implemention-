// utils.c
#include <ctype.h>
#include <string.h>
#include "utils.h"

void to_lowercase(char *str) {
    for (char *p = str; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }
}

int compare_entries(const void *a, const void *b) {
    const char *name1 = *(const char **)a;
    const char *name2 = *(const char **)b;
    char lower_name1[NAME_MAX];
    char lower_name2[NAME_MAX];

    strncpy(lower_name1, name1, NAME_MAX);
    strncpy(lower_name2, name2, NAME_MAX);
    lower_name1[NAME_MAX - 1] = '\0';
    lower_name2[NAME_MAX - 1] = '\0';

    to_lowercase(lower_name1);
    to_lowercase(lower_name2);

    return strcmp(lower_name1, lower_name2);
}

