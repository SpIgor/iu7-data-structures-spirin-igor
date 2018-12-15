#include "main.h"
#include "tree_operations.h"

int main(void)
{
    char file_name[LEN_STRING];  // имя входного файла
    FILE *in_file, *out_file;  // Указатели на файлы
    int choice = 1;  // Переменная для работы с меню
    int *date = (int *)calloc(8, sizeof(int));  // Вводимая пользователем дата
    int count = 0;  // Количество введенных позиций
    char *string;  // Вводимое пользоваетем имя файла
    size_t len_string = LEN_STRING;  // длина строки
    tree_t *root = NULL;  // Корень дерева
    int rn = OK;  // Код возврата

    while (choice)
    {
        printf("\n1 - считать граф из файла\n");
        printf("2 - добавить вершину в граф\n");
        printf("3 - удаление файлов\n");
        printf("4 - вывести граф\n");
        printf("5 - обход дерева\n");
        printf("0 - завершение работы\n");
        printf("Выберете пункт меню: ");
        if (scanf("%d", &choice) == 1)
        {
            switch (choice)
            {
                case (1):
                    printf("Введите имя файла: ");
                    scanf("%s", file_name);
                    in_file = fopen(file_name, "r");
                    if (in_file)
                    {
                        printf("Считывание дерева\n");
                        rn = read_tree_from_file(&root, in_file);
                        if (rn)
                        {
                            printf("Неверный формат\n");
                            exit(WRONG_FORMAT);
                        }
                    }
                    else
                    {
                        printf("Не возможно открыть файл\n");
                        exit(CANT_OPEN_FILE);
                    }
                    break;
                case (2):
                    printf("Введите вершину: ");
                    string = (char *)calloc(LEN_STRING, sizeof(char));
                    scanf("\n");
                    getline(&string, &len_string, stdin);
                    if (!check_sting(string))
                    {
                        rn = allocate_element(&root, string);
                        if (rn)
                            printf("Невозможно выделить память\n");
                        else
                            printf("Элемент добавлен\n");
                    }
                    else
                    {
                        printf("Неверный формат\n");
                        rn = WRONG_FORMAT;
                    }
                    free(string);
                    break;
                
                case (3):
                    count = 0;
                    printf("Введите дату\n");
                    printf("День:\n");
                    scanf("%d", &date[count]);
                    count++;
                    scanf("%d", &date[count]);
                    count++;
                    printf("Месяц:\n");
                    scanf("%d", &date[count]);
                    count++;
                    scanf("%d", &date[count]);
                    count++;
                    printf("Год:\n");
                    scanf("%d", &date[count]);
                    count++;
                    scanf("%d", &date[count]);
                    count++;
                    scanf("%d", &date[count]);
                    count++;
                    scanf("%d", &date[count]);
                    count++;
                    remove_word(&root, date);
                    break;
                case (4):
                    if (root == NULL || (root->left == NULL && root->right == NULL))
                        printf("Недостаточно вершин\n");
                    else
                    {
                        out_file = fopen("tree.gv", "w");
                        export_to_dot(root, out_file);
                        fclose(out_file);
                        system("dot -Tpng tree.gv -otree.png");
                        system("shotwell tree.png");
                    }
                    break;
                case (5):
                    printf("\n1 - Постфиксный обход\n");
                    printf("\n2 - Префиксный обход\n");
                    printf("\n3 - Инфиксный обход\n");
                    if (scanf("%d", &choice) == 1)
                    {
                        switch (choice)
                        {
                            case (1):
                                postfix(root);
                                break;
                            case (2):
                                prefix(root);
                                break;
                            case (3):
                                infix(root);
                                break;
                            default:
                                printf("Неверный пункт меню\n");
                                break;
                        }
                    }
                    break;
                case (0):
                    free_tree(root);
                    free(date);
                    printf("Завершение работы\n");
                    break;
                default:
                    printf("Неверный пункт меню\n");
                    break;

            }
        }
        else
            printf("Ошибка ввода\n");
    }
    return 0;
}
