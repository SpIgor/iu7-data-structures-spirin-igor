#include<stdio.h>
#include<stdlib.h>

#define MAX_NODES 1000

int n;
int capacity[MAX_NODES][MAX_NODES];
int reach[MAX_NODES];


void to_dot(FILE *param, int from, int to)
{
    FILE *f = param;
    fprintf(f, "%d -> %d;\n", from, to);
}

void dfs(int v)
{
     int i;
     reach[v]=1;
     for(i=0; i<n; i++)
         if(capacity[v][i] && !reach[i])
            dfs(i);
 }

int read_input_file(FILE *in) {
    int a,b,i,j;
    FILE* input = in;
    // read number of nodes and edges
    int e = 0;
    fscanf(input,"%d %d",&n,&e);
    // initialize empty capacity matrix 
    for (i=0; i<n; i++) 
    {
        for (j=0; j<n; j++) 
        {
            capacity[i][j] = 0;
        }
    }
    FILE *f = fopen("gra.gv", "w");
    fprintf(f, "digraph %s {\n", "gra");

    // read edge capacities
    for (i=0; i<e; i++) 
    {

        fscanf(input,"%d %d",&a,&b);
        capacity[a][b] = 1;

        to_dot(f, a, b);

    }
    fprintf(f, "}\n");
    fclose(f);

    system("dot -Tpng gra.gv -o gra.png");
    //system("shotwell gra.png &");

    fclose(input);
    return n;
}

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        FILE *in = fopen(argv[1], "r");
        if(in != NULL)
        {
            n = read_input_file(in);

            printf("Начало обхода: ");
            int k;
            if (!scanf("%d", &k))
            {
                printf("Неверный символ\n");
                exit(-1);
            }
            printf("\n");
            dfs(k);

            printf("Недостижимые вершины:\n");
            for(int i = 0; i < n; i++)
               if(!reach[i] && i != k)
                printf("%d\n", reach[i]);
        }
        else
            printf("\nНе удалось открыть файл\n");
    }
    else
        printf("\nНе указан файл графа\n");
}