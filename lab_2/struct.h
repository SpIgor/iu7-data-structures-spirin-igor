#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include "main.h"

struct line
{
    char marka[LEN_MARKA + 1];  // Поле, для хранения марки автомобиля
    char country[LEN_COUNTRY + 1];  // для страны производителя
    int cost;  // для стоимости автомобиля
    char colour[LEN_COLOUR + 1];  // для цвета автомобиля
    int flag; // "Логическая" переменная для количества не вариатных полей
    union
    {
        int year_n;  // лет гарантии
        struct
        {
            int year_o;  // года выпуска
            int probeg;  // пробега
            int count;  // стоимости
        };
    };
} table[LEN_TABLE], long_table1[LEN_LONG_TABLE], long_table2[LEN_LONG_TABLE];
// Основная таблица, таблица на 1000 строк для пузырька, таблица на 1000 строк для вставок

#endif 
