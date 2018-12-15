#include "main.h"
#include "tree_operations.h"

// Освобождение памяти под дерево
void free_tree(tree_t *root)
{
    tree_t *left, *right;
    if(root)
    {
        right = root->right;
        left = root->left;
        free(root);
        if (left)
            free_tree(left);

        if (right)
            free_tree(right);
    }
}

// Постфиксный обход дерева
void postfix(tree_t *root)
{
    if (root)
    {
        postfix(root->left);
        postfix(root->right);
        printf("%s   ",root->data->name);
    }
}

// Префиксный обход дерева
void prefix(tree_t *root)
{
    if (root)
    {
        postfix(root->left);
        printf("%s   ",root->data->name);
        postfix(root->right);
    }
}

// Инфиксный обход дерева
void infix(tree_t *root)
{
    if (root)
    {
        printf("%s   ",root->data->name);
        postfix(root->left);
        postfix(root->right);
    }
}

// Добавление элемента в дерево
tree_t *add_to_tree(tree_t *root, tree_t *tmp)
{
    if (root)
    {
        if (strcmp(root -> data -> name, tmp -> data -> name) > 0)
            root->left = add_to_tree(root -> left, tmp);
        else if (strcmp(root -> data -> name, tmp -> data -> name) < 0)
            root->right = add_to_tree(root -> right, tmp);
        else
        {
            printf("Повторный элемент\n");
            exit(WRONG_FORMAT);
        }
    }
    else
        root = tmp;

    return root;
}

// Проверка строки на соответствие формату
int check_sting(char *string)
{
    char *pos = strchr(string, '|');
    
    if (*string == '|')
        return WRONG_FORMAT;
    if (!pos)
        return WRONG_FORMAT;
    else
        pos++;
    if (strlen(pos) < 10)
        return WRONG_FORMAT;
    if (*(pos + 2) != '.' && *(pos + 5) != '.')
        return WRONG_FORMAT;
    for (int i = 0; i < 10; ++i)
    {
        if (i != 2 && i != 5)
            if (!isdigit(pos[i]))
            {
                printf("%c\n", pos[i]);
                return WRONG_FORMAT;
            }
    }

    while (*pos != '\n')
        pos++;
    *pos = '\0';

    return OK;
}

// Полуяение даты из вводимой строки
void get_date(int *date, char *string)
{
    int count = 0;
    while (*string)
    {
        if (*string != '.')
        {
            date[count] = *string - '0';
            count++;
        }
        string++;
    }
}

// Считывание дерева из файла
int read_tree_from_file(tree_t **root, FILE *in_file)
{
    int rn = OK;
    size_t len_string = LEN_STRING;
    char* string = (char *)calloc(len_string, sizeof(char));
    tree_t *tmp;
    data_t *tmp_d;
    char *pos;

    while (!rn && getline(&string, &len_string, in_file) > 0)
    {
        if (check_sting(string))
            return WRONG_FORMAT;
        tmp = (tree_t *)calloc(1, sizeof(tree_t));
        tmp_d = (data_t *)calloc(1, sizeof(data_t));
        if (tmp && tmp_d)
        {
            pos = strchr(string, '|');
            tmp_d -> date = (int *)calloc(8, sizeof(int));
            tmp_d -> name = (char *)calloc(pos - string + 1, sizeof(char));
            if (tmp_d -> date && tmp_d -> name)
            {
                get_date(tmp_d -> date, pos + 1);
                *pos = '\0';
                strcpy(tmp_d -> name, string);
                tmp -> data = tmp_d;
                tmp -> left = NULL;
                tmp -> right = NULL;
                *root = add_to_tree(*root, tmp);
            }
            else
                rn = CANT_ALLOCATE;
        }
        else
            rn = CANT_ALLOCATE;
    }
    return rn;
}

// Добавление вершины пользователем
int allocate_element(tree_t **root, char *string)
{
    int rn = OK;
    tree_t *tmp;
    data_t *tmp_d;
    char *pos;
    tmp_d = (data_t *)calloc(1, sizeof(data_t));
    tmp = (tree_t *)calloc(1, sizeof(tree_t));
    if (tmp && tmp_d)
    {
        pos = strchr(string, '|');
        tmp_d -> date = (int *)calloc(8, sizeof(int));
        tmp_d -> name = (char *)calloc(pos - string + 1, sizeof(char));
        if (tmp_d -> date && tmp_d -> name)
        {
            get_date(tmp_d -> date, pos + 1);
            *pos = '\0';
            strcpy(tmp_d -> name, string);
            tmp -> data = tmp_d;
            *root = add_to_tree(*root, tmp);
        }
        else
            rn = CANT_ALLOCATE;
    }
    else
        rn = CANT_ALLOCATE;
    return rn;
}

// Вывод вершин в файл для языка dot
void to_dot(tree_t *root, FILE *out_file)
{
    char st = '"';
    if (root->left)
    {
        fprintf(out_file, "%c%s : ", st, root->data->name);
        for (int i = 0; i < 8; ++i)
        {
            fprintf(out_file, "%d", root->data->date[i]);
            if (i == 1 || i == 3)
                fprintf(out_file, ".");
        }
        fprintf(out_file, "%c", st);
        fprintf(out_file, "->");
        fprintf(out_file, "%c%s : ", st, root->left->data->name);
        for (int i = 0; i < 8; ++i)
        {
            fprintf(out_file, "%d", root->left->data->date[i]);
            if (i == 1 || i == 3)
                fprintf(out_file, ".");
        }
        fprintf(out_file, "%c\n", st);
        to_dot(root->left, out_file);
    }
    if (root->right)
    {
        fprintf(out_file, "%c%s : ", st, root->data->name);
        for (int i = 0; i < 8; ++i)
        {
            fprintf(out_file, "%d", root->data->date[i]);
            if (i == 1 || i == 3)
                fprintf(out_file, ".");
        }
        fprintf(out_file, "%c", st);
        fprintf(out_file, "->");
        fprintf(out_file, "%c%s : ", st, root->right->data->name);
        for (int i = 0; i < 8; ++i)
        {
            fprintf(out_file, "%d", root->right->data->date[i]);
            if (i == 1 || i == 3)
                fprintf(out_file, ".");
        }
        fprintf(out_file, "%c\n", st);
        to_dot(root->right, out_file);
    }
}

// Добавление заголовка в dot файл
void export_to_dot(tree_t *root, FILE *out_file)
{
    fprintf(out_file, "digraph File_system {\n");

    to_dot(root, out_file);

    fprintf(out_file, "}\n");
}

// Копирование даты
void copy_date(int *array1, int *array2)
{
    for (int i = 0; i < 8; ++i)
         array1[i] = array2[i];
}

// поиск самого правого потомка левого поддерева
void find_replace(tree_t **branch, tree_t *root)
{
    if((*branch)->right)
        find_replace(&((*branch)->right), root);
    else
    {
        copy_date(root->data->date, (*branch)->data->date);
        strcpy(root->data->name,(*branch)->data->name);
        tree_t *tmp = *branch;
        *branch = (*branch)->left;
        free(tmp);
    }
}

// Сравнение даты
int compare_date(int *date1, int *date2)
{
    for (int i = 4; i < 8; ++i)
    {
        if (date1[i] < date2[i])
        {
            return 1;
        }
        else if (date1[i] > date2[i])
        {
            return 0;
        }
    }
    for (int i = 2; i < 4; ++i)
    {
        if (date1[i] < date2[i])
        {
            return 1;
        }
        else if (date1[i] > date2[i])
        {
            return 0;
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        if (date1[i] < date2[i])
        {
            return 1;
        }
        else if (date1[i] > date2[i])
        {
            return 0;
        }
    }
    return 0;
}

// Удаление вершины
void remove_word(tree_t ** root, int *date)
{
    tree_t *tmp;
    if (*root)
    {
        remove_word(&((*root)->left), date);
        remove_word(&((*root)->right), date);
        if (compare_date((*root)->data->date, date))
        {
            printf("remove = %s\n", (*root)->data->name);
            if (!(*root)->right && !(*root)->left)
                *root = NULL;
            else if (!(*root)->right)  // если нет правого потомка заменить на левый
            {
                tmp = (*root);
                *root = (*root)->left;
                free(tmp);
            }
            else if (!(*root)->left)   // если нет левого потомка, заменить на правый
            {
                tmp = (*root);
                *root = (*root)->right;
                free(tmp);
            }
            else
            {
                find_replace(&((*root)->left), *root);  // найти самену в левом поддреве
            }
        }
    }
}