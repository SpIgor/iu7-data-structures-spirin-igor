#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "define_file.h"
#include "input_output.h"
#include <time.h>

// ДВОИЧНОЕ ДЕРЕВО ПОИСКА

T_t* add_tree(T_t *root, T_t *add_word);  // добавление слова в дерево

void remove_word(T_t **root,char* search);  // удаление слова из дерева

T_t* search_word(T_t *root, char* search, int *cmp);  // поиск узлов

// СБАЛАНСИРОВАННОЕ ДЕРЕВО

balance_t* add_balance_tree(balance_t* root, char* value);  // добавление элемента в сбалансированное дерево

balance_t* remove_balance(balance_t* root, char *key, int *del);  // удаление элемента из сбалансированного дерева

balance_t* search_balance(balance_t* root, char *key, int *cmp);  // поиск слова в сбалансированном дереве

// ХЭШ-ТАБЛИЦА

int hash_function(char *word, int num);  // индекс

void insert_close(Close_t *close_table, char *string, double *coef, int size);  // закрытое хэширование
void insert_open(Open_t *open_table, char *string,  double *coef, int size);  // открытое хэширование

int search_close(Close_t *close, char *search, int *cmp, int size);  // поиск в тбалице с закрытым хэшированием
int search_open(Open_t *open, char *search, int *cmp, int size);  // поиск в таблице с открытым хэшированием

Close_t* restruct_close(Close_t* close, double *coef, int *size);  // реструкторизация таблицы с закрытым хэшированием
Open_t* restruct_open(Open_t* open, double *coef, int *size);  // реструкторизация таблицы с открытым хэшированием

void remove_close(Close_t *close_table, char *search, int size, double *coef);  // удаление элемента из таблицы с закрытым хэшированием
void remove_open(Open_t *open_table, char *search,int size,double *coef);  // удаление элемента из таблицы с открытым хэшированием

void time_it();  // замер времени выполнения

#endif