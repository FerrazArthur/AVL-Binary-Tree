CC = gcc

CFLAGS = -g -Wall 

DEPS = AVL.h

example: Example.o AVL.o
	$(CC) $(CFLAGS) -o example Example.o AVL.o

Example.o: Example.c $(DEPS)
	$(CC) $(CFLAGS) -c -o Example.o Example.c

AVL.o: AVL.c
	$(CC) $(CFLAGS) -c -o AVL.o AVL.c

clean:
	\rm *.o
