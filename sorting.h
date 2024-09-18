/******************************* Name    : sorting.h               *******************************/   
/******************************* Author  : Mohamed Ayman           *******************************/  
/******************************* Date    : 10-9-2024               *******************************/  
/******************************* version : 0.3.1                   *******************************/ 
#ifndef SORTING_H
#define SORTING_H

// Function to perform case-insensitive comparison
int case_insensitive_compare(const void *a, const void *b);

// Function to sort directory entries
void sort_entries(char **entries, int num_entries);

#endif // SORTING_H

