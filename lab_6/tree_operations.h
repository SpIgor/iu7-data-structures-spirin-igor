#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void free_tree(tree_t *root);

void postfix(tree_t *root);

void prefix(tree_t *root);

void infix(tree_t *root);

void find_replace(tree_t **branch, tree_t *root);

void remove_word(tree_t **root, int* date);

int compare_date(int *date1, int *date2);

int check(tree_t *root, int *date);

int allocate_element(tree_t **root, char *string);

void to_dot(tree_t *root, FILE *out_file);

void export_to_dot(tree_t *root, FILE *out_file);

tree_t *add_to_tree(tree_t *root, tree_t *tmp);

int check_sting(char *string);

int read_tree_from_file(tree_t **root, FILE *in_file);

#endif
