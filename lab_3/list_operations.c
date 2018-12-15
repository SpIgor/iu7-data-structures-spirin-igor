#include "list_operations.h"
#include "main.h"
#include "time.h"

// Функция добавления элемента в список
int add_element_to_list(list_element **head, free_list_element **head_free, int element, unsigned long long *time)
{
    int rn = OK; // Код возврата
    list_element *tmp = (list_element *)malloc(sizeof(list_element));  // Указатель на новый элемент списка
    unsigned long long int time1 = tick(), time2;  // Переменные для замера времени

    if (tmp)
    {
        tmp -> element = element;
        tmp -> address = tmp;
        tmp -> next = *head;
        *head = tmp;
        check_address(tmp, head_free);
    }
    else
        rn = CANT_ALLOCATE;

    time2 = tick();
    *time = time2 - time1;

    return rn;
}

// Функция печати списка стека
void print_list(list_element *head)
{
    if (head == NULL)
        printf("Пустой список\n");
    else
    {
        printf("Адрес элемента|Значение\n");
        while (head != NULL)
        {
            printf("%14p|%8d\n", head -> address, head -> element);
            head = head -> next;
        }
    }
    printf("\n");
}

// Функция печати списка освобожденных областей
void print_free_list(free_list_element *head_free)
{
    if (head_free == NULL)
        printf("Нет свободных областей\n");
    else
    {
        printf("Адреса освобожденных областей\n");
        while (head_free != NULL)
        {
            printf("%12p\n", head_free -> address);
            head_free = head_free -> next;
        }
    }
    printf("\n");
}

// Функция удаления элемента списка и добаления его в список освобожденных
int delete_element_from_list(list_element **head, free_list_element **head_free, unsigned long long *time)
{
    int rn = OK;  // Код возврата
    free_list_element *tmp = (free_list_element *)malloc(sizeof(free_list_element));  // Указатель на новый элемент списка освобожденных областей
    list_element *tmp_h;  // Указатель на удаляемый элемент списка стека
    int time1 = tick(), time2;  // Переменные для замера времени

    if (tmp)
    {
        tmp -> address = *head;
        tmp -> next = *head_free;
        *head_free = tmp;
        tmp_h = *head;
        *head = (*head) -> next;
        free(tmp_h);
    }
    else
        rn = CANT_ALLOCATE;
    
    time2 = tick();
    *time = time2 - time1;

    return rn;
}

// Вывод найденных последовательностей
unsigned long long print_sequences_in_list(list_element *head)
{
    int len = 0;  // Длина списка и массива последовательности
    list_element *last = head;  // Дублирование указателя на начало списка для определения его длины
    int array[len];  // Массив для последовательности
    int count = 0;  // Текущая длина массива 
    unsigned long long time1 = tick(), time2;  // Переменные для замера времени выполнения функции

    while (last != NULL)
    {
        last = last -> next;
        len += 1;
    }


    array[count] = head -> element;
    count += 1;
    head = head -> next;
    printf("    Последовательности: ");
    while (head != NULL)
    {
        if (head -> element <= array[count - 1])
        {
            for (int i = count - 1; i > -1; i--)
            {
                printf("%d", array[i]);
                array[i] = 0;
            }
            count = 0;
            printf("  ");
            array[count] = head -> element;
            count += 1;
        }
        else
        {
            array[count] = head -> element;
            count += 1;
        }
        head = head -> next;
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

void check_address(list_element *tmp, free_list_element **head_free)
{
    free_list_element *tmp_free;

    while (*head_free != NULL)
    {
        if (tmp -> address == (*head_free) -> address)
        {
            tmp_free = *head_free;
            *head_free = (*head_free) -> next;
            free(tmp_free);
        }
    }
}