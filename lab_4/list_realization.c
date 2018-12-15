#include "list_realization.h"
#include "generators.h"
#include "main.h"

// Проверка перевыделения адреса
void check(free_list *p)
{
    list *tmp;  // Переменная для запоминания позиции
    free_list *pa;  // Переменная для запоминания позиции

    while (p)
    {
        tmp = p -> address;
        p = p -> next;
        pa = p;
        while (pa)
        {
            if (pa -> address == tmp)
                pa -> address = 0;
            pa = pa -> next;
        }
    }
}

// Функция вывода списка
void print_list(list *pout)
{
    if (pout)
    {
        printf("Очередь:  ");
        while (pout != NULL)
        {
            printf("%d  ", pout->number);
            pout = pout->next;
        }
    }
    else
        printf("Пустая очередь\n");
    printf("\n");
}

// Функция вывода списка освобожденных областей
void print_free_list(free_list *p)
{
	free_list *tmp;  // Переменная для запоминания позиции
    int count = 0;  // Номер позиции в списке

    check(p);
    if (p)
    {
        printf("Освобожденные области:\n");
        while (p)
        {
            if (p -> address)
            {
                printf("%3d. %12p   ", count, p->address);
                count += 1;
                if (count % 5 == 0)
                    printf("\n");
            }
            tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    else
        printf("Пустая очередь\n");
    printf("\n");
}

// Функция добавления элемента в массив
void add_element_to_list(list **pout, list **pin, int num, double time)
{
    list *tmp = (list *)malloc(sizeof(list));  // Переменная для проверки успешности выделения памяти

    if (tmp)
    {
        tmp -> number = num;
        tmp -> time = time;
        tmp -> next = NULL;
    }
    if (*pin != NULL)
        (*pin) -> next = tmp;
    *pin = tmp;
    if (*pout == NULL)
        *pout = tmp;
}

// Функция удаления элемнета из массива
void delete_element(list **pout, list **pin)
{
    list *tmp;  // Переменная для запоминания позиции

    tmp = *pout;
    *pout = (*pout) -> next;
    if (*pout == NULL)
        *pin = NULL;
    free(tmp);
}

// Функция добавления адреса в массив освобожденных областей
void add_to_free(free_list **p, list *pout)
{
	free_list *tmp = (free_list *)malloc(sizeof(free_list)); // Переменная для проверки успешности выделения памяти

	if (tmp)
	{
		tmp -> address = pout;
		tmp -> next = *p;
	}

	*p = tmp;
}

// Функция освобождения памяти под список
void free_l(list *pout)
{
    list *tmp;  // Переменная для запоминания позиции

    while (pout)
    {
        tmp = pout;
        pout = pout -> next;
        free(tmp);
    }
}

int main_list(void)
{
    int rn = OK;  // Код возврата

    list *pout1 = NULL;  // Указатель на голову первой очереди
    list *pin1 = NULL;  // Указатель на хвост первой очереди
    list *pout2 = NULL;  // Указатель на голову второй очереди
    list *pin2 = NULL;  // Указатель на хвост второй очереди
    free_list *p = NULL;  // Указатель на список освобожденных областей

    int count_list2 = 0;  // Счетчик прохождения через второй аппарат
    double working_time = 0;  // Общее время работы
    double delta = 0, tmp;  // Переменные для сохранения времени работы аппаратов
    double working_time_oa1 = 0, working_time_oa2 = 0;  // Времена работы аппаратов
    int k = 0;  // Количество заявок первого типа
    int len_array2 = 0;  // Длина второй очереди
    double s = 0;

    for (int i = 0; i < LEN_ARRAY; i++)
        add_element_to_list(&pout1, &pin1, i, 0);

    unsigned long long time2, time1 = clock();

    while (count_list2 < 1000)
    {
        tmp = oa1();
        working_time += tmp;
        working_time_oa1 += tmp;
        if (pin2 != NULL)
        {
            if (delta > pout2 -> time || pin1 == pout1)
            {
                delta -= pout2 -> time;
                add_element_to_list(&pout1, &pin1, pout2->number, pout2->time);
                working_time += pout2->time;
                add_to_free(&p, pout2);
                delete_element(&pout2, &pin2);
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
        		printf("Переполнение списка\n");
        		break;
        	}
            tmp = oa2();
            add_element_to_list(&pout2, &pin2, pout1 -> number, tmp);
            delete_element(&pout1, &pin1);
            working_time_oa2 += tmp;
            count_list2 += 1;
            if (count_list2 % 100 == 0)
            {
            	printf("\n");
                printf("   Время простоя второго аппарата =         %lf\n", working_time_oa1 - working_time_oa2);
                s += working_time_oa1 - working_time_oa2;
                printf(" Количество срабатываний первого автомата = %d\n", k + 1);
        		printf("Среднее время пребывания в первой очереди = %lf\n", working_time_oa1 / 100);
                working_time_oa1 = 0;
                working_time_oa2 = 0;
            }
        }
        else
        {
            add_element_to_list(&pout1, &pin1, pout1 -> number, 0);
            delete_element(&pout1, &pin1);
        }
        k += 1;
    }
    time2 = clock();
    printf("\n");
    printf("Время выполнения = %llu\n", time2 - time1);
    printf("Время простоя второго аппарата = %lf\n", s);
    printf("Время моделирования = %lf\n", working_time);
    printf("Среднее время пребывания в первой очереди   %lf\n", working_time / (k + count_list2));
    printf("Вывести области памяти?(1 - Да/ 0 - Нет)\n");
    fscanf(stdin, "%d", &k);
    if (k == 1)
    	print_free_list(p);
    free_l(pout1);
    free_l(pout2);

    return rn;
}
