CC := gcc
CFLAGS := -std=c99 -Wall -Werror

main.exe : main.o string_operations.o struct_operations.o sorts.o time.o
	$(CC) $(CFLAGS) -o main.exe main.o string_operations.o struct_operations.o sorts.o time.o

main.o : main.c string_operations.h struct_operations.h main.h struct.h
	$(CC) $(CFLAGS) -c main.c

struct_operations.o : struct_operations.c struct_operations.h struct.h string_operations.h
	$(CC) $(CFLAGS) -c struct_operations.c

string_operations.o : string_operations.c string_operations.h struct.h
	$(CC) $(CFLAGS) -c string_operations.c

sort.o : sorts.c sorts.h struct.h struct_operations.h time.h
	$(CC) $(CFLAGS) -c sorts.c

clean :
	rm *.o *.exe