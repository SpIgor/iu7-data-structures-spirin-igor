CC := gcc

FLAGS := -Wall -Werror

ifeq ($(mode), memory_check)
	CFLAGS += -ggdb
endif


main.exe : main.o functions.o input_output.o
	$(CC) -o main.exe main.o functions.o input_output.o

input_output.o: input_output.c input_output.h functions.h
	$(CC) $(FLAGS) -c input_output.c

functions.o : functions.c functions.h define_file.h input_output.h
	$(CC) $(CFLAGS) -c functions.c

main.o : main.c define_file.h functions.h input_output.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm *.o *.exe

