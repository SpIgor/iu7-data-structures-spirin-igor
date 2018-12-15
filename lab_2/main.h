#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#define OK 0  // При корректной работе
#define MORE_ARGUMENTS -1  // При неверном количестве аргументов при запуске программы
#define CANT_OPEN_FILE -2  // При невозможности открытия файлов
#define CANT_READ_TABLE -3  // При неверном формате файлов
#define OVERFLOW -4  // При переполнении поля записи
#define WRONG_POSITION -5  // При неверном символе в поле записи
#define TOO_MANY_POSITIONS -6  // При превышении количества полей
#define LEN_COUNTRY 3  // Длина поля структуры для записи страны
#define LEN_MARKA 16  // Длина поля структуры для записи марки
#define LEN_COLOUR 10  // Длина поля структуры для записи цвета
#define LEN_STRING 100  // Длина входящей строки
#define LEN_TABLE 100  // Количество элементов таблицы
#define LEN_LONG_TABLE 1000  // Количество элементов таблицы для замера времени при сортировках

#endif