GCC = gcc
CFLAGS = -g -Wall -Wshadow
VAL = valgrind --tool=memcheck --leak-check=full --verbose

all: pa10

clean:
	rm -rf *o pa10

tree.o: tree.c tree.h
	$(GCC) $(CFLAGS) -c tree.c

pa10.o: pa10.c pa10.h
	$(GCC) $(CFLAGS) -c pa10.c

answer10.o: answer10.c pa10.h tree.h
	$(GCC) $(CFLAGS) -c answer10.c

pa10: pa10.o answer10.o
	$(GCC) $(CFLAGS) -o pa10 pa10.o answer10.o tree.o
