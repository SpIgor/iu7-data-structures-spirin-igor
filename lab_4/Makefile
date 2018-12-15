CC := gcc
CFLAGS := -std=c99 -Wall

array_realization.o : array_realization.c array_realization.h main.h generators.h
	$(CC) $(CFLAGS) -c -o array_realization.o array_realization.c

main.o: main.c main.h array_realization.h list_realization.h
	$(CC) $(CFLAGS) -c -o main.o main.c

main.exe : main.o array_realization.o generators.o list_realization.o
	$(CC) $(CFLAGS) -o main.exe main.o array_realization.o generators.o list_realization.o

generators.o : generators.c generators.h
	$(CC) $(CFLAGS) -c -o generators.o generators.c

list_realization.o : list_realization.c list_realization.h generators.h main.h
	$(CC) $(CFLAGS) -c -o list_realization.o list_realization.c

clean :
	rm *.exe *.o