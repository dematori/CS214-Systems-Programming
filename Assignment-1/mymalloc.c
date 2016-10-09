#include "mymalloc.h"

static char memoryBlock[5000];				                		// 5000 * 2 bytes
int dataSize = sizeof(metadata);									// 2 bytes
int memorySize = sizeof(memoryBlock);								// 10000 bytes

void* mymalloc(size_t size){
	if(size <= 0){												// allocating 0 space does nothing
		return;	
	}
	size_t request = size + dataSize;
	metadata *memory = (metadata *) memoryBlock;
	if(memory->size == 0){
		memory->size = memorySize;
	}
	metadata *endmemory = (metadata *) (memoryBlock + memorySize);
	metadata *retMem;
	int allocated = 0; 
	while(memory < endmemory && allocated == 0){
		if(memory->size < 0){
			memory = (metadata*)((char*)memory + (abs(memory->size)));							// if block is allocated, jump to next block
		}else if(request <= abs(memory->size) && memory->size > 0){	// if request size > unallocated block size
			int remaining = memory->size;
			memory->size = (request)*(-1);							// set block size to allocated
			remaining += memory->size;								// gets remaining free space and initializes the next block to unallocated
			retMem = memory;
			memory = (metadata*)((char*)memory + (abs(memory->size)));									// jumps to end of newly allocated memory
			memory->size = remaining;								// sets next empty block to remaining size avaliable
			allocated = 1;
		}
	}
	if(allocated == 0){
		printf("Not enough memory to be allocated\n");
		return;
	}
	printf("--Memory: \n");
	int i;
	for(i = 0; i < memorySize; i++){
		printf("[%c]", memoryBlock[i]);
	}
	printf("\n");
	return retMem;
}

void myfree(void * ptr){
	return;
}
