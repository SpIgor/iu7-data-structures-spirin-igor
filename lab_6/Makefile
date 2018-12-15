CC := gcc
CFLAGS := -Wall

main.exe : main.o tree_operations.o
	$(CC) $(CFLAGS) -o main.exe main.o tree_operations.o

tree_operations.o : tree_operations.c tree_operations.h main.h
	$(CC) $(CFLAGS) -c -o tree_operations.o tree_operations.c

main.o : main.c main.h tree_operations.h
	$(CC) $(CFLAGS) -c -o main.o main.c

clean :
	rm *.exe *.o *.png
