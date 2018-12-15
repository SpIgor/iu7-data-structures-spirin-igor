#include "struct_operations.h"
#include "string_operations.h"
#include "struct.h"

// Функция печати таблицы
void print_table(struct line *table, int len_p)
{
    printf("|-----|----------------|------|-----------|---------------|-----|------------|-------|\n");
    for (int i = 0; i < len_p; i++)
    {
        printf("|%5d|", i + 1);
        printf("%16s|", table[i].marka);
        printf("%6s|", table[i].country);
        printf("%11d|", table[i].cost);
        printf("%15s|", table[i].colour);
        if (table[i].flag == 1)
        {
            printf("%5d|", table[i].year_o);
            printf("%12d|", table[i].probeg);
            printf("%7d|", table[i].count);
        }
        else
            printf("%5d|", table[i].year_n);
        printf("\n");
    }
    printf("|-----|----------------|------|-----------|---------------|-----|------------|-------|\n");
    printf("\n");
}

// Функция выделения подстроки
int fill_char_position(char *pole, int len_pole, char *position, char *string)
{
    int i = 0;  // Новая позиция начала строки

    if (position != NULL && (position - string) <= len_pole && (position - string) != 0)
    {
        while (string < position)
        {
            pole[i] = *string;
            i++;
            string++;
        }
        string++;
    }

    return i + 1;
}
 
 // Функция выделения целого из строки
int fill_int_position(int *pole, char *position, char *string)
{
    int result = 0;  // Накапливаемое число
    int count = 0;  // Код возврата

    if (position != NULL && (position - string) > 0)
    {
        while ((string < position) && (isdigit(*string) != 0))
        {
            result *= 10;
            result += *string - '0';
            string++;
            count += 1;
        }
        *pole = result;
    }

    return count + 1;
}

// Функция удаления строки таблицы
void delete_struct_line(struct line *p, int *len_table, int position)
{
    for (int i = position; i < *len_table; i++)
        p[i] = p[i + 1];
    *len_table -= 1;
}

// Функция заполнения записи
int fill_struct(struct line *p, char *string)
{
    int rn = OK;  // Код возврата
    char *position;  // Указатель на начало строки
    int status = 0;  // Код возврата вызываемых подпрограмм
    int num_positions = count_positions(string, len(string));  // Количество разделителей в строке

    if (num_positions == 5 || num_positions == 7)
    {
        position = strchr(string, ';');
        status = fill_char_position(p->marka, LEN_MARKA, position, string);
        if (status == 1)
            rn = WRONG_POSITION;
        else
            string += status;

        position = strchr(string, ';');
        status = fill_char_position(p->country, LEN_COUNTRY, position, string);
        if (status == 1)
            rn = WRONG_POSITION;
        else
            string += status;

        position = strchr(string, ';');
        status = fill_int_position(&(p->cost), position, string);
        if (status == 1)
            rn = WRONG_POSITION;
        else
            string += status;

        position = strchr(string, ';');
        status = fill_char_position(p->colour, LEN_COLOUR, position, string);
        if (status == 1)
            rn = WRONG_POSITION;
        else
            string += status;
        if (num_positions == 5 && rn == OK)
        {
            p->flag = 0;
            position = strchr(string, ';');
            status = fill_int_position(&p->year_n, position, string);
            if (status == 1)
                rn = WRONG_POSITION;
            else
                string += status;
        }
        else
        {
            p->flag = 1;

            position = strchr(string, ';');
            status = fill_int_position(&p->year_o, position, string);
            if (status == 1)
                rn = WRONG_POSITION;
            else
                string += status;

            position = strchr(string, ';');
            status = fill_int_position(&p->probeg, position, string);
            if (status == 1)
                rn = WRONG_POSITION;
            else
                string += status;

            position = strchr(string, ';');
            status = fill_int_position(&p->count, position, string);
            if (status == 1)
                rn = WRONG_POSITION;
            else
                string += status;
        }
    }
    else
        rn = TOO_MANY_POSITIONS;
    return rn;
}

// Функция записи таблицы в файл
void save_struct(struct line *p, int len_table, FILE* out_file)
{
    for (int i = 0; i < len_table; i++)
    {
        fprintf(out_file, "%s;", p[i].marka);
        fprintf(out_file, "%s;", p[i].country);
        fprintf(out_file, "%d;", p[i].cost);
        fprintf(out_file, "%s;", p[i].colour);
        if (p[i].flag == 0)
            fprintf(out_file, "%d;", p[i].year_o);
        else
        {
            fprintf(out_file, "%d;", p[i].year_n);
            fprintf(out_file, "%d;", p[i].probeg);
            fprintf(out_file, "%d;", p[i].count);
        }
        if (i != len_table - 1)
            fprintf(out_file, "\n");
    }
}
