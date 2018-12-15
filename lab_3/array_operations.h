#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H
#include <stdlib.h>
#include <stdio.h>

void print_array(int *pa, int *pb);

int add_element(int **ps, int *pb, int element, unsigned long long *time);

int delete_element(int **ps, int *pa, unsigned long long *time);

unsigned long long print_sequences(int *pa, int *pb, int *ps);

#endif
