#include "mymalloc.h"

static char memoryBlock[MEM_SIZE];											// 5000 * 2 bytes
int dataSize = sizeof(metadata);											// 2 bytes
int memorySize = sizeof(memoryBlock);										// 10000 bytes

/*	
*	mymalloc() is a custom implementation of the malloc() method in C.
*	By utilizing a character array as a custom memory size, we allocate according to a custom overhead
*	The purpose of this method  is to replicate the malloc() method in the given character array.
*	parameters: size - size in bytes that the system needs to allocate into the character array
*/
void* mymalloc(size_t size){
	if(size <= 0){															// allocating 0 or negative space returns nothing
		//printf("ERROR: Cannot allocated negative or 0 bytes");			// error message for user to see, if uncommented
		return;
	}
	size_t request = size + dataSize;										// setting the size to be added with the request size and the overhead
	metadata *memory = (metadata *) memoryBlock;							// initializing the first pointer to the start of the memory array
	if(memory->size == 0){													// if the memory is untouched for the allcoation then ...
		memory->size = memorySize;											// ... set the initial avaliable size as the size of the memory block
	}
	metadata *endmemory = (metadata *) (memoryBlock + memorySize);			// setting the last address of the array so that there will be no overflow
	metadata *retMem;														// declaring the return address for other program to point to the allocation
	int allocated = 0; 														// declaring and initializing allocation flag
	while(memory < endmemory && allocated == 0){							// as long as the pointer is not past the end pointer of the memory and if the allocated is equal to 0
		if(memory->size < 0){												// if the block is allocated (NOTE: see header to see how program sees if a block is allocated), then ...
			memory = (metadata*)((char*)memory + (abs(memory->size)));		// --- jump to next block
		}else if(request <= abs(memory->size) && memory->size > 0){			// if request size > unallocated block size
			//printf("%15s", "allocated");									// notify for user if allocated, if uncommented
			int remaining = memory->size;									// finding the remaining space after allocating the size and the overhead
			memory->size = (request)*(-1);									// setting the block to be allocated with the size and the overhead bytes (NOTE: see header to see how program sees if a block is allocated)
			remaining += memory->size;										// gets remaining free space and initializes the next block to unallocated
			retMem = memory;												// setting the return memory pointer to the current memory pointer
			memory = (metadata*)((char*)memory + (abs(memory->size)));		// jumps to end of newly allocated memory
			memory->size = remaining;										// sets next empty block to remaining size avaliable since the previous block is no longer unallocated
			allocated = 1;													// setting flag to reflect the allocation
		}else{
			break;															// if everything above does not occur or the memory faults and points to an incorrect location, then break
		}
	}
	if(allocated == 0){														// if the allocation flag is unchanged from intial state, then ...
		//printf("%15s", "No memory");										// ... notify the user that there is no memory left to be allocated, if uncommented
		return memory;														// ... return the beginning of the memory pointer which is the end of the memory since there is are no changes.
	}
	return retMem;															// return the address of allocation for other program to use
}

/*	
*	myfree() is a custom implementation of the free() method in C.
*	By utilizing a character array as a custom memory, we free according to the given pointer
*	The purpose of this method is to replicate the free() method in the given character array
*	parameters: *ptr - pointer to the location in the character array
*/	
void myfree(void *ptr) {
	if(ptr == NULL) {														// if the pointer points to nothing, then ...
		//printf("%15s", "ERROR: Null pointer");							// ... NULL POINTER error message for user to see, if uncommented
		return;
	}
	metadata * point = (metadata *) ptr;									// else ptr is set as the local pointer
	if(point == NULL) return;												// if for some reason that the local pointer is null, then return nothing
	if(point->size >= 0) {													// if point is greater or equal to 0, then ...
		//printf("%15s", "ERROR: Invalid Pointer");							// ... INVALID POINTER error meessage for user to see if uncommented
		return;
	}
	point->size = abs(point->size);											// setting the size of the allocation to positive to show that it is now unallocated
	//printf("%15s", "freed");												// notification telling the user that the memory has been freed, if uncommented
	mergeBlocks();															// calling the mergeBlocks() method
	return;
}

/*	
*	mergeBlocks() is a method to find all the adjacent free blocks and merges them together as a sum
*	and sets the merged blocks to 0 and only setting the very first block as the sum of all blocks freed 
*	after it until the next allocated block.
*/
void mergeBlocks() {
	metadata *ptr = (metadata *) memoryBlock;								// setting the starting pointer at the intial location of the character array
	metadata *end = (metadata *) (memoryBlock + memorySize);				// setting the ending pointer at the final location of the character array
	while(ptr < end && ptr->size != 0) {									// as long as the current pointer is before the final pointer and that the size of the pointer is not equal to 0
		if(ptr->size > 0){													// if the block size is greater than 0 (unallocated), then ...
			metadata* temp = ptr;											// ... set the temporary pointer as the current pointer
			int hold = 0;													// declaring and intializing the running sum of the unallocated spaces
			while(temp->size > 0){											// as long as the temporary pointer points to a size greater than 0
				int increment = temp->size;									// keeping the size as a temporary incrementer to get to the next memory block
				hold += temp->size;											// adding the temporary size to the running sum
				temp->size = 0;												// setting the temporary pointer size to 0 so no other pointer can point to it
				temp = (metadata *)((char *)temp + increment);				// incrementing to the next block that is either allocated or unallocated.
			}
			ptr->size = hold;												// setting the current pointer to the running sum so all unallocated blocks are summed to one block
			break;															// finished merging the memory block that was just freed
		}else{
			ptr = (metadata *)((char *)ptr + abs(ptr->size));				// incrementing to the next memory block since current block is allocated and cannot be merged with free blocks
		}
	}
	return;
}