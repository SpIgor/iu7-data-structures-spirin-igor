#include <stdio.h>

int main(void)
{
	FILE *out_file = fopen("out.txt", "w");
	for (int i = 0; i < 1000; i++)
	{
		fprintf(out_file, "%s;", "as");
        fprintf(out_file, "%s;", "as");
        fprintf(out_file, "%d;", 1000 - i);
        fprintf(out_file, "%s;", "as");

        fprintf(out_file, "%d;", 1000 - i);
        fprintf(out_file, "%d;", 1000 - i);
        fprintf(out_file, "%d;", 1000 - i);
        fprintf(out_file, "\n");

	}

	return 0;
}