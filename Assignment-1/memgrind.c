#include <stdio.h>
#include <time.h>
#include "mymalloc.h"

void main(){
    // --- WORKLOAD A ---
   /* 
    printf("\n==========WORKLOAD A==========\n");
    char* a[3000];
    int i = 0;
    int lineSplitter = 8;
    printf("-Allocating 1 byte pointers - 3000 times");
    for(i = 0; i < 3000; i++){
        if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));
        a[i] = (char*) mymalloc(1);
    }
    printf("\n-Freeing 1 byte pointers - 3000 times");
    for(i = 0; i < 3000; i++){
        if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));
        myfree(a[i]);
    }

    // --- WORKLOAD B ---
    printf("\n==========WORKLOAD B==========\n");
    printf("-Allocating 1 byte pointer - 1 time\n\t");
    printf("%7s - ", "b");
    char* b = (char *) mymalloc(1);
    printf("\n-Freeing 1 byte pointer - 3000 times");    
    for(i = 0; i < 3000; i++){
        if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));
        myfree(b);
    }
    printf("\n");
    */
    // -- WORKLOAD C --
    printf("\n==========WORKLOAD C==========\n");
    printf("-Randomly allocating or freeing 1 byte pointers (3000 times each)\n");
    
    int mallocCount;
    int freeCount;

    int front = 0;
    int rear = -1;
    char * arr[500];
    memset(&arr[0], 0, sizeof(arr));

    mallocCount = 0;
    freeCount = 0;
    srand(time(NULL));

    while(mallocCount < 500 && freeCount < 500) {
	int choose;
	choose = rand();
	if(choose % 2 == 0) {
		arr[rear + 1] = (char *) mymalloc(1);
		if(arr[rear + 1] != NULL) {
			rear++;
			mallocCount++;
		}
		printf("Malloc Count: %d\n", rear - front + 2);
	}
	else {
		myfree(arr[front]);
		freeCount++;
		printf("Free Count: %d\n", rear - front + 2);
		if(mallocCount > front) {
			front++;
		}
	}
    }
    while(mallocCount < 500) {
	    arr[rear + 1] = (char *) mymalloc(1);
	    mallocCount++;
	    if(arr[rear + 1] != NULL) {
		rear++;
	    }
	    printf("Malloc Count: %d\n", rear - front + 2);
    }
    while(front < rear) {
	    myfree(arr[front]);
	    freeCount++;
	    printf("Free Count: %d\n", rear - front + 2);
	    if(mallocCount > front) {
		    front++;
	    }
    }

    int i = 0;
    for(i = 0; i < 500; i++) {
	metadata * temp = (metadata *) arr[i];
	printf("%d\n", temp->size);
    }

	
    printf("Total mallocs done: %d\n", mallocCount);
    printf("Total frees done: %d\n", freeCount);
}
