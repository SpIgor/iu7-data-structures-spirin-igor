#ifndef __DEFINE_FILE_H__
#define __DEFINE_FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_STRING 500
#define MAX_NUM 200
#define OK 0
#define WRONG_SYMB -1
#define CANNOT_OPEN -2
#define WRONG_FORMAT -3
#define CANT_ALLOCATE -4
#define NO_INPUT -5

typedef struct Tree T_t;
typedef struct BalanceTree balance_t;
typedef struct HashClose Close_t;
typedef struct HashOpen Open_t;
typedef struct Open data_t;

struct Tree
{
    char word[LEN_STRING + 1];
    T_t *left;
    T_t *right;
};

struct BalanceTree
{
    char word[LEN_STRING + 1];
    int height;
    balance_t *left;
    balance_t *right;
};

struct HashClose
{
    int hash;
    int count;
    char word[LEN_STRING + 1];
};

struct Open
{
    char word[LEN_STRING + 1];
    int state;
    data_t *next;
};

struct HashOpen
{
    int hash;
    data_t *data;
};


#endif