#ifndef __INPUT_OUTPUT_H__
#define __INPUT_OUTPUT_H__

#include "define_file.h"
#include "functions.h"

T_t* read_tree(FILE *f, int *ret, balance_t **b_tree, Close_t *close_table, Open_t *open_table, double *coef1, double *coef2, int *size1, int *size2);  // построение дерева

T_t* input_word(T_t *root, int *ret, balance_t **b_tree, Close_t *close_table, Open_t *open_table, double *coef1, double *coef2, int *size1, int *size2);  // добавление элемента

void export_to_dot(FILE *f,const char *tree_name, T_t *root);  // вывод дерева в файл
void export_to_dot_balance(FILE *f,const char *tree_name, balance_t *root);  // вывод дерева в файл

void free_tree(T_t *root);  // освобождение памяти
void free_balance_tree(balance_t *root);  // освобождение памяти

void my_strcopy(char *str_1, char *str_2);  // копирование строки
int check_word(char *word);  // проверка является ли строка словом

void clean_tables(Close_t *close, Open_t *open, int size1, int size2);  // очистка таблиц

#endif