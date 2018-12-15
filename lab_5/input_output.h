#ifndef __INPUT_OUTPUT_H__
#define __INPUT_OUTPUT_H__

#include "define_file.h"

int **input_matrix(int *n, int *m, int *ret);  // ввод матрицы

void output_sp(matrix_t *matr);  // вывод разреженной матрицы
void output_reg(int **matr, int n, int m);  // вывод обычной матрицы

int** allocate_matrix(int n, int m);  // выделение памяти под матрицу
void free_matrix(int **matr, int n);  // освобождение памяти под матрицу
void free_sp(matrix_t *matr);  // освобождение памяти из-под разряженной матрицы

list_t* push(list_t *head, int x);  // добавление в список list_t элемента x
list_t* reverse(list_t *head);  // обращение списка
matrix_t* convert(int **matr, int n, int m);  // приведение к разреженному формату

#endif
