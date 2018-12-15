#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

void dejkstra(int **a, int *d, int size)
{
  int v[size]; // массив меток
  int temp, i;
  int minindex, min;

  for (i = 0; i<size; i++) {
    d[i] = INF; // массив путей инициализируется бесконечностью
    v[i] = 1;
  }
  d[0] = 0;
  do { // исполнение алгоритма 
    minindex = INF;
    min = INF;
    for (i = 0; i<size; i++) {
      if ((v[i] == 1) && (d[i]<min)) {
        min = d[i];
        minindex = i;
      }
    }
    if (minindex != INF) {
      for (i = 0; i<size; i++) {
        if (a[minindex][i] != INF) {
          temp = min + a[minindex][i];
          if (temp < d[i])
            d[i] = temp;
        }
      }
      v[minindex] = 0;
    }
  } while (minindex < INF);
}

int main(void)
{
	FILE *in_file = fopen("in.txt", "r");

	int n = 0;
	fscanf(in_file, "%d", &n);

	int **graph = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; ++i)
		graph[i] = (int *)calloc(n, sizeof(int));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			fscanf(in_file, "%d", &graph[i][j]);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			printf("%d  ", graph[i][j]);
		printf("\n");
	}

	int *d = (int *)calloc(n, sizeof(int));
	dejkstra(graph, d, n);

	printf("Len: ");
	for (int i = 0; i < n; ++i)
		printf("%d  ", d[i]);

	return 0;
}