CC := gcc

FLAGS := -std=c99 -Wall

main.exe : main.o calculate.o input_output.o
	$(CC) -o main.exe main.o calculate.o input_output.o -lm

input_output.o: input_output.c input_output.h define_file.h
	$(CC) $(CFLAGS) -c input_output.c

calculate.o : calculate.c calculate.h define_file.h input_output.h
	$(CC) $(CFLAGS) -c calculate.c

main.o : main.c define_file.h calculate.h input_output.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm *.o *.exe
