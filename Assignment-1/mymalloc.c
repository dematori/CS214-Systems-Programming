#include "mymalloc.h"

static char memoryBlock[5000];				                									// 5000 * 2 bytes
int dataSize = sizeof(metadata);																// 2 bytes
int memorySize = sizeof(memoryBlock);															// 10000 bytes

void* mymalloc(size_t size){
	if(size <= 0){																				// allocating 0 space does nothing
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
		}else if(request <= abs(memory->size) && memory->size > 0){								// if request size > unallocated block size
			printf("allocated\n");
			int remaining = memory->size;
		memory->size = (request)*(-1);															// set block size to allocated
			remaining += memory->size;															// gets remaining free space and initializes the next block to unallocated
			retMem = memory;
			memory = (metadata*)((char*)memory + (abs(memory->size)));							// jumps to end of newly allocated memory
			memory->size = remaining;															// sets next empty block to remaining size avaliable
			allocated = 1;
		}else{
			break;
		}
	}
	if(allocated == 0){
		printf("Not enough memory to be allocated\n");
		return memory;
	}
	/**
	int i;
	for(i = 0; i < memorySize; i++){
		printf("[%c]", memoryBlock[i]);
	}
	printf("\n");
	**/
	return retMem;
}

void myfree(void * ptr){
	metadata * point = (metadata *)ptr;
	point->size = abs(point->size);
	mergeBlocks(point);
	return;
}

void mergeBlocks(metadata * point) {
	if (point->size == 0){
		printf("Pointer does not exist\n");
		return;
	}
	metadata *memory = (metadata *) memoryBlock;
	metadata *endmemory = (metadata *) (memoryBlock + memorySize);
	metadata* next1 = (metadata*)((char*)memory + (abs(memory->size)));
	metadata* next2 = (metadata*)((char*)next1 + (abs(next1->size)));
	metadata* next3 = (metadata*)((char*)next2 + (abs(next2->size)));
	int freed = 0;
	while(memory <= endmemory && freed == 0){
		while(next1 < endmemory && next2 < endmemory && freed == 0){
			if(memory == point && next1->size > 0){
				memory->size = abs(memory->size) + next1->size;					// START -> [-3][+5]... --> [8][]...
				freed = 1;
				break;
			}else if(next1 == point && next2->size > 0){
				next1->size = abs(next1->size) + next2->size;					// START -> ...[-3][-4][5]... --> ...[-3][9][]...
				next2->size = 0;
				if(memory->size > 0){
					memory->size += abs(next1->size);							// START -> ...[3][-9][0]... --> ...[12][][]...
					next1->size = 0;
				}
				freed = 1;
			}else if(next1 == point && memory->size > 0){
				if(next2->size > 0){
					next1->size = abs(next1->size) + next2->size;				// START -> ...[3][-4][5]... --> ...[3][9][]...
					next2->size = 0;
				}
				memory->size += abs(next1->size);								// START -> ...[3][-9][-3]... --> ...[12][][-3]...
				freed = 1;
			}else if(next2 == point && next1->size > 0 && next3 == endmemory){
				next1->size += abs(next2->size);								// ...[3][-4] <- END --> ...[7][[]
				next2->size = 0;
				freed = 1;
			}else{
				memory = next1;
				next1 = (metadata*)((char*)memory + (abs(memory->size)));
				next2 = (metadata*)((char*)next1 + (abs(next1->size)));
				next3 = (metadata*)((char*)next2 + (abs(next2->size)));
			}
		}
	}
	if(freed == 1){
		printf("freed\n");
	}
	/**
	int i;
	for(i = 0; i < memorySize; i++){
		printf("[%c]", memoryBlock[i]);
	}
	printf("\n");
	**/
	return;                                                                                                                                              
}
	
