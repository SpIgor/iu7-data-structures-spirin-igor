#include "array_operations.h"
#include "main.h"
#include "time.h"

void print_array(int *pa, int *pb)
{
    printf("Массив: ");
    while (pa < pb)
    {
        printf("%d ", *pa);
        pa += 1;
    }
    printf("\n");
}

// Функция добавления элемента в массив
int add_element(int **ps, int *pb, int element, unsigned long long *time)
{
    int rn = OK;  // Код возврата
    unsigned long long time1 = tick(), time2;  // Переменные для замера времени


    if (*ps < pb - 1)
    {
       *ps += 1;
       **ps = element;
    }
    else
        rn = OVERFLOW;

    time2 = tick();
    *time = time2 - time1;
    return rn;
}

// Функция удаления элемента массива
int delete_element(int **ps, int *pa, unsigned long long *time)
{
    int rn = OK;  // Код возврата
    unsigned long long time1 = tick(), time2;  // Переменные для замера времени

    if (*ps >= pa)
    {
       **ps = 0;
       *ps -= 1;
    }
    else
        rn = EMPTY_ARRAY;

    time2 = tick();
    *time = time2 - time1;

    return rn;
}

// Функция поиска и вывода убывающих последовательностей
unsigned long long print_sequences(int *pa, int *pb, int *ps)
{
    int len_array = pb - pa;  // Длина списка и массива последовательности
    int array[len_array];  // Массив для последовательности
    int count = 0;   // Текущая длина массива 
    int time1 = tick(), time2;  // Переменные для замера времени выполнения функции

    array[count] = *ps;
    count += 1;
    ps--;
    printf("    Последовательности: ");
    while (ps >= pa)
    {
        if (*ps <= array[count - 1])
        {
            for (int i = count - 1; i > -1; i--)
            {
                printf("%d", array[i]);
                array[i] = 0;
            }
            count = 0;
            printf("  ");
            array[count] = *ps;
            count += 1;
        }
        else
        {
            array[count] = *ps;
            count += 1;
        }
        ps--;
    }
    if (count != 0)
        for (int i = count - 1; i > -1; i--)
        {
            printf("%d", array[i]);
            array[i] = 0;
        }

    time2 = tick();

    return time2 - time1;
}
