#ifndef STRUCT_OPERATIONS_H
#define STRUCT_OPERATIONS_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "struct.h"

void print_table(struct line *table, int len_p);

int fill_char_position(char *pole, int len_pole, char *position, char *string);

int fill_int_position(int *pole, char *position, char *string);

int fill_struct(struct line *p, char *string);

void delete_struct_line(struct line *p, int *len_table, int position);

void save_struct(struct line *p, int len_table, FILE* out_file);

#endif
