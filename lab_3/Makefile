CC := gcc
CFLAGS := -std=c99 -Wall

time.o : time.c time.h
	$(CC) $(CFLAGS) -c -o time.o time.c

array_operations.o : array_operations.c array_operations.h main.h time.o
	$(CC) $(CFLAGS) -c -o array_operations.o array_operations.c time.o

list_operations.o : list_operations.c list_operations.h time.o
	$(CC) $(CFLAGS) -c -o list_operations.o list_operations.c time.o

main.o : main.c *.h
	$(CC) $(CFLAGS) -c -o main.o main.c

main.exe : main.o array_operations.o list_operations.o time.o
	$(CC) $(CFLAGS) -o main.exe main.o array_operations.o list_operations.o time.o


clean :
	rm *.o *.exe