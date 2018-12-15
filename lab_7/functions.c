#include "functions.h"

// ДВОИЧНОЕ ДЕРЕВО ПОИСКА

T_t* add_tree(T_t *root, T_t *add_word)  // добавление элемента в дерево двоичного поиска
{
    if (root != NULL)
    {
        if (strcmp(root->word, add_word->word) > 0)
            root->right = add_tree(root->right, add_word);
        else if (strcmp(root->word, add_word->word) < 0)
            root->left = add_tree(root->left, add_word);
    }
    else
        root = add_word;

    return root;
}

void find_replace(T_t **branch, T_t *root)  // поиск самого правого потомка левого поддерева (двоичное дерево поиска)
{
    if((*branch)->right)
        find_replace(&((*branch)->right), root);
    else
    {
        my_strcopy(root->word,(*branch)->word);
        T_t *tmp = *branch;
        *branch = (*branch)->left;
        free(tmp);
    }
}

void remove_word(T_t **root,char* search)  // удаление слова из дерева двоичного поиска
{
    int cmp;
    T_t *tmp;

    if (*root)
    {
        cmp = strcmp((*root)->word, search);
        if (cmp > 0)
            remove_word(&((*root)->right),search);
        else if (cmp < 0)
            remove_word(&((*root)->left),search);
        else
        {
            if (!(*root)->right)  // если нет правого потомка заменить на левый
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
                find_replace(&((*root)->left), *root);  // найти самену в левом поддреве
        }
    }
}

T_t* search_word(T_t *root, char* search, int *cmp)  // поиск узлов (двоичное дерево поиска)
{
    if (root)
    {
        if (strcmp(root->word, search) > 0)
        {
            *cmp += 1;
            search_word(root->right, search, cmp);
        }
        else if (strcmp(root->word, search) < 0)
        {
            *cmp += 1;
            search_word(root->left, search, cmp);
        }
        else
        {
            *cmp += 1;
            return root;
        }
    }
    else
        return NULL;
}


// СБАЛАНСИРОВАННОЕ ДЕРЕВО

int max(int a, int b)
{
    return (a > b)? a : b;
}

int height(balance_t *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

balance_t *new_node(char *value)
{
    balance_t *node = (balance_t*)malloc(sizeof(balance_t));
    my_strcopy(node->word, value);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

// левый поворот дерева
balance_t *left_rotate(balance_t *x)
{
    balance_t *y = x->right;
    balance_t *t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

// правый поворот дерева
balance_t *right_rotate(balance_t *y)
{
    balance_t *x = y->left;
    balance_t *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}

int get_balance(balance_t *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

balance_t* min_val_node(balance_t* node)
{
    balance_t* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

balance_t* add_balance_tree(balance_t* root, char* value)  // добавление элемента в сбалансированное дерево
{
    if (root == NULL)
        return(new_node(value));

    if (strcmp(value,root->word) > 0)
        root->left  = add_balance_tree(root->left, value);
    else if (strcmp(value,root->word) < 0)
        root->right = add_balance_tree(root->right, value);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = get_balance(root);
    if (balance > 1 && strcmp(value, root->left->word) > 0)
        return right_rotate(root);
    if (balance < -1 && strcmp(value, root->right->word) < 0)
        return left_rotate(root);
    if (balance > 1 && strcmp(value, root->left->word) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && strcmp(value, root->right->word) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

balance_t* remove_balance(balance_t* root, char *key, int *del)
{
    if (root == NULL)
        return NULL;
    if (strcmp(key, root->word) > 0)
        root->left = remove_balance(root->left, key, del);
    else if(strcmp(key, root->word) < 0)
        root->right = remove_balance(root->right, key, del);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            balance_t *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                *del += 1;
                temp = root;
                root = NULL;
            }
            else
            {
                *del += 1;
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            balance_t* temp = min_val_node(root->right);
            my_strcopy(root->word,temp->word);
            root->right = remove_balance(root->right, temp->word, del);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = get_balance(root);
    if (balance > 1 && get_balance(root->left) <= 0)
        return right_rotate(root);
    if (balance > 1 && get_balance(root->left) > 0)
    {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) >= 0)
        return left_rotate(root);
    if (balance < -1 && get_balance(root->right) < 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

balance_t* search_balance(balance_t* root, char *key, int *cmp)  // поиск в сбалансированном дереве
{
    if (root == NULL || strcmp(root->word, key) == 0)
    {
       *cmp += 1;
       return root;
    }
    if (strcmp(root->word, key) > 0)
    {
       *cmp += 1;
       return search_balance(root->right, key, cmp);
    }
    *cmp += 1;
    return search_balance(root->left, key, cmp);
}

// ХЭШ-ТАБЛИЦА


int hash_function(char *word, int num)
{
    int hash = 0;
    for (int i = 0; word[i] != '\0' && word[i] != '\n'; i++)
        hash = (hash*31 + word[i])%num;

    if (hash == 196)
        hash = 195;

    return hash;
}

void insert_close(Close_t *close_table, char *string, double *coef, int size)  // закрытое хэширование
{
    int hash = hash_function(string, size);
    //printf("close    %d   %s",close_table[31].hash, string);
    if (close_table[hash].hash == -1)
    {
        my_strcopy(close_table[hash].word,string);
        close_table[hash].hash = hash;
        close_table[hash].count = 0;
    }
    else
    {
        int index = hash;
        int num = 1;
        while (close_table[index].hash != -1)
        {
            if (index >= size)
            {
                num = 1;
                index = 0;
            }
            else
                index += num;
            num += 1;
            num *= num;
        }
        my_strcopy(close_table[index].word,string);
        close_table[index].hash = hash;
        close_table[hash].count += 1;
    }
    *coef += (double)1/size;
}

void insert_open(Open_t *open_table, char *string, double *coef, int size)  // открытое хэширование
{
    int hash = hash_function(string, size);

    if (hash == 196)
        printf("%s",string);

    //printf("\nopen    %d   %s\n",open_table[31].hash, string);
    if (open_table[hash].hash == -1)
    {
        //printf("    in -1\n");
        open_table[hash].hash = hash;
        open_table[hash].data = (data_t*)calloc(1,sizeof(data_t));
        my_strcopy(open_table[hash].data->word,string);
        open_table[hash].data->state = 1;
        open_table[hash].data->next = NULL;
    }
    else
    {
       // printf("    after\n");
        data_t *tmp = (data_t*)calloc(1,sizeof(data_t));
        my_strcopy(tmp->word,string);
        tmp->state = 1;
        tmp->next = open_table[hash].data;
        open_table[hash].data = tmp;
        //if (strcmp(tmp->word, "effort") == 0)
          //  printf("!!!!!!!!                %d\n", open_table[hash].hash);
        //printf("1 = %s\n2 = %s\n", tmp->word, tmp->next->word);
    }
    *coef += (double)1/size;
}

Close_t* restruct_close(Close_t* close, double *coef,  int *size)  // реструкторизация закрытой
{
    *coef = 0;
    Close_t *tmp = (Close_t*)calloc(*size*2,sizeof(Close_t));
    for (int i = 0; i < *size*2; i++)
    {
        for (int j = 0; j < LEN_STRING; j++)
            tmp[i].word[j] = '\0';
        tmp[i].hash = -1;
    }
    for (int i = 0; i < *size; i++)
    { 
        if (close[i].hash != -1)        
             insert_close(tmp,close[i].word,coef,*size*2);

    }   
    *size *= 2;
    return tmp; 
}

Open_t* restruct_open(Open_t* open,double *coef,  int *size)  // реструкторизация закрытой
{
    *coef = 0;
    Open_t *tmp = (Open_t*)malloc((*size)*2*sizeof(Open_t));
    for (int i = 0; i < (*size)*2; i++)
    {
        tmp[i].hash = -1;
        tmp[i].data = NULL;
    }

    for (int i = 0; i < (*size); i++)
    {        
        if (open[i].data)
        { 
             //printf("%d   %s  %d",i, open[i].data->word, open[i].hash);
             data_t *save = open[i].data;
             while (save)
             {
                 insert_open(tmp, save->word, coef, (*size)*2);
                 save = save->next;
             }
        }
    }
    *size *= 2;
    return tmp; 
}

void shift_up(Close_t *close, int s_h, int size, int index, int num, int count)
{
    int next = index + num;

    while(count < close[s_h].count)
    {
        if (close[next].hash != -1)
        {
            if (hash_function(close[index].word, size) == s_h)
                for (int i = 0; close[index].word[i];i++)
                    close[index].word[i] = '\0';
            if (hash_function(close[next].word, size) == s_h)
                my_strcopy(close[index].word, close[next].word);
            index = next;
        }

        num += 1;
        num *= num;
        next += num;
        if (next >= size)
        {
            num = 1;
            next = 0;
        }
        count += 1;
    }

}

void remove_close(Close_t *close_table, char *search, int size, double *coef)  // удаление элемента из таблицы с закрытым хэшированием
{
    int s_h = hash_function(search, size);
    int count = 0;
    close_table[s_h].count -= 1;
    if (strcmp(close_table[s_h].word, search) == 0)
    {
        for (int i = 0; close_table[s_h].word[i];i++)
            close_table[s_h].word[i] = '\0';
        shift_up(close_table, s_h, size, s_h, 1, count);
    }
    else
    {
        int index = s_h + 1;
        int num = 1;
        while (strcmp(close_table[index].word,search) && count < close_table[s_h].count)
        {
            num += 1;
            num *= num;
            if (index >= size)
            {
                num = 1;
                index = 0;
            }
            else
                index += num;
            if (hash_function(close_table[index].word,size) == s_h)
                count += 1;
        }
        if (strcmp(close_table[index].word,search) == 0)
        {
            for (int i = 0; close_table[index].word[i];i++)
                close_table[index].word[i] = '\0';
            shift_up(close_table, s_h, size, index, num, count);
        }
    }
    *coef -= 1/(size);

}


void remove_open(Open_t *open_table, char *search,int size,double *coef)  // удаление элемента из таблицы с открытым хэшированием
{
    int h = hash_function(search, size);
    data_t *tmp = open_table[h].data;

    while (open_table[h].data)
    {
        if (strcmp(open_table[h].data->word, search) == 0)
        {
            open_table[h].data->state = 0;
            break;
        }

        open_table[h].data = open_table[h].data->next;
    }
    *coef -= 1/(size);
    open_table[h].data = tmp;
}


int search_close(Close_t *close, char *search, int *cmp, int size)  // поиск в тбалице с закрытым хэшированием
{
    int s_h = hash_function(search, size);
    int found = 0;
    int count = 0;
    *cmp = 1;
    if (strcmp(close[s_h].word, search) == 0)
        found = 1;
    else
    {
        int index = s_h + 1;
        int num = 1;
        while (count < close[s_h].count && strcmp(close[index].word,search))
        {
            if (close[index].hash != -1)
            {
                if (hash_function(close[index].word,size) == s_h)
                    count += 1;
            }
            num += 1;
            num *= num;
            if (index >= size)
            {
                num = 1;
                index = 0;
            }
            else
                index += num;
            *cmp += 1;
        }
        if (!strcmp(close[index].word,search))
            found = 1;
    }
    return found;
}

int search_open(Open_t *open, char *search, int *cmp, int size)  // поиск в таблице с открытым хэшированием
{
    int found = 0;
    *cmp = 1;
    int s_h = hash_function(search, size);
    if (open[s_h].data)
    {
        if (!strcmp(open[s_h].data->word, search) && open[s_h].data->state)
            found = 1;
        else
        {
            if (open[s_h].data->state == 0)
                *cmp -= 1;
            data_t *tmp = open[s_h].data;
            while (strcmp(tmp->word, search) && tmp->next != NULL)
            {
                tmp = tmp->next;
                if (tmp->state)
                    *cmp += 1;
            }
            if (!strcmp(tmp->word, search) && tmp->state)
                found = 1;
        }
    }
    if (*cmp == 0)
        *cmp = 1;
    return found;
}

// ЗАМЕР ВРЕМЕНИ

void time_it()  // замер времени выполнения
{    
    FILE *f_in;
    T_t *tree = NULL;
    balance_t *b_tree = NULL;
    Close_t *close = (Close_t*)malloc(MAX_NUM*sizeof(Close_t));
    Open_t *open = (Open_t*)malloc(MAX_NUM*sizeof(Open_t));
    int size1 = MAX_NUM, size2 = MAX_NUM;
    double coef1 = 0; double coef2 = 0;
    int rn = OK;
    char search[LEN_STRING + 2];
    time_t t1, t2;
    int compare = 0;

    clean_tables(close, open, size1, size2);

    f_in = fopen("in_7.txt", "r");
    if (f_in)
    {
        tree = read_tree(f_in, &rn, &b_tree, close, open, &coef1, &coef2, &size1, &size2);
        while (coef1 > 1.33)
            close = restruct_close(close, &coef1, &size1);
        while (coef2 > 0.5)
            open = restruct_open(open, &coef2, &size2);
        if (!rn)
        {
            printf("    Введите слово: ");
            scanf("%s",search);
            printf("\n");
            int ret = check_word(search);
            if (!ret)
            {
                    printf("    Время поиска слова '%s' в мс:\n",search);
                    t1 = clock();
                    search_word(tree, search, &compare);
                    t2 = clock();
                    printf("    В дереве двоичного поиска: %5ld    Число сравнений:  %d\n",t2-t1, compare);
                    compare = 0;
                    t1 = clock();
                    search_balance(b_tree, search, &compare);
                    t2 = clock();
                    printf("    В сбалансированном дереве: %5ld    Число сравнений:  %d\n",t2-t1, compare);
                    t1 = clock();
                    compare = 0;
                    search_close(close, search, &compare, size1);
                    t2 = clock();
                    printf("    В таблице с закрытым хэшированием: %5ld    Число сравнений:  %d\n",t2-t1, compare);
                    t1 = clock();
                    compare = 0;
                    search_open(open, search, &compare, size2);
                    t2 = clock();
                    printf("    В таблице с открытым хэшированием: %5ld    Число сравнений:  %d\n\n",t2-t1, compare);

            }
            else
            {
               printf("    Введено недопустимое значение\n\n");
               rn = WRONG_FORMAT;
            }
        }
        fclose(f_in);
    }
    else
        printf("    Нет такого файла как in_1.txt \n\n");
}