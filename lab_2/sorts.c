#include "sorts.h"
#include "struct_operations.h"
#include "time.h"

// Функция выделения памяти для матрицы
int** allocate_matrix(int len_table)
{
    int **matrix;  // Указатель на матрицу

    matrix = calloc(len_table, sizeof(int*));
    if (!matrix)
        return NULL;

    for (int i = 0; i < len_table; i++)
    {
        matrix[i] = (int*) malloc(2 * sizeof(int));
        if (!matrix[i])
        {
            free_matrix(matrix, len_table);

            return NULL;
        }
    }

    return matrix;
}

// Функция освобождения памяти матрицы
void free_matrix(int **matrix, int len_table)
{
    for (int i = 0; i < len_table; i++)
        free(matrix[i]);
    free(matrix);
}

// Функция заполнения матрицы ключей
void copy_str_to_matrix(int **matrix, struct line *p, int len_table)
{
    for (int i = 0; i < len_table; i++)
    {
        matrix[i][0] = i;
        matrix[i][1] = table[i].cost;
    }
}

// Функция печати матрицы ключей
void print_matrix(int **matrix, int len_table)
{
    int count = 1;  // Переменная подсчета номера строки

    printf("|Номер|Позиция|Значение поля|\n");
    for (int i = 0; i < len_table; i++)
    {
        printf("|%5d|%7d|%13d|\n", count, matrix[i][0] + 1, matrix[i][1]);
        count++;
    }
}

// Функция сортировки матрицы методом простых вставок
unsigned long long insert_sort_mtr(int **matrix, int len_table)
{
    int sorted = 0;  // Длина отсортированной части
    int count;  // Новая позиция элемента
    int *spare;  // Переменная для обмена
    unsigned long long time1 = clock(), time2;  // Переменные для замера времени сортировки

    while (sorted < len_table - 1)
    {
        if (matrix[sorted][1] > matrix[sorted + 1][1])
        {
            count = 0;
            while (count < (sorted + 1) && matrix[sorted + 1][1] > matrix[count][1])
                count++;
            spare = matrix[sorted + 1];
            for (int i = sorted + 1; i > count; i--)
                matrix[i] = matrix[i - 1];
            matrix[count] = spare;
        }
        sorted++;
    }
    time2 = clock();

    return time2 - time1;
}

// Функция сортировки структуры методом простых вставок
unsigned long long insert_sort_str(struct line *p, int len_table)
{
    int sorted = 0;  // Длина отсортированной части
    int count;  // Новая позиция элемента
    struct line spare;  // Переменная для обмена
    unsigned long long time1 = clock(), time2;  // Переменные для замера времени сортировки

    while (sorted < len_table - 1)
    {
        if (p[sorted].cost > p[sorted + 1].cost)
        {
            count = 0;
            while (count < (sorted + 1) && p[sorted + 1].cost > p[count].cost)
                count++;
            spare = p[sorted + 1];
            for (int i = sorted + 1; i > count; i--)
                p[i] = p[i - 1];
            p[count] = spare;
        }
        sorted++;
    }
    time2 = clock();

    return time2 - time1;
}

// Функция сортировки структуры методом простого обмена
unsigned long long bubble_sort_str(struct line *p, int len_table)
{
    struct line spare;  // Переменная для обмена
    unsigned long long time1 = clock(), time2;  // Переменные для замера времени сортировки

    for (int i = 0 ; i < len_table - 1; i++) 
       for (int j = 0 ; j < len_table - i - 1; j++)
           if (p[j].cost > p[j+1].cost)
           {
              //time1 = tick();
              spare = p[j];
              p[j] = p[j+1];
              p[j+1] = spare; 
              //time2 = tick();
           }
    time2 = clock();

    return time2 - time1;
}

// Функция сортировки матрицы методом простого обмена
unsigned long long bubble_sort_mtr(int **matrix, int len_table)
{
    int *spare;  // Переменная для обмена
    //int flag = 1;
    unsigned long long time1 = clock(), time2;  // Переменные для замера времени сортировки

/*
    while (flag == 1)
    {
        flag = 0;
        for (int i = 0;i < len_table - 1;i++)
            if (matrix[i][1] > matrix[i+1][1])
            {
                spare = matrix[i];
                matrix[i] = matrix[i+1];
                matrix[i+1] = spare;
                flag = 1;
            }
    }


*/
    for (int i = 0 ; i < len_table - 1; i++) 
       for (int j = 0 ; j < len_table - i - 1; j++)
            if (matrix[j][1] > matrix[j+1][1])
            {
                //time1 = tick();
                spare = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = spare;
                //time2 = tick();
            }
            
    time2 = clock();

    return time2 - time1;
}

