#include "main.h"
#include "array_operations.h"
#include "list_operations.h"

int main(void)
{
    int rn = OK;   // Код возврата
    int choise = 1, choise1 = 1;  // Переменные для реализации меню программы
    int element;  // Вводимое пользователем значение
    int array[LEN_ARRAY];  // Массив для стека
    int *pa = array, *pb = array + LEN_ARRAY, *ps = array - 1;  // Указатели для работы с массивом
    unsigned long long time_for_add_in_array = 0;  // Время выполнения функции добавления элемента для массива
    unsigned long long time_for_add_in_list = 0;  // Время выполнения функции добавления элемента для списка
    unsigned long long time_for_delete_in_array = 0;  // Время выполнения функции удаления элемента для массива
    unsigned long long time_for_delete_in_list = 0;  // Время выполнения функции удаления элемента для списка
    //unsigned long long time_for_seq_in_array = 0;  // Время выполнения функции поиска последовательностей для массива
    //unsigned long long time_for_seq_in_list = 0;  // Время выполнения функции поиска последовательностей для списка

    while (choise != 0)
    {
        printf("1 - реализация массивом\n");
        printf("2 - реализация списком\n");
        // printf("3 - вывод замеров времени\n");
        printf("0 - завершение программы\n");
        printf("Выбирете опцию: ");
        if (scanf("%d", &choise) != 1)
        {
            choise = 0;
            printf("Нет такого поля\n");
        }

        if (choise == 1)
        {
            choise1 = 1;
            while (choise1 != 0)
            {
                printf("\n");
                printf("    1 - добавление элемента\n");
                printf("    2 - удаление элемента\n");
                printf("    3 - вывод убывающих последовательностей\n");
                printf("    4 - вывод массива\n");
                printf("    0 - Обратно\n");
                printf("    Выбирете опцию: ");
                scanf("%d", &choise1);
                switch (choise1)
                {
                    case (1): printf("         Введите элемент: ");
                              if (scanf("%d", &element) != 1)
                              {
                                  printf("        Неподходящий тип элемента\n");
                                  rn = WRONG_ELEMENT;
                              }
                              else
                              {
                                  if (add_element(&ps, pb, element, &time_for_add_in_array) != OK)
                                  {
                                      printf("         Переполнение массива\n");
                                      rn = OVERFLOW;
                                  }
                                  else
                                      printf("         Элемент добавлен\n");
                              }
                              break;
                    case (2): if (delete_element(&ps, pa, &time_for_delete_in_array) != OK)
                                  printf("        Пустой массив\n");
                              else
                                  printf("         Элемент удален\n");
                              break;
                    
                    case (3): if (ps >= pa && ps <= pb)
                                  //time_for_seq_in_array = print_sequences(pa, pb, ps);
                                  print_sequences(pa, pb, ps);
                              else
                                  printf("         Пустой массив\n");
                              break;
                    
                    case (4): print_array(pa, ps + 1);
                              break;
                    case (0): printf("\nЗавершение работы с массивом\n\n");
                              break;
                    default : printf("         Нет такой опции\n");
                              break;
                }
            }
        }
        else if (choise == 2)
        {
            list_element *head = NULL;  // Указатель на список
            free_list_element *head_free = NULL;  // Указатель на список освобожденных областей
            choise1 = 1;

            while (choise1 != 0)
            {
                printf("\n");
                printf("    1 - добавление элемента\n");
                printf("    2 - удаление элемента\n");
                printf("    3 - вывод вывод убывающих последовательностей\n");
                printf("    4 - вывод списков\n");
                printf("    0 - Обратно\n");
                printf("    Выбирете опцию: ");
                scanf("%d", &choise1);

                switch (choise1)
                {
                    case (1):   printf("        Введите элемент: ");
                                if (scanf("%d", &element) == 1)
                                {
                                    if (add_element_to_list(&head, &head_free, element, &time_for_add_in_list) != 0)
                                        printf("        Не получилось выделить память\n");
                                    else
                                        printf("        Элемент добавлен\n");
                                }
                                else
                                    printf("        Неподходящий тип элемента\n");
                                break;
                    case (2):   if (delete_element_from_list(&head, &head_free, &time_for_delete_in_list) != 0)
                                    printf("        Не получилось выделить память\n");
                                else
                                    printf("        Элемент удален\n");
                                break;
                    case (3):   if (head != NULL)
                                    //time_for_seq_in_list = print_sequences_in_list(head);
                                    print_sequences_in_list(head);
                                else
                                    printf("Пустой список\n");
                                break;
                    case (4):   print_list(head);
                                print_free_list(head_free);
                                break;
                    case (0):   printf("\nЗавершение работы со списком\n\n");
                    default :   printf("Нет такой опции\n");
                                break;
                }
            }
        }
        /*
        else if (choise == 3)
        {
            printf("\n");
            printf("Время добавления элемента в массив = %llu\n", time_for_delete_in_array);
            printf("Время добавления элемента в список = %llu\n", time_for_add_in_list);
            printf("Время удаления элемента из массива = %llu\n", time_for_delete_in_array);
            printf("Время удаления элемента из списка = %llu\n", time_for_delete_in_list);
            printf("Время поиска последовательностей в массиве = %llu\n", time_for_seq_in_array);
            printf("Время поиска последовательностей в списке = %llu\n", time_for_seq_in_list);
            printf("\n");
        }
        */
        else if (choise == 0)
            printf("Завершение программы\n");
        else
            printf("Нет такой опции\n");
    }

    return rn;
}
