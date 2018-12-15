#include "input_output.h"

int check_word(char *word)  // проверка является ли строка словом
{
    int rn = OK;
    while(*word && *word != '\n' && !rn)
    {
        if ((*word <'A' || *word >'Z') && (*word <'a' || *word >'z'))
            rn = WRONG_FORMAT;
        word++;
    }

    return rn;
}

void my_strcopy(char *str_1, char *str_2)  // копирование строки
{
    while(*str_2 && *str_2 != '\n')
    {
        *str_1 = *str_2;
        str_1++;
        str_2++;
    }
    *str_1 = '\0';
}

T_t* read_tree(FILE *f, int *ret, balance_t **b_tree, Close_t *close_table, Open_t *open_table,  double *coef1, double *coef2, int *size1, int *size2)  // построение дерева
{
    T_t *root = NULL;  // корень дерева
    T_t *tmp = NULL;  // элемент дерева
    char *string = (char*)calloc(LEN_STRING + 2,sizeof(char));  // строка файла

    size_t n = LEN_STRING + 2;
    *ret = OK;
    while(!*ret && getline(&string,&n,f) != -1)
    {
        if(*string != '\n')
        {
            tmp = (T_t*)malloc(sizeof(T_t));           
            if (tmp)
            {
                *ret = check_word(string);
                if (!*ret)
                {
                    insert_close(close_table, string, coef1, *size1);
                    insert_open(open_table, string, coef2, *size2);
                    my_strcopy(tmp->word, string);
                    tmp->left = NULL;
                    tmp->right = NULL;                   
                    root = add_tree(root, tmp);
                    *b_tree = add_balance_tree(*b_tree, string);                    
                }
            }
            else
                *ret = CANT_ALLOCATE;
        }
    }
    return root;
}


T_t* input_word(T_t *root, int *ret, balance_t **b_tree, Close_t *close_table, Open_t *open_table, double *coef1, double *coef2, int *size1, int *size2)  // добавление элемента
{
    char *string = (char*)calloc(LEN_STRING +2,sizeof(char));  // слово
    T_t *tmp = (T_t*)malloc(sizeof(T_t));

    printf("Введите слово: ");
    scanf("%s",string);
    printf("\n");
    if (tmp)
    {
        *ret = check_word(string);
        if (!*ret)
        {
            my_strcopy(tmp->word, string);
            tmp->left = NULL;
            tmp->right = NULL;
            root = add_tree(root, tmp);
            *b_tree = add_balance_tree(*b_tree, string);
            insert_close(close_table, string, coef1, *size1);
            insert_open(open_table, string, coef2, *size2);
        }
    }
    else
        *ret = CANT_ALLOCATE;
    free(string);
    return root;
}

// ДЕРЕВО ДВОИЧНОГО ПОИСКА

void apply(T_t *root, void (*f)(T_t*, void*), void *arg)  // рекурсивная печать в файл
{
    if (root == NULL)
        return;

    f(root, arg);
    apply(root->left, f, arg);
    apply(root->right, f, arg);
}

void to_dot(T_t *root, void *param)  // запись в dot
{
    FILE *f = param;

    if (root->left)
        fprintf(f, "%s -> %s;\n", root->word, root->left->word);

    if (root->right)
        fprintf(f, "%s -> %s;\n", root->word, root->right->word);
}

void export_to_dot(FILE *f, const char *tree_name, T_t *root)  // экспорт графа
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply(root, to_dot, f);

    fprintf(f, "}\n");
}

// СБАЛАНСИРОВАННОЕ ДЕРЕВО

void apply_b(balance_t *root, void (*f)(balance_t*, void*), void *arg)  // рекурсивная печать в файл
{
    if (root == NULL)
        return;

    f(root, arg);
    apply_b(root->left, f, arg);
    apply_b(root->right, f, arg);
}

void to_dot_b(balance_t *root, void *param)  // запись в dot
{
    FILE *f = param;

    if (root->left)
        fprintf(f, "%s -> %s;\n", root->word, root->left->word);

    if (root->right)
        fprintf(f, "%s -> %s;\n", root->word, root->right->word);
}

void export_to_dot_balance(FILE *f,const char *tree_name, balance_t *root)  // вывод дерева в файл
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_b(root, to_dot_b, f);

    fprintf(f, "}\n");
}

void free_tree(T_t *root)  // освобождение памяти
{
    T_t *left, *right;
    if(!root)
        return;

    right = root->right;
    left = root->left;
    free(root);
    if (left)
        free_tree(left);

    if (right)
        free_tree(right);
}

void free_balance_tree(balance_t *root)  // освобождение памяти
{
    balance_t *left, *right;
    if(!root)
        return;

    right = root->right;
    left = root->left;
    free(root);
    if (left)
        free_balance_tree(left);

    if (right)
        free_balance_tree(right);
}

void clean_tables(Close_t *close, Open_t *open, int size1, int size2)  // очистка таблиц
{

    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < LEN_STRING; j++)
            close[i].word[j] = '\0';
        close[i].hash = -1;
    }

    for (int i = 0; i < size2; i++)
    {
        open[i].hash = -1;
        open[i].data = NULL;
    }
}