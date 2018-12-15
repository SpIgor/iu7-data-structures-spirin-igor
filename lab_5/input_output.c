#include "input_output.h"

int** allocate_matrix(int n, int m)  // выделение памяти
{
    int **matrix;  // Матрица

    matrix = (int **)malloc(n*sizeof(int *));
    if (matrix)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i] = (int *)calloc(m, sizeof(int));
            if (!matrix[i])
                return NULL;
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int n)  // освобождение памяти
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void free_sp(matrix_t *matr)  // освобождение памяти из-под разряженной матрицы
{
    list_t *tmp;  // Переменная для освобождения памяти

    free(matr->A);
    free(matr->IA);
    while (matr->IA)
    {
        tmp = matr->IA->next;
        free(matr->IA);
        matr->IA = tmp;
    }
}

int matrix_size(FILE *f, int *n, int *m)  // ввод размеров матрицы из файла
{
    int ret;  // Код возврата
    if (f == stdin)
    {
        printf("Введите размеры матрицы (от 1 до %d ): ", MAX_NUMBER);
        if (scanf("%d %d", n, m) != 2)
        {
            printf("    Некорректные данные\n\n");
            ret = WRONG_INPUT;
        }
        else if (*n < 1 || *n > MAX_NUMBER || *m < 1 || *m > MAX_NUMBER)
        {
            printf("Введены значения, превышающие максимально допустимый размер матрицы или отрицательные числа\n\n");
            ret = WRONG_INPUT;
        }
        else
        {
            ret = OK;
            printf("\n");
        }
    }
    else
    {
        if (fscanf(f, "%d %d", n, m) != 2)
        {
            printf("Некорректные данные в файле\n\n");
            ret = WRONG_INPUT;
        }
        else if (*n < 1 || *n > MAX_NUMBER || *m < 1 || *m > MAX_NUMBER)
        {
            printf("Введены значения, превышающие максимально допустимый размер матрицы или отрицательные числа\n\n");
            ret = WRONG_INPUT;
        }
        else
            ret = OK;
    }
    return ret;
}

int **read_file_matrix(FILE *f, int *n, int *m, int *ret)  // ввод матрицы из файла
{
    int **matrix = NULL;  // Матрица
    int flag = 1;  // "Логическая" переменная
    int i, j;  // Индексы матрицы

    *ret = matrix_size(f, n, m);
    if (*ret == OK)
    {
        matrix = allocate_matrix(*n, *m);
        if (matrix)
        {
            if (f == stdin)
                printf("Введите матрицу:\n");
            for (i = 0; i < *n && flag; i++)
            {
                for (j = 0; j < *m-1 && flag; j++)
                    if (fscanf(f, "%d", &matrix[i][j]) != 1)
                        flag = 0;
                if (fscanf(f, "%d", &matrix[i][j]) != 1)
                    flag = 0;
            }
            if (!flag)
            {
                if (f == stdin)
                    for(;getchar() != '\n';);
                printf("Некорректные входные данные\n");
                *ret = WRONG_INPUT;
                free_matrix(matrix, *n);
                matrix = NULL;
            }
        }
        else
        {
            printf("Ошибка при выделении памяти\n");
            *ret = MEMORY_ERR;
        }
    }
    else
    {
        if (f == stdin)
            for(;getchar() != '\n';);
        printf("Некоректные входные данные\n");
        *ret = WRONG_INPUT;
    }

    return matrix;
}

int **read_sp(int *n, int *m, int *ret)
{
    int **matrix = NULL;  // Матрица
    int flag = 1;  // Лог переменная
    int i = 0, j = 0, x = 0;  // Индексы
    int choice;  // Переменная выбоа меню

    matrix = allocate_matrix(*n, *m);
    if (matrix)
    {
        printf("\n");
        printf("Ввод матрицы поэлементно в формате: <элемент> <строковый индекс> <столбцевой индекс>\n    Введите элемент: ");
        while (flag)
        {
            if (scanf("%d %d %d", &x,&i, &j) == 3 && (i - 1 >= 0) && (i - 1 < *n) && (j - 1 >= 0) && (j - 1 < *m))
            {
                *ret = OK;
                printf("\n");
                matrix[i - 1][j - 1] = x;
                printf("Завершить ввод?\n    0 - Нет, 1 - Да: ");

                if (scanf("%d", &choice) == 1)
                {
                    if (choice == 1)
                    {
                        flag = 0;
                        printf("Ввод завершен.\n\n");
                    }
                    else
                        printf("Введите элемент: ");
                }
                else
                {
                    for (;getchar() != '\n';);
                    printf("Некорректная команда\n\n");
                    *ret = WRONG_MENU;
                }
            }
            else
            {
                for (;getchar() != '\n';);
                *ret = WRONG_INPUT;
                printf("Некорректные входные данные\n\n");
            }
        }
    }

    return matrix;
}

int **input_matrix(int *n, int *m, int *ret)  // ввод матрицы
{
    int choice = -1;
    FILE *f_in;
    int **matrix = NULL;
    char file_name[20];
    printf("\n");
    printf("Выберите способ ввода матрицы:\n\
1 - вручную в обычном формате\n\
2 - вручную в разреженном формате\n\
3 - из файла\n\n");
    printf("Выберите опцию: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Введен неверный символ.\n");
        choice = 0;
    }
    switch(choice)
    {
        case 1: matrix = read_file_matrix(stdin, n, m, ret);
                break;
        case 2: printf("Введите размеры матрицы (<число строк> <число столбцов>) от 1 до %d: ",MAX_NUMBER);
                if (scanf("%d %d",n, m) != 2)
                {
                    printf("Некореектные данные\n\n");
                    *ret = WRONG_INPUT;
                }
                else if (*n < 1 || *n > MAX_NUMBER || *m < 1 || *m > MAX_NUMBER)
                {
                    printf("Введены значения, превышающие максимально допустимый размер матрицы или отрицательные числа\n\n");
                    *ret = WRONG_INPUT;
                }
                else
                    matrix = read_sp(n, m, ret);
                break;
        case 3: printf("Введите имя файла с матрицей: ");
                scanf("%s", file_name);
                f_in = fopen(file_name, "r");
                if (f_in)
                {
                    matrix = read_file_matrix(f_in, n, m, ret);
                    fclose(f_in);
                }
                else
                {
                    printf("ОШИБКА: не удалось открыть файл\n\n");
                    *ret = CANNOT_OPEN;
                    matrix = NULL;
                }
                break;
        case 0: printf("Возвращение в главное меню\n\n");
                break;
        default: printf("Введен неизвестный пункт меню\n\n");
                 *ret = WRONG_MENU;
                 break;
    }
    return matrix;
}

void output_sp(matrix_t *matr)  // вывод разреженной матрицы
{
    int x = 0;
    list_t *tmp;
    int i = 0;

    if (matr->A[0])
    {
        printf(" A:  ");
        while(matr->A[i])
        {
            printf("%d ", matr->A[i]);
            i++;
        }
        printf("\n");
        printf(" J:  ");
        i = 0;
        while (matr->J[i])
        {
            printf("%d ", matr->J[i]);
            i++;
        }
        printf("\n");
        printf("IA:  ");

        tmp = matr->IA;
        while(tmp->next)
        {
            printf("%d ", tmp->index);
            tmp = tmp->next;
        }
        printf("\n");
    }
    else
        printf("Нулевая матрица\n");
    printf("\n");
}

void output_reg(int **matr, int n, int m)  // вывод обычной матрицы
{
    if (matr)
    {
        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                printf("%d ", matr[i][j]);
            printf("\n");
        }
    }
}

list_t* push(list_t *head, int x)  // добавление компоненты A и J
{
    list_t *tmp = malloc(sizeof(list_t));

    if (tmp)
    {
        tmp->index = x;
        tmp->next = head;
        head = tmp;
        return head;
    }
    else
        return NULL;
}

list_t* reverse(list_t *head)  // обращение списка в нужном порядке
{
    list_t *prev = NULL, *curr, *next;

    curr = head;
    next = curr->next;

    while (next)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;

    return curr;
}

matrix_t* convert(int **matr, int n, int m)  // приведение к разреженному формату
{
    matrix_t *sp;
    int i = 0, j = 0, k = 0, x = k;
    sp = (matrix_t *)calloc(1,sizeof(matrix_t));
    sp->A = calloc(n*m,sizeof(int));
    sp->J = calloc(n*m,sizeof(int));
    for(i = 0; i < n; i++)
    {
        x = 0;
        for(j = 0; j < m; j++)
        {
            if (matr[i][j])
            {
                sp->A[k] = matr[i][j];
                sp->J[k] = j + 1;
                x = k + 1;
                k++;
            }
        }
        sp->IA = push(sp->IA, x);
    }
    sp->IA = push(sp->IA, k + 1);
    sp->IA = reverse(sp->IA);
    sp->A[k] = 0;
    sp->J[k] = 0;
    return sp;
}
