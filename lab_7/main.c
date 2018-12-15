#include "define_file.h"
#include "functions.h"
#include "input_output.h"

int main(void)
{
    int rn = OK;
    int choice = -1;
    int exist = 0;
    int del = 0;
    T_t *tree = NULL;
    balance_t *b_tree = NULL;
    Close_t *close_table = (Close_t*)calloc(MAX_NUM,sizeof(Close_t));
    Open_t *open_table = (Open_t*)calloc(MAX_NUM,sizeof(Open_t));
    int size1 = MAX_NUM, size2 = MAX_NUM;
    double coef1 = 0; double coef2 = 0;
    FILE *f_in;
    char *file_name = (char*)calloc(LEN_STRING+2,sizeof(char));
    char *search = (char*)calloc(LEN_STRING+2,sizeof(char));
    int compare = 0;

    clean_tables(close_table, open_table, size1, size2);
    while(choice)
    {
        printf("Выберите действие:\n\
1 - считать данные\n\
2 - вывести дерево двоичного поиска\n\
3 - вывести сбалансированное дерево\n\
4 - вывести хэш-таблицу\n\
5 - добавить слово\n\
6 - удалить слово\n\
7 - поиск слова в дереве\n\
8 - сравнить время поиска\n\
0 - выход\n\n");
        printf("Ваш выбор: ");
        if (scanf("%d",&choice) != 1)
        {
            printf("Введен некорректный символ\n\n");
            rn = WRONG_SYMB;
            break;
        }
        printf("\n");
        switch (choice)
        {
            case 1: /*
                    printf("Введите название файла: ");
                    scanf("%s",file_name);
                    printf("\n");
                    f_in = fopen(file_name, "r");
                    */
                    f_in = fopen("in_1.txt", "r");
                    if (f_in)
                    {
                        if (exist)
                        {
                            free_tree(tree);                           
                            free_balance_tree(b_tree);
                            b_tree = NULL;
                            tree = NULL;
                            clean_tables(close_table,open_table, size1, size2);
                            exist = 0;
                        }
                        tree = read_tree(f_in, &rn, &b_tree, close_table, open_table, &coef1, &coef2, &size1, &size2);  // считываение дерева

                        while (coef1 > 1.33)
                            close_table = restruct_close(close_table, &coef1, &size1);
                        while (coef2 > 0.5)
                            open_table = restruct_open(open_table, &coef2, &size2);
                        if (!rn)
                            exist = 1;
                        else if (rn == WRONG_FORMAT)
                            printf("Неверный формат\n\n");
                        else
                            printf("Невозможно выделить память подо все элементы\n\n");
                        fclose(f_in);
                    }
                    else
                    {
                        printf("Невозможно открыть файл\n");
                        rn = CANNOT_OPEN;
                    }

                 break;
            case 2: if (exist)
                    {
                       FILE *f_out;
                       f_out = fopen("tree.gv", "w");
                       export_to_dot(f_out, "Tree", tree);
                       fclose(f_out);
                       system("dot -Tpng tree.gv -otree.png");
                       system("shotwell tree.png");
                       printf("\n");
                    }
                    else
                        printf("Введите дерево\n\n");

                break;
            case 3: if (exist)
                    {
                        FILE *f_out;
                        f_out = fopen("tree_balance.gv", "w");
                        export_to_dot_balance(f_out, "Tree", b_tree);
                        fclose(f_out);
                        system("dot -Tpng tree_balance.gv -otree_b.png");
                        system("shotwell tree_b.png");
                        printf("\n");
                    }
                    else
                        printf("Введите дерево\n\n");
                break;
            case 4: if (exist)
                    {
                       printf("Таблица с закрытым хэшированием:\n");
                       for (int i = 0; i < size1; i++)
                       {
                           printf("%d   %s\n",i, close_table[i].word);
                       }
                       printf("\nТаблица с открытым хэшированием:\n");
                       for (int i = 0; i < size2; i++)
                       {
                           if (open_table[i].hash != -1)
                           {
                               data_t *open_tmp = open_table[i].data;
                               while(open_tmp)
                               {
                                   if (open_tmp->state)
                                       printf("%d   %s\n",i,open_tmp->word);
                                   open_tmp = open_tmp->next;
                               }
                           }
                           else
                               printf("%d\n",i);

                       }
                       printf("\n");
                    }
                    else
                        printf("Введите таблицу\n\n");
                break;
            case 5:tree = input_word(tree, &rn, &b_tree, close_table, open_table, &coef1, &coef2, &size1, &size2);
                   while (coef1 > 1.33)
                       close_table = restruct_close(close_table, &coef1, &size1);
                   while (coef2 > 0.5)
                       open_table = restruct_open(open_table, &coef2, &size2);
                   if (!rn)
                   {
                       printf("Элемент добавлен\n\n");
                       exist = 1;
                   }
                   else if (rn == WRONG_FORMAT)
                       printf("Неверный формат\n\n");
                   else
                       printf("Невозможно выделить память\n\n");
                break;
            case 6: if (exist)
                    {
                        printf("Введите слово удаляемое слово: ");
                        scanf("%s",search);
                        printf("\n");
                        rn = check_word(search);
                        if(!rn)
                        {
                            compare = 0;
                            if (search_word(tree, search, &compare))
                            {
                                remove_word(&tree, search);
                                b_tree = remove_balance(b_tree, search, &del);
                                remove_close(close_table, search, size1, &coef1);
                                remove_open(open_table, search, size2, &coef2);
                                del = 0;
                                if (tree)
                                    printf("Слово удалено\n\n");
                                else
                                {
                                    printf("Введите дерево\n\n");
                                    exist = 0;
                                }
                            }
                            else
                                printf("Слова нет в дереве\n\n");
                        }
                        else
                            printf("Неверный формат\n\n");
                    }
                    else
                        printf("Введите данные\n\n");
                break;
            case 7: if (exist)
                    {
                       printf("Введите слово: ");
                       scanf("%s",search);
                       printf("\n");
                       rn = check_word(search);
                       if(rn)
                       {
                          printf("Введено недопустимое значение\n\n");
                          rn = WRONG_FORMAT;
                       }
                       else
                       {
                           compare = 0;
                           if (search_word(tree, search, &compare))
                               printf("Слово найдено в дереве двоичного поиска\n");
                           else
                               printf("Слово не найдено в дереве двоичного поиска\n");
                           printf("Количество сравнений: %d\n\n",compare);

                           compare = 0;
                           if (search_balance(b_tree, search, &compare))
                               printf("Слово найдено в сбалансированном дереве\n");
                           else
                               printf("Слово не найдено в сбалансированном дереве\n");
                           printf("Количество сравнений: %d\n\n",compare);

                           compare = 0;
                           if (search_close(close_table, search, &compare, size1))
                               printf("Слово найдено в таблице с закрытым хэшированием\n");
                           else
                               printf("Слово не найдено в таблице с закрытым хэшированием\n");
                           printf("Количество сравнений: %d\n\n",compare);

                           compare = 0;
                           if (search_open(open_table, search, &compare, size2))
                               printf("Слово найдено в таблице с открытым хэшированием\n");
                           else
                               printf("Слово не найдено в таблице с открытым хэшированием\n");
                           printf("Количество сравнений: %d\n\n",compare);
                       }
                    }
                    else
                        printf("Введите данные\n\n");

                break;            
            case 8:time_it();
                break;
            case 0: printf("Завершение работы\n");
                    if(exist)
                        free_tree(tree);
                   if (file_name)
                       free(file_name);
                   if (search)
                       free(search);
                break;
            default: printf("Введен неизвестный пункт меню\n\n");
                break;
        }
    }
    return rn;
}