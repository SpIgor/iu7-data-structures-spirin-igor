#ifndef LIST_REALIZATION_H
#define LIST_REALIZATION_H

#include <time.h>

// Списки элементов очередей
typedef struct list
{
    int number;  // Номер
    double time;  // Время во втором аппарате
    struct list *next;  // Указатель на следующий элемент списка
} list;

// Список освобожденных областей
typedef struct free_list
{
    list *address;  // Адрес ячейки памяти
    struct free_list *next;  // Указатель на следующий элемент списка
} free_list;

typedef struct fragmentation_list
{
	list *address;
	int count_allocate;
	int count_free;
	struct fragmentation_list *next;
} fr_list;


void check(free_list *p);

void print_list(list *pout);

void print_free_list(free_list *p);

void add_element_to_list(list **pout, list **pin, int num, double time);

void delete_element(list **pout, list **pin);

void add_to_free(free_list **p, list *pout);

void free_l(list *pout);

int main_list(void);

#endif
