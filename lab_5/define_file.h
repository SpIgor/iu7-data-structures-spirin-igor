#ifndef __DEFINE_FILE_H__
#define __DEFINE_FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 0
#define NOT_JOINED -1
#define CANNOT_OPEN -2
#define WRONG_INPUT -3
#define MEMORY_ERR -4
#define WRONG_MENU -5
#define MAX_NUMBER 1000


typedef struct ListMatrix matrix_t;
typedef struct ListIA list_t;


struct ListIA
{
    int index;
    list_t *next;
};

struct ListMatrix
{
    int *A;
    int *J;
    list_t *IA;
};



#endif

