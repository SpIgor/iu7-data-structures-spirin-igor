#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#define CANT_ALLOCATE -6  // Код возврата при не выделении памяти

// Структура для хранения элементов последовательности
typedef struct list_element
{
    int element;  // Введенное значение
    struct list_element *address;  // Адрес области памяти
    struct list_element *next;  // Указатель на следующий элемент списка
} list_element;

// Структура для хранения освобожденных областей
typedef struct free_list_element
{
    list_element *address;  // Адрес освобожденной области памяти
    struct free_list_element *next;  // Указатель на следующий элемент списка
} free_list_element;

int add_element_to_list(list_element **head, free_list_element **head_free, int element, unsigned long long *time);

void print_list(list_element *head);

int delete_element_from_list(list_element **head, free_list_element **head_free, unsigned long long *time);

void print_free_list(free_list_element *head_free);

unsigned long long print_sequences_in_list(list_element *head);

void check_address(list_element *tmp, free_list_element **head_free);

#endif
