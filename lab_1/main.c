#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define OK 0
#define LEN_MANTISSA 30
#define LEN_STPEN 5
#define LEN_STRING 40
#define WRONG_NUMBER -2
#define NO_MANTISSA -3
#define TOO_LONG_STEP -4
#define E_NOT_FOUND -5
#define WRONG_ELEMENT -6

void print_array(int *array, int len_array)
{
    for (int i = 0; i < len_array; i++)
        printf("%d  ", array[i]);
    printf("\n");
}

/*
 * Возвращает
 * 1 array_1 > array_2
 * 0 array_1 == array_2
 * -1 array_1 < array_2
*/
int compare_array(int *array_1, int len_array_1, int *array_2, int len_array_2)
{
    if (len_array_1 - len_array_2 != 0)
        return len_array_1 - len_array_2;
    else
        for (int i = 0; i < len_array_1; i++)
            if (array_1[i] != array_2[i])
                return array_1[i] - array_2[i];
    return 0;
}

/*
 * На вход два массива
 * array_1 - увеличиваемый массив
 * array_2 - прибавляется к массиву array_1 столбиком
 * длина array_1 может быть максимум на 1 больше, чем длина array_2
*/
int *increas_array(int *array_1, int len_array_1, int *array_2, int len_array_2)
{
    int diff = len_array_1 - len_array_2;
    int spare = 0;
    int result = 0;

    for (int i = len_array_2 - 1; i >= 0; i--)
    {
        result = array_1[diff + i] + array_2[i] + spare;
        spare = 0;
        if (result > 9)
        {
            array_1[diff + i] = result % 10;
            spare = result / 10;
        }
        else
            array_1[diff + i] = result;
    }
    array_1[0] += spare;
    if (diff == 0 && spare != 0)
        array_1[0] = result;

    return array_1;
}

/*
 * Входные данные
 * array_1 - уменьшаемое
 * array_2 - вычетаемое
 * -1 < len_array_1 - len_array_2 < 2
*/
void umenshit(int *array_1, int len_array_1, int *array_2, int len_array_2)
{
    int diff = len_array_1 - len_array_2;

    for (int i = len_array_2 - 1; i > -1; i--)
    {
        array_1[i + diff] -= array_2[i];
        if (array_1[i + diff] < 0)
        {
            array_1[i + diff] += 10;
            array_1[i - 1 + diff]--;
        }
    }
}

/*
 * Входные данные
 * array_1 - массив из которого надо максимальное колияество раз вычесть array_2
 * len_array_1  максимум на 1 больше чем len_array_2
 * или равна ему
*/
int vichest(int *array_1, int len_array_1, int *array_2, int len_array_2)
{
    int array_3[len_array_1];
    int len_array_3 = len_array_1;
    int diff = len_array_1 - len_array_2;
    int count = 1;

    for (int i = 0; i < len_array_3; i++)
        array_3[i] = 0;

    for (int i = len_array_2 -1; i >= 0; i--)
        array_3[diff + i] = array_2[i];

    while (compare_array(array_1, len_array_1, increas_array(array_3, len_array_3, array_2, len_array_2), len_array_3) >= 0)
        count++;
    umenshit(array_3, len_array_3, array_2, len_array_2);
    umenshit(array_1, len_array_1, array_3, len_array_3);

    return count;
}

void move_left(int *array)
{
    for (int i = 0; i < LEN_MANTISSA - 1; i++)
        array[i] = array[i + 1];
}

int void_array(int *array)
{
    for (int i = 0; i < LEN_MANTISSA; i++)
        if (array[i] != 0)
            return 1;
    return 0;
}

int start_division(int *array_1, int len_array_1, int *array_2, int len_array_2, int *result, int *len_result)
{
    int tmp_len;
    int count = 0;
    int flag = 0;

    while (len_array_1 > 0 && *len_result < LEN_MANTISSA)
    {
        tmp_len = 0;
        while (compare_array(array_1, tmp_len, array_2, len_array_2) < 0)
            tmp_len++;
        if (tmp_len > len_array_1)
        {
            //len_array_1 += 1;
            //count += 1;
            count += tmp_len - len_array_1;
            len_array_1 = tmp_len;

        }
        result[*len_result] = vichest(array_1, tmp_len, array_2, len_array_2);
        *len_result += 1;
        while (array_1[0] == 0 && tmp_len > 0)
        {
            move_left(array_1);
            tmp_len -= 1;
            len_array_1 -= 1;
            if (flag == 1 && len_array_1 != 0)
            {
                result[*len_result] = 0;
                *len_result += 1;
            }
            flag = 1;
        }
        flag = 0;
    }

    return count;
}

int read_number(char *input_number, int *mantissa, int *stepen, int *znak_mantissa, int *znak_stepen, int *count_fraction, int *len_mantissa, int *len_stepen)
{
    int start_mantissa = 0;
    int start_stepen = -1;
    int count_stepen = 0;
    int count_mantissa = 0;

    switch(input_number[0])
    {
        case('-') : *znak_mantissa = 0;

        case('+') : start_mantissa = 1;
                    break;
    }

    if (input_number[start_mantissa] == 'E')
    {
            printf("Отсутствует мантисса\n");
            return NO_MANTISSA;
    }

    for (int i = 1;i < LEN_STRING; i++)
        if (input_number[i] == 'E')
            start_stepen = i+1;

    switch(input_number[start_stepen])
    {
        case('\n'): printf("Нет степени\n");
                    return WRONG_ELEMENT;
                    break;
        case('-') : *znak_stepen = 0;

        case('+') : start_stepen++;
                    break;
    }
    if (start_stepen == -1)
    {
        printf("Нет E\n");
        return E_NOT_FOUND;
    }


    for (int i = start_mantissa; i < start_stepen - 2 + *znak_stepen; i++)
    {
        if (isdigit(input_number[i]))
        {
            count_mantissa++;
            if (count_mantissa > 30)
            {
                printf("Переполнение мантиссы\n");
                return WRONG_NUMBER;
            }

            mantissa[*len_mantissa] = input_number[i] - '0';
            *len_mantissa += 1;

            if (*count_fraction >= 0)
                *count_fraction += 1;
        }
        else if (input_number[i] == '.' && *count_fraction == -1)
            *count_fraction = 0;
        else if (input_number[i] == '.' && *count_fraction == 0)
        {
            printf("Wrong element in mantissa\n");
            return WRONG_ELEMENT;
        }
        else
        {
            printf("Посторонний элемент в мантиссе: %c\n", input_number[i]);
            return WRONG_NUMBER;
        }
    }
    *count_fraction = 0;

    for (int i = start_stepen; i < LEN_STRING; i++)
    {
        if (input_number[i] == '\n')
            return OK;
        if (isdigit(input_number[i]))
        {
            count_stepen++;
            if (count_stepen > 5)
            {
                printf("Переполнение степени\n");
                return WRONG_NUMBER;
            }

            stepen[*len_stepen] = input_number[i] - '0';
            *len_stepen += 1;
        }
        else
        {
            printf("Посторонний элемент в степени: %c\n", input_number[i]);
            return WRONG_ELEMENT;
        }
    }

    return OK;
}

void transform_mantissa(int *mantissa, int *len_mantissa)
{
    while (mantissa[0] == 0)
    {
        move_left(mantissa);
        *len_mantissa -= 1;
        if (*len_mantissa == 0)
            break;
    }
}

int print_result(int *result, int len_result, int count_fraction_1, int count_fraction_2, int count, int *stepen_1, int len_stepen_1, int znak_stepen_1, int *stepen_2, int len_stepen_2, int znak_stepen_2, int znak_1, int znak_2)
{
    int st_1 = 0;
    int st_2 = 0;
    int result_st = 0;

    for (int i = 0; i < len_stepen_1; i++)
    {
        st_1 *= 10;
        st_1 += stepen_1[i];
    }
    if (znak_stepen_1 == 0)
        st_1 *= -1;

    for (int i = 0; i < len_stepen_2; i++)
    {
        st_2 *= 10;
        st_2 += stepen_2[i];
    }
    if (znak_stepen_2 == 0)
        st_2 *= -1;


    result_st = st_1 - st_2;
    result_st -= count_fraction_1;
    result_st += count_fraction_2;
    //result_st += count - 1;
    if (result[len_result - 1] == 0)
        len_result--;
    printf("count = %d\n", count);
    printf("Len_resukt = %d\n", len_result);
    print_array(result, len_result);
    //result_st += len_result;
    if (result_st <= 99999 && result_st >= -99999)
    {
        printf("Result = ");
        if (znak_1 != znak_2)
            printf("-");
        printf("0.");
        for (int i = 0; i < len_result; i++)
            printf("%d", result[i]);
        printf("E");
        printf("%d\n", result_st);
    }
    else
    {
        printf("Переполнение порядка\n");
        return TOO_LONG_STEP;
    }

    return OK;
}

int main(void)
{
    int mantissa_1[LEN_MANTISSA], mantissa_2[LEN_MANTISSA];  // mantissa_1 содержит мантиссу первого числа, mantissa_2 мантиссу второго числа
    int stepen_1[LEN_STPEN], stepen_2[LEN_STPEN];  // stepen_1 содержит порядок первого числа, stepen_2 порядок вторго числа
    int znak_stepen_1 = 1, znak_stepen_2 = 1;  // s1 знак порядка первого числа, s2 знак порядка второго числа
    int znak_mantissa_1 = 1, znak_mantissa_2 = 1;  // m1 знак мантиссы первого числа, m2 знак мантиссы второго числа
    int count_fraction_1 = -1, count_fraction_2 = -1;  // Количество чисел после запятой
    char inputStr[LEN_STRING];  // Входящая строка
    int len_mantissa_1 = 0, len_mantissa_2 = 0;  // Длина строки
    int len_stepen_1 = 0, len_stepen_2 = 0;  // Длины степеней
    int result[LEN_MANTISSA];  // Массив-результат
    int len_result = 0;  // Длина результата
    int count = 0;  // Сдвиг степени при делении

    for (int i = 0; i < LEN_MANTISSA; i++)
    {
        mantissa_2[i] = 0;
        mantissa_1[i] = 0;
    }
    for (int i = 0; i < LEN_STPEN; i++)
    {
        stepen_1[i] = 0;
        stepen_2[i] = 0;
    }

    printf("Введите первое число\n");
    printf("--------------------------------E------\n");
    fgets(inputStr, LEN_STRING, stdin);
    if (read_number(inputStr, mantissa_1, stepen_1, &znak_mantissa_1, &znak_stepen_1, &count_fraction_1, &len_mantissa_1, &len_stepen_1) == 0)
    {
        printf("Введите второе число\n");
        printf("--------------------------------E------\n");
        fgets(inputStr, LEN_STRING, stdin);
        if (read_number(inputStr, mantissa_2, stepen_2, &znak_mantissa_2, &znak_stepen_2, &count_fraction_2, &len_mantissa_2, &len_stepen_2) == 0)
        {
            transform_mantissa(mantissa_1, &len_mantissa_1);
            transform_mantissa(mantissa_2, &len_mantissa_2);
            if (len_mantissa_1 == 0)
                printf("0\n");
            else if (len_mantissa_2 >= 1 && len_mantissa_1 >= 1)
            {
                count = start_division(mantissa_1, len_mantissa_1, mantissa_2, len_mantissa_2, result, &len_result);
                print_result(result, len_result, count_fraction_1, count_fraction_2, count, stepen_1, len_stepen_1, znak_stepen_1, stepen_2, len_stepen_2, znak_stepen_2, znak_mantissa_1, znak_mantissa_2);
            }
            else
                printf("Не могу вычислить\n");
        }
    }

    return 0;
}