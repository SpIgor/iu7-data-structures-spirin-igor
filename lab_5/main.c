#include "define_file.h"
#include "calculate.h"
#include "input_output.h"

int main()
{
    int rn = OK;  // код ошибки
    int **fmtr, **smtr, **rmtr;  // все матрицы в обычном формате
    // число строк и столбцов 
    int fm_n = 0, fm_m = 0;  // Для первой матрицы
    int sm_n = 0, sm_m = 0;  // Для второй матрицы
    int rm_n = 0, rm_m = 0;  // Для матрицы результата
    matrix_t  *sp_fmtr, *sp_smtr, *sp_rmtr;  // матрицы в разреженном формате
    int choice = -1;  // выбор меню
    int exist_fm = 0, exist_sm = 0, exist_r1 = 0, exist_r2 = 0;  // проверка исходных данных

    sp_smtr = NULL;
    sp_fmtr = NULL;
    sp_rmtr = NULL;

    while(choice)
    {
        printf("\
1 - ввести первую матрицу\n\
2 - ввести вторую матрицу\n\
3 - вывести матрицы в разреженном формате\n\
4 - вывести матрицы в обычном формате\n\
5 - сложить матрицы в разреженном формате\n\
6 - сложить матрицы в обычном формате\n\
7 - сравнить время работы\n\
0 - покинуть программу\n\n");
        printf("Выбирете опцию: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Введен неверный символ\n");
            rn = WRONG_INPUT;
            choice = 0;
        }
        switch(choice)
        {
            case 0: printf("Завершение работы программы\n\n");                 
                    if (exist_fm)
                        free_matrix(fmtr, fm_n);
                    if (exist_sm)
                       free_matrix(smtr, sm_n);
                    if (exist_r1)
                        free_matrix(rmtr, rm_n);
                    break;
            case 1: if (exist_fm)
                        free_matrix(fmtr, fm_n);
                    fmtr = input_matrix(&fm_n, &fm_m, &rn);
                    if (!rn)
                    {
                       sp_fmtr = convert(fmtr, fm_n, fm_m);
                       printf("Матрица успешно переведена в разреженный формат\n\n");
                       exist_fm = 1;
                    }
                    break;
            case 2: if (exist_sm)
                        free_matrix(smtr, sm_n);
                    smtr = input_matrix(&sm_n,&sm_m, &rn);
                    if (!rn)
                    {
                        sp_smtr = convert(smtr, sm_n, sm_m);
                        printf("Матрица успешно переведена в разреженный формат\n\n");
                        exist_sm = 1;
                    }
                    break;
            case 3: if (exist_fm && exist_sm)
                    {
                        printf("Первая матрица:\n");
                        output_sp(sp_fmtr);
                        printf("Вторая матрица:\n");
                        output_sp(sp_smtr);
                    }
                    else
                        printf("Не все матрицы введены\n\n");
                    break;
            case 4: if (exist_sm && exist_fm)
                    {
                        printf("Первая матрица:\n");
                        output_reg(fmtr,fm_n,fm_m);
                        printf("\n");
                        printf("Вторая матрица:\n");
                        output_reg(smtr, sm_n, sm_m);
                        printf("\n");
                    }
                    else
                        printf("Не все матрицы введены\n\n");
                    break;
            case 5: if (exist_fm && exist_sm)
                    {
                        if (fm_n == sm_n || fm_m == sm_m)
                        {
                            sp_rmtr = sum_sp_matrix(sp_fmtr, sp_smtr, fm_n, fm_m);
                            printf("Результат сложения:\n");                            
                            output_sp(sp_rmtr);
                            exist_r2 = 1;
                            printf("Завершение работы\n");
                            exit(1);
                        }
                        else
                            printf("ОШИБКА: невозможно сложить\n\n");
                    }
                    else
                        printf("Вы не ввели данные\n\n");
                    break;
            case 6: if (exist_fm && exist_sm)
                    {
                        if (fm_n != sm_n || fm_m != sm_m)
                            printf("Нельзя сложить матрицы\n");
                        else
                        {
                            if (rmtr)
                                free_matrix(rmtr,rm_n);
                            rm_n = fm_n;
                            rm_m = fm_m;
                            rmtr = allocate_matrix(fm_n, fm_m);
                            rmtr = sum_matrix(fmtr, smtr, sm_n, sm_m, rmtr);
                            printf("Результат сложения:\n\n");
                            output_reg(rmtr, rm_n, rm_m);
                            exist_r1 = 1;
                            printf("\n");
                        }
                    }
                    else
                        printf("Введены не все матрицы\n\n");
                    break;
            case 7: rn = compare();
                    break;
            default: printf("Введен неизвестный пункт меню\n\n");
                     rn = WRONG_MENU;
                     break;
        }
    }

    return rn;
}
