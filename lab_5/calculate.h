#ifndef __CALCULATE_H__
#define __CALCULATE_H__

#include "define_file.h"
#include <math.h>

int **sum_matrix(int **matrix1, int **matrix2, int n, int m, int **result_matrix);  // суммирование матриц

matrix_t* sum_sp_matrix(matrix_t *sp_fmtr, matrix_t *sp_smtr, int fm_n, int fm_m);  // суммирование матриц в разряженном формате

int compare();  // сравнение времени выполнения

#endif
