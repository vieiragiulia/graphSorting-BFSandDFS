CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99 -pedantic
OBJ = main.o List.o Graph.o
DEPS = List.h Graph.h
VFLAGS = -v --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./tp1 input.txt output.txt
TIMED_RUN = time ./tp1 

all: tp1

tp1: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tp1

valgrind:
	valgrind $(VFLAGS) $(EXEC)

run:
	$(EXEC)

timed:
	$(TIMED_RUN)

