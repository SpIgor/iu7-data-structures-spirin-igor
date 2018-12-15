#include "string_operations.h"
#include "struct.h"

// Функция определения количества полей в строке
int count_positions(char *string, int len_string)
{
    int count = 0;  // Количество полей

    for (int i = 0; i < len_string; i++)
        if (string[i] == ';')
            count++;
    
    return count;
}

// Функция определения длины строки
int len(char *string)
{
    int i = 0;  // Длина строки

    while (string[i] != '\n' && string[i] != '\0' && i < LEN_STRING)
        i++;

    return i;
}