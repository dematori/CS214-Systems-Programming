#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define malloc( x ) mymalloc(x, __FILE__, __LINE__);	// overriding the declaration of the original malloc()
#define free( x ) myfree(x, __FILE__, __LINE__);	// overriding the declaration of the original free()

#define MEM_SIZE 5000								// setting the default size of the memory allocation as 5000

typedef struct freelist{
	short size;										// 2 bytes -> positive is unallocated and negative is allocated
} metadata;											// 2 bytes <- TOTAL for overhead

void* mymalloc(size_t size, char* file, int line);	// function declaration of malloc()
void myfree(void *ptr, char* file, int line);		// function declaration of free()
void mergeBlocks();									// function declaration for merging all free blocks in the array.

#endif