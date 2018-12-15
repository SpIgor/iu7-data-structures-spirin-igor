#ifndef SORTS_H
#define SORTS_H
#include "struct.h"
#include <stdlib.h>
#include <time.h>

int** allocate_matrix(int len_struct);

void free_matrix(int **matrix, int len_struct);

void copy_str_to_matrix(int **matrix, struct line *p, int len_struct);

void print_matrix(int **matrix, int len_struct);

unsigned long long bubble_sort_str(struct line *p, int len_table);

unsigned long long insert_sort_str(struct line *p, int len_table);

unsigned long long insert_sort_mtr(int **matrix, int len_table);

unsigned long long bubble_sort_mtr(int **array, int len_array);

#endif
