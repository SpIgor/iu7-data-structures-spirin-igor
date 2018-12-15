#ifndef ARRAY_REALIZATION_H
#define ARRAY_REALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OVERFLOW_ARRAY -1
#define EMPTY_ARRAY -2

typedef struct element_of_array
{
    double time;  // Для сохранения времени обработки во второй очереди
    int number;  // Сохранение номера
} element;

int main_array(void);

void print_array(element *pout, element *pin, int num);

void move_elements_left(element *pout, element *pin);

void restart(element *pout, element *pin);

#endif
