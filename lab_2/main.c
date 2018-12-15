#include "main.h"
#include "struct.h"
#include "struct_operations.h"
#include "string_operations.h"
#include "sorts.h"

// Функция вывода таблицы по условиям задания
void print_result(struct line *p, int len_table, char *colour)
{
    int count = 1; // Переменная для подсчета номера строки

    printf("|Номер|Марка автомобиля|Страна| Стоимость |Цвет автомобиля| Год |   Пробег   |Ремонты|\n");
    for (int i = 0; i < len_table; i++)
    {
        if (strcmp(table[i].colour, colour) == 0 && table[i].flag == 1 && table[i].probeg < 10000 && table[i].count == 0)
        {
            printf("|%5d|", count);
            printf("%16s|", table[i].marka);
            printf("%6s|", table[i].country);
            printf("%11d|", table[i].cost);
            printf("%15s|", table[i].colour);
            printf("%5d|", table[i].year_o);
            printf("%12d|", table[i].probeg);
            printf("%7d|", table[i].count);
            count += 1;
            printf("\n");
        }
    }
}

int main(int argc, char **argv)
{
    FILE* in_file, *out_file, *long_file;  // Переменные для используемых файлов
    int rn = OK;  // Код ошибки
    char string[LEN_STRING];  // Входящая строка
    char colour[LEN_COLOUR];  // Строка для выполнения задания
    int len_table = 0;  // Длина считанной таблицы
    int choise = -1, choise1 = -1, position = -1;  // Переменные для работы меню программы
    int **matrix = NULL, **matrix1 = NULL, **matrix2 = NULL; // Матрицы для сортировок ключей
    unsigned long long bbl_mtr = 0, bbl_str = 0, ins_str = 0, ins_mtr = 0;  // Переменные для записи времени сортировок
    int flag = 0;  // Логическая переменная

    if (argc == 3)
    {
        in_file = fopen(argv[1], "r");
        out_file = fopen(argv[2], "w");

        if (in_file && out_file)
        {
            while (len_table < LEN_TABLE && fgets(string, LEN_STRING, in_file) != NULL && rn == OK)
            {
                rn = fill_struct(&table[len_table], string);
                len_table++;
            }
            if (fgets(string, LEN_STRING, in_file) != NULL && rn == OK)
            {
                printf("Переполнение таблицы\n");
                rn = OVERFLOW;
            }
            if (rn == OK)
                while (choise != 0 && flag == 0)
                {
                    printf("\n");
                    printf("1 - вывод таблицы\n");
                    printf("2 - добавление строки\n");
                    printf("3 - удаление строки\n");
                    printf("4 - сортировка\n");
                    printf("5 - вывод таблицы задания\n");
                    printf("6 - замер времени на сортировку\n");
                    printf("0 - выход\n");

                    printf("\nВыбирете опцию: ");
                    if (scanf("%d", &choise) == 0)
                        flag = 1;

                    if (choise == 1)
                    {
                        printf("\n");
                        printf("|Номер|Марка автомобиля|Страна| Стоимость |Цвет автомобиля| Год |   Пробег   |Ремонты|\n");
                        print_table(table, len_table);
                    }
                    else if (choise == 2)
                    {
                        printf("Правила ввода: марка(%d);страна(%d);стоимость;цвет(%d);год выпуска/гарантия;пробег;количество ремонтов;\n", LEN_MARKA, LEN_COUNTRY, LEN_COLOUR);

                        printf("Введите новую строку: ");
                        fgets(string, LEN_STRING, stdin);
                        string[0] = '\0';
                        fgets(string, LEN_STRING, stdin);
                        if (len_table < LEN_TABLE)
                        {
                            if (count_positions(string, len(string)) == 5 || count_positions(string, len(string)) == 7)
                            {
                                rn = fill_struct(&table[len_table], string);
                                if (rn == OK)
                                {
                                    len_table++;
                                    if (matrix != NULL)
                                    {
                                        free_matrix(matrix, len_table - 1);
                                        matrix = allocate_matrix(len_table);
                                        copy_str_to_matrix(matrix, table, len_table);
                                    }
                                }
                                else
                                    printf("Неверный формат ввода\n");
                            }
                            else
                                printf("Неверное количество полей\n");
                        }
                        else
                        {
                            printf("Переполнение таблицы\n");
                            choise = 0;
                            rn = OVERFLOW;
                        }
                    }
                    else if (choise == 3)
                    {
                        printf("Номер удаляемой строки: ");
                        scanf("%d", &position);
                        if (position <= len_table && position > 0)
                        {
                            delete_struct_line(table, &len_table, position - 1);
                            if (matrix != NULL)
                            {
                                free_matrix(matrix, len_table + 1);
                                matrix = allocate_matrix(len_table);
                                copy_str_to_matrix(matrix, table, len_table);
                            }
                        }
                        else
                            printf("Нет такого номера\n");
                    }
                    else if (choise == 4)
                    {
                        printf("Сортировка по стоимости\n");
                        if (matrix == NULL)
                        {
                            matrix = allocate_matrix(len_table);
                            copy_str_to_matrix(matrix, table, len_table);
                        }
                        printf("    1 - Сортировка таблицы ключей\n");
                        printf("    2 - Сортировка исходной таблицы\n");
                        printf("    3 - Вывод таблицы ключей\n");
                        printf("    4 - Вывод таблицы по ключам\n");
                        printf("    Выбирете опцию: ");
                        scanf("%d", &choise1);
                        printf("\n");
                        if (choise1 == 1 || choise1 == 2)
                        {
                            printf("       1 - сортировка пузырьком\n");
                            printf("       2 - сортировка вставками\n");
                            printf("       Выбирете опцию: ");
                        }
                        if (choise1 == 1)
                        {
                            scanf("%d", &choise);
                            if (choise == 1)
                                bubble_sort_mtr(matrix, len_table);
                            else if (choise == 2)
                                insert_sort_mtr(matrix, len_table);
                            else
                                printf("Нет такой опции\n");
                        }
                        else if (choise1 == 2)
                        {
                            scanf("%d", &choise);
                            if (choise == 1)
                                bubble_sort_str(table, len_table);
                            else if (choise == 2)
                                insert_sort_str(table, len_table);
                            else
                                printf("Нет такой опции\n");
                        }
                        else if (choise1 == 3 && matrix != NULL)
                            print_matrix(matrix, len_table);
                        else if (choise1 == 4)
                        {
                            for (int i = 0; i < len_table; i++)
                            {
                                printf("%16s|", table[matrix[i][0]].marka);
                                printf("%6s|", table[matrix[i][0]].country);
                                printf("%11d|", table[matrix[i][0]].cost);
                                printf("%15s|", table[matrix[i][0]].colour);
                                if (table[matrix[i][0]].flag == 1)
                                {
                                    printf("%5d|", table[matrix[i][0]].year_o);
                                    printf("%12d|", table[matrix[i][0]].probeg);
                                    printf("%7d|", table[matrix[i][0]].count);
                                }
                                else
                                    printf("%5d|", table[matrix[i][0]].year_n);
                                printf("\n");
                            }
                        }
                        else
                            printf("Нет такой опции\n");
                    }
                    else if (choise == 5)
                    {
                        printf("Введиты искомый цвет\n");
                        scanf("%s", colour);
                        printf("\n");
                        print_result(table, len_table, colour);
                    }
                    else if (choise == 6)
                    {
                        printf("Сортировка по стоимости\n");
                        long_file = fopen("out.txt", "r");
                        if (long_file == NULL)
                            printf("Не могу открыть файл для сортировки\n");
                        else if (ins_str == 0 && ins_mtr == 0 && bbl_str == 0 && bbl_mtr == 0)
                        {
                            int len_long_table1 = 0;
                            while (len_long_table1 < LEN_LONG_TABLE && fgets(string, LEN_STRING, long_file) != NULL)
                            {
                                fill_struct(&long_table1[len_long_table1], string);
                                len_long_table1++;
                            }
                            if (matrix1 == NULL)
                            {
                                matrix1 = allocate_matrix(len_long_table1);
                                copy_str_to_matrix(matrix1, long_table1, len_long_table1);
                            }
                            ins_str = insert_sort_str(long_table1, len_long_table1);
	                        ins_mtr = insert_sort_mtr(matrix1, len_long_table1);
                        	printf("Время на сортировку таблицы методом простых включений = %llu\n", ins_str);
                        	printf("Время на сортировку таблицы ключей методом простых включений = %llu\n", ins_mtr);
                        	//printf("Разница на сортировках = %llu%%\n", ins_str / ins_mtr);

                            int len_long_table2 = 0;
                            rewind(long_file);
                            while (len_long_table2 < LEN_LONG_TABLE && fgets(string, LEN_STRING, long_file) != NULL)
                            {
                                fill_struct(&long_table2[len_long_table2], string);
                                len_long_table2++;
                            }
                            if (matrix2 == NULL)
                            {
                                matrix2 = allocate_matrix(len_long_table2);
                                copy_str_to_matrix(matrix2, long_table2, len_long_table2);
                            }
                            bbl_mtr = bubble_sort_mtr(matrix2, len_long_table2);
                            bbl_str = bubble_sort_str(long_table2, len_long_table2);
                            /*
                            for (int i = 0; i < 100; i++)
                            {
                            	tmp = bubble_sort_str(long_table2, len_long_table2);
	                            if (tmp > bbl_str)
	                            	bbl_str = tmp;
	                            tmp = bubble_sort_mtr(matrix2, len_long_table2);
	                            if (tmp < bbl_mtr)
	                           		bbl_mtr = tmp;
	                        }
	                        */
                            printf("Время на сортировку таблицы методом простого обмена = %llu\n", bbl_str);
                            printf("Время на сортировку таблицы ключей методом простого обмена = %llu\n", bbl_mtr);
                            //printf("Экономия времени = %llu%%\n", (bbl_str / bbl_mtr));
                        }
                        //else
                        //{
                          //  printf("Время на сортировку таблицы методом простых включений = %llu\n", ins_str);
                           // printf("Время на сортировку таблицы ключей методом простых включений = %llu\n", ins_mtr);
                            //printf("Время на сортировку таблицы методом простого обмена = %llu\n", bbl_str);
                            //printf("Время на сортировку таблицы ключей методом простого обмена = %llu\n", bbl_mtr);
                            //printf("Экономия времени = %llu\n", (ins_str - ins_mtr) / 100);
                        //}
                    }
                    else if (choise == 0)
                    {
                        save_struct(table, len_table, out_file);
                        fclose(in_file);
                        fclose(out_file);
                        if (matrix != NULL)
                            free_matrix(matrix, len_table);
                        printf("Завершение программы\n");
                    }
                    else
                        printf("Нет такой опции\n");
                }
            else
            {
                printf("Невозможно считать таблицу\n");
                rn = CANT_READ_TABLE;
            }
        }
        else
        {
            rn = CANT_OPEN_FILE;
            printf("Невозможно открыть файлы\n");
        }
    }
    else
    {
        rn = MORE_ARGUMENTS;
        printf("Недостаточно аргументов\n");
    }

    return rn;
}
