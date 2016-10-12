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
			printf("%15s", "allocated");
			int remaining = memory->size;
			memory->size = (request)*(-1);														// set block size to allocated
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
		printf("%15s", "No memory");
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

void myfree(void * ptr) {
	if(ptr == NULL) {
		printf("%15s", "Null pointer");
		return;
	}
	metadata * point = (metadata *) ptr;
	if(point == NULL) return;
	if(point->size >= 0) {
		printf("%15s", "Invalid Pointer");
		return;
	}
	point->size = abs(point->size);
	printf("%15s", "freed");
	mergeBlocks();
	return;
}
void mergeBlocks() {
	metadata *memory = (metadata *) memoryBlock;
	metadata *endmemory = (metadata *) (memoryBlock + memorySize);
	int merged = 0;
	while((metadata *)((char*)memory + memory->size) <= endmemory && merged == 0) {
		if(memory->size > 0){
			metadata* temp = memory;
			while(temp->size > 0){
				int hold = temp->size;
				temp->size = 0;
				temp = (metadata *)((char *)temp + hold);
			}
			memory->size = (char *)temp - (char *) memory;
			memory = (metadata *)((char *)temp + temp->size);
			merged = 1;
		}else{
			memory = (metadata *)((char *)memory + abs(memory->size));
		}
		/*
		if(ptr->size > 0) {
			metadata * ptr2 = ptr;
			while(ptr2->size > 0) {
				ptr2 = (metadata *) &ptr2 + ptr2->size;
				printf("\n%p - ", ptr2);
			}
			ptr->size = &ptr2 - &ptr;
			printf("%d - ", ptr->size);
			ptr = (metadata *) &ptr2 + ptr2->size;
			printf("%p", ptr);
		} else {
			ptr = (metadata *)(&ptr + ptr->size);
		}
		*/
	}
	return;
}
