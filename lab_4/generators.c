#include "generators.h"

// Время первого аппарата
double oa1(void)
{
	double result;

	result = (double)(rand())/ RAND_MAX*(MAX_TIME_OA1 - MIN_TIME_OA1) + MIN_TIME_OA1;

	return result;
}

// Время второго аппарата
double oa2(void)
{
    double result;

    result = (double)(rand())/ RAND_MAX*(MAX_TIME_OA2 - MIN_TIME_OA2) + MIN_TIME_OA2;

    return result;
}

// Вероятности
int generator(void)
{
    double result;

    result = (int)(0 + (rand()) % TRUE);

    return result;
}