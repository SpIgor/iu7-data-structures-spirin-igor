#include "main.h"
#include "array_realization.h"
#include "generators.h"

// Вывод массива
void print_array(element *pout, element *pin, int num)
{
    printf("Массив%d:   ", num);
    for (int i = 0; i < pin - pout; ++i)
        printf("%d ", pout[i].number);
    printf("\n");
}

// Сдвиг всех элементов массива на 1 влево
void move_elements_left(element *pout, element *pin)
{
    for (int i = 0; i < pin - pout - 1; i++)
    {
        pout[i].time = pout[i + 1].time;
        pout[i].number = pout[i + 1].number;
    }
}

// Функция отправки элемента в конец массива
void restart(element *pout, element *pin)
{
    int num = pout->number;
    move_elements_left(pout, pin);
    (pin - 1)->number = num;
}

int main_array(void)
{
    int rn = OK;  // Код возврата

    element array1[LEN_ARRAY];  // Массив для первой очереди
    element array2[LEN_ARRAY];  // Массив для второй очереди
    element *pout1 = array1;  // Указатель на начало массива
    element *pin1 = array1 + LEN_ARRAY;  // Указатель на конец массива
    element *pout2 = array2;  // Указатель на начало массива
    element *pin2 = array2;  // Указатель на конец массива

    int count_list2 = 0;  // Счетчик прохождения через второй аппарат
    double working_time = 0;  // Общее время работы
    double delta = 0, tmp;  // Переменные для сохранения времени работы аппаратов
    double working_time_oa1 = 0, working_time_oa2 = 0;  // Времена работы аппаратов
    int k = 0;  // Счетчик заявок первого типа
    int len_array2 = 0;  // Длина второй очереди
    double s = 0;

    srand(time(NULL));

    for (int i = 0; i < LEN_ARRAY; ++i)
        array1[i].number = i;

    unsigned long long time2, time1 = clock();

    while (count_list2 != 1000)
    {
        tmp = oa1();
        working_time += tmp;
        working_time_oa1 += tmp;
        if (pin2 != pout2)
        {
            if (delta > pout2 -> time || pin1 == pout1)
            {
                delta -= pout2 -> time;
                pin1->number = pout2->number;
                working_time += pout2->time;
                pin1 += 1;
                move_elements_left(pout2, pin2);
                pin2 -= 1;
                len_array2 -= 1;
            }
            else
                delta += tmp;
        }
        if (generator() >= PROBABILITY)
        {
            len_array2 += 1;
            if (len_array2 > 100)
            {
                printf("Переполнение массива\n");
                break;
            }
            pin2->number = pout1->number;
            tmp = oa2();
            pin2->time = tmp;
            working_time_oa2 += tmp;
            pin2 += 1;
            move_elements_left(pout1, pin1);
            pin1 -= 1;
            count_list2 += 1;
            if (count_list2 % 100 == 0)
            {
                printf("\n");
                printf("Время простоя второго аппарата              %lf\n", working_time_oa1 - working_time_oa2);
                s += working_time_oa1 - working_time_oa2;
                printf("Количество срабатываний первого автомата    %d\n", k + 1);
                
                working_time_oa1 = 0;
                working_time_oa2 = 0;
            }
        }
        else
        {
            restart(pout1, pin1);
        }
        k += 1;
    }
    time2 = clock();
    printf("\n");
    printf("Время выполнения = %llu\n", time2 - time1);
    printf("Время простоя второго аппарата = %lf\n", s);
    printf("Время моделирования = %lf\n", working_time);
    printf("Среднее время пребывания в первой очереди   %lf\n", working_time / (k + count_list2));

    return rn;
}
