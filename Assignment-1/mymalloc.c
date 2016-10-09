#include "mymalloc.h"

int dataSize = sizeof(metadata);								// 2 bytes
static char myblock[MEM_SIZE * dataSize];						// 5000 * 2 bytes
int memorySize = sizeof(myblock);								// 10000 bytes
static metadata *memory = (metadata*) myblock;					// setting char array as memory
static int firstRun = -1;										// first run indicator


void* mymalloc(size_t size, char* file, int line){
	if(firstRun == -1){
		memory->size = memorySize - dataSize;					// positive size = unallocated
																// negative size = allocated
		firstRun = 0;											// no longer first run
	}
	if(size <= 0){
		return memory;											// no changes in memory allocation
	}
	metadata *current = memory;
	metadata *tail = (metadata *) ((char *)memory + memorySize);
	// --- checking if there is room to allocate requested space to memory
	while(current->size != 0 && current != tail){
		if(current->size >= size){
			break;
		}else{
			current = (metadata *) ((char *)current + dataSize + (abs(current->size) & ~1));
			if(tail < current){
				printf("Not enough memory to be allocated.\n");
				return 0;
			}
		}
	}
	// --- allocating requested space in memory since there is room somewhere
	metadata *limit = (metadata *)((char *)current + dataSize + size);
	if(tail - limit < 0){
		printf("Not enough memory to be allocated./n");
		return 0;
	}
	metadata *temp = (metadata *)((char *) current + dataSize + abs(current->size));
	if(temp == tail){
		limit->size = (int)((char *)head + memorySize - (char *)limit - dataSize);
	}else{
		if((int) ((char *)temp - (char *)current - size - dataSize)){
			limit->size = (int) ((char *)temp - (char *)current - size - 2*dataSize);
		}
	}
	if(limit->size == 0){
		size += dataSize;
	}
	current->size = 0-size;
	return current + 1;
}

void myfree(void * ptr){
	
}


