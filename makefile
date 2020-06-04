all: makeproject
makeproject: main.o
	gcc main.o -o makeproject -lsense
main.o: main.c
	gcc -g -c main.c
clean:
	rm -f *.o makeproject
