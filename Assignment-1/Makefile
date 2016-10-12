output: memgrind.o mymalloc.o
	gcc memgrind.o mymalloc.o -o output

memgrind: memgrind.c
	gcc -c memgrind.c

mymalloc: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

clean:
	rm *.o output

