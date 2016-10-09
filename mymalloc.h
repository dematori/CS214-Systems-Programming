#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define malloc( x ) mymalloc(x, __FILE__,__LINE__)
#define free( x ) myfree(x,__FILE__,__LINE__)

#define MEM_SIZE 5000

typedef struct freelist{
	short size;					// 2 bytes
} metadata;						// 4 bytes <- TOTAL

void *mymalloc(size_t size);
void myfree(void *ptr);

#endif
