#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define LEN_STRING 100  // Длина вводимой строки
#define OK 0  // Код возврата при корректной работе программы
#define CANT_ALLOCATE -1  // Код возврата при невозмодности выделения памяти
#define WRONG_FORMAT -2  // Код возврата при неверном формате вводимых значений
#define CANT_OPEN_FILE -3  // Код возврата при невозможности открытия файлов

typedef struct tree_node tree_t;
typedef struct data data_t;

// Атрибуты файлов
struct data
{
    char *name;  // Имя файла
    int *date;  // Дата последнего открытия
};

// Вергина дерева
struct tree_node
{
    data_t *data;  // Атрибуты файла
    struct tree_node *left;  // Указатель на левого потомка
    struct tree_node *right;  // Указатель на правого потомка
};

#endif