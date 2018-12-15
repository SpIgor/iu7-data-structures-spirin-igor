#include "calculate.h"
#include "input_output.h"

// Функция сложения матриц
int **sum_matrix(int **matrix1, int **matrix2, int n, int m, int **result_matrix)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result_matrix[i][j] = matrix1[i][j] + matrix2[i][j];

    return result_matrix;
}

// Функция подсчета элементов в разряженной матрице
int count_elements(matrix_t *matrix1)
{
    int ind;
    list_t *tmp = matrix1 -> IA;
    while (tmp -> next)
    {
        ind = tmp->index;
        tmp = tmp -> next;
    }

    return ind;
}

// Сложение разряженных матриц
matrix_t* sum_sp_matrix(matrix_t *sp_fmtr, matrix_t *sp_smtr, int fm_n, int fm_m)
{
    matrix_t *tmp_smtr = sp_smtr;
    matrix_t *tmp_fmtr = sp_fmtr;
    int len = 0;
    int ind;
    matrix_t *sp_rmtr = malloc(sizeof(matrix_t));
    len += count_elements(tmp_smtr) + count_elements(tmp_fmtr);
    sp_rmtr -> A = calloc(len, sizeof(int));
    sp_rmtr -> J = calloc(len, sizeof(int));
    sp_rmtr -> IA = tmp_fmtr -> IA;
    int r_len = 0, f_len, s_len;
    int s_prev = 0, f_prev = 0;

    list_t *tmp = sp_rmtr -> IA;
    len = 0;

    while (tmp_fmtr -> IA -> next)
    {
        f_len = tmp_fmtr -> IA -> index;
        s_len = tmp_smtr -> IA -> index;
        while (f_prev < f_len && s_prev < s_len)
        {
            if (tmp_fmtr -> J[f_prev] < tmp_smtr -> J[s_prev])
            {
                sp_rmtr -> A[r_len] = tmp_fmtr -> A[f_prev];
                sp_rmtr -> J[r_len] = tmp_fmtr -> J[f_prev];
                f_prev++;
                r_len++;
            }
            else if (tmp_fmtr -> J[f_prev] == tmp_smtr -> J[s_prev])
            {
                if (tmp_fmtr -> A[f_prev] + tmp_smtr -> A[s_prev])
                {
                    sp_rmtr -> A[r_len] = tmp_fmtr -> A[f_prev] + tmp_smtr -> A[s_prev];
                    sp_rmtr -> J[r_len] = tmp_fmtr -> J[f_prev];
                    r_len++;
                }
                f_prev++;
                s_prev++;
            }
            else if (tmp_fmtr -> J[f_prev] > tmp_smtr -> J[s_prev])
            {
                sp_rmtr -> A[r_len] = tmp_smtr -> A[s_prev];
                sp_rmtr -> J[r_len] = tmp_smtr -> J[s_prev];
                s_prev++;
                r_len++;
            }
        }
        while (f_prev < f_len)
        {
            sp_rmtr -> A[r_len] = tmp_fmtr -> A[f_prev];
            sp_rmtr -> J[r_len] = tmp_fmtr -> J[f_prev];
            f_prev++;
            r_len += 1; 
        }
        while (s_prev < s_len)
        {
            sp_rmtr -> A[r_len] = tmp_smtr -> A[s_prev];
            sp_rmtr -> J[r_len] = tmp_smtr -> J[s_prev];
            s_prev++;
            r_len += 1;
        }
        if (s_len && f_len)
        {
            f_prev = f_len;
            s_prev = s_len;
        }
        tmp_fmtr -> IA = tmp_fmtr -> IA -> next;
        tmp_smtr -> IA = tmp_smtr -> IA -> next;
        if (r_len - ind)
            tmp -> index = r_len;
        else
            tmp -> index = 0;
        tmp = tmp -> next;
        ind = r_len;
    }
    sp_rmtr -> A = realloc(sp_rmtr -> A, (r_len + 1) * sizeof(int));
    sp_rmtr -> J = realloc(sp_rmtr -> J, (r_len + 1) * sizeof(int));
    sp_rmtr -> A[r_len] = 0;
    sp_rmtr -> J[r_len] = 0;

    return sp_rmtr;
}

int rand_int(int a)  // случайное целое число
{
    return rand() / (double) RAND_MAX * a;
}

int **generate_matr(int n, int m, int percent)  // генерация матрицы
{
    int **matrix;
    int i, j, count;

    srand(time(NULL));

    matrix = allocate_matrix(n, m);

    if (matrix)
    {
        count = round(n*m* (double)percent/100);
        for (int k = 0; k < count; k++)
        {
            i = rand_int(n);
            j = rand_int(m);
            if (matrix[i][j] != 0)
                k--;
            else
                matrix[i][j] = rand_int(100);
        }
    }

    return matrix;
}



// Сравнение времени сложения на матрицах двух типов
int compare()
{
    int ret = OK;  // код возврата
    time_t t1, t2;  // переменные для замеров времени
    int percent;  // процент заполнения матриц
    int f_n, f_m, s_n, s_m;  // размеры
    int **fmtr, **smtr, **rmtr;  // матрицы в обычном формате
    matrix_t *sp_fmtr, *sp_smtr;  // матрицы в разряженном формате

    printf("Введите размер первой матрицы (от 1 до %d): ", MAX_NUMBER);
    if (scanf("%d %d", &f_n, &f_m) && f_m > 0 && f_n > 0 && f_m <= MAX_NUMBER && f_n <= MAX_NUMBER)
    {
        printf("\n");
        printf("Введите размеры второй матрицы (от 1 до %d ): ", MAX_NUMBER);
        if (scanf("%d %d", &s_n, &s_m) != 2)
        {
            for(;getchar() != '\n';);
            printf("Некорректный ввод\n");
            ret = WRONG_INPUT;

        }
        else if (s_n <= 0 || s_m <= 0 || s_m > MAX_NUMBER || s_n > MAX_NUMBER)
        {
            printf("Недопустимые значения\n");
            ret = WRONG_INPUT;
        }
        else
        {
            if (s_m != f_m || f_n != s_n)
            {
                printf("ОШИБКА: Размеры матриц должны быть одинаковыми\n\n");
                ret = NOT_JOINED;
            }
            else
            {
                printf("\n");
                printf("Введите процент заполнения (от 1 до 100): ");
                if (scanf("%d", &percent) != 1)
                {
                    for(;getchar() != '\n';);
                    printf("Некорректный ввод\n");
                    ret = WRONG_INPUT;
                }
                else if (percent < 1 || percent > 100)
                {
                    printf("Недопустимое значения\n");
                    ret = WRONG_INPUT;
                }
                else
                {
                    fmtr = generate_matr(f_n, f_m, percent);
                    smtr = generate_matr(s_n, s_m, percent);
                    sp_fmtr = convert(fmtr, f_n, f_m);
                    sp_smtr = convert(smtr, s_n, s_m);

                    printf("\nВыделяемая память для матриц в обычном формате 2 * %d * %d * sizeof(int) = %lu\n", f_n , f_m, 2 * f_n * f_m * sizeof(int));
                    printf("Разреженном формате      %lu\n\n", 2 * sizeof(int) * (int)(f_n * f_m * percent / 100) * 2);

                    t1 = clock();
                    rmtr = allocate_matrix(f_n, f_m);
                    sum_matrix(fmtr, smtr, f_n, f_m, rmtr);
                    t2 = clock();
                    printf("Время для сложения в обычном формате:  %ld\n", t2 - t1);

                    t1 = clock();
                    sum_sp_matrix(sp_fmtr, sp_smtr, f_n, f_m);
                    t2 = clock();
                    printf("Время для сложения в разряженном формате:  %ld\n\n", t2 - t1);
                }
            }
        }
    }
    else
    {
        for(;getchar() != '\n';);
        printf("    Некорректное значение\n");
        ret = WRONG_INPUT;
    }
    return ret;
}
