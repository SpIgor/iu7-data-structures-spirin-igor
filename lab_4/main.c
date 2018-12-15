#include "main.h"
#include "array_realization.h"
#include "list_realization.h"

int main(void)
{
    int choise = 1;  //  Переменная для работы меню
    int rn = OK;  // Код возрата

    while (choise != 0)
    {
        printf("1 - работа программы на массиве\n");
        printf("2 - работа программы на списке\n");
        printf("0 - завершеине работы программы\n");
        printf("Выбирете опцию: ");

        if (scanf("%d", &choise) != 1)
            printf("Нет такого пункиа в меню\n");
        else
        {
            switch (choise)
            {
                case (1) :
                    main_array();
                    break;
                case (2):
                    main_list();
                    break;
                case (0):
                    printf("Завершеине работы\n");
                    break;
                default:
                    printf("Нет такого пункта меню\n");
                    break;
            }
        }
    }

    return rn;
}
