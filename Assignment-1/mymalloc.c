#include "mymalloc.h"

static char memoryBlock[10000];				                		// 5000 * 2 bytes
int dataSize = sizeof(metadata);									// 2 bytes
int memorySize = sizeof(memoryBlock);								// 10000 bytes

void* mymalloc(size_t size){
	int request = size*dataSize;
	printf("--Size to be allocated: %d \n", request);
	printf("--Data size: %d\n", dataSize);
	printf("--Memory size: %d \n", memorySize);
	printf("--Old Memory: \n");
	int i;
	for(i = 0; i < memorySize; i++){
		printf("[%c]", memoryBlock[i]);
	}
	if(request <= 0){												// allocating 0 space does nothing
		return;	
	}
	metadata *memory = (metadata *) memoryBlock;
	if(memory->size == 0){
		memory->size = memorySize;
	}
	printf("\n--Current memory size: %d\n", memory->size);									
	metadata *endmemory = (metadata *) (memoryBlock + memorySize);
	printf("--Memory pointer: %\n", memory);
	printf("--End memory pointer: %p\n", endmemory);
	int allocated = 0; 
	while(memory < endmemory && allocated == 0){
		if(memory->size < 0){
			memory += abs(memory->size);							// if block is allocated, jump to next block
		}else if(request <= abs(memory->size) && memory->size > 0){	// if request size > unallocated block size
			int remaining = memory->size;
			memory->size = (request)*(-1);							// set block size to allocated
			remaining += memory->size;								// gets remaining free space and initializes the next block to unallocated
			memory += abs(memory->size);					// jumps to end of newly allocated memory
			memory->size = remaining;								// sets next empty block to remaining size avaliable
			printf("--Remaining memory: %d\n", remaining);
			allocated = 1;
		}else{
			memory += memory->size + dataSize;
		}
	}
	if(allocated == 0){
		printf("Not enough memory to be allocated\n");
	}
	printf("--New Memory: \n");
	for(i = 0; i < memorySize; i++){
		printf("[%c]", memoryBlock[i]);
	}
	printf("\n");
	return;
}

void myfree(void * ptr){
	
}
