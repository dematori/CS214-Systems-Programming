#include <stdio.h>
#include <time.h>
#include "mymalloc.h"



void main(){
    // --- WORKLOAD A ---
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
        a[i] = (char *) mymalloc(1);
    }
    printf("\n-Freeing 1 byte pointers - 3000 times\n");
    printf("Freeing a[100]");
    myfree(a[100]);
    printf("\n %d - %p\n", ((metadata*)a[99])->size, a[99]);
    printf("\n %d - %p\n", ((metadata*)a[100])->size, a[100]);
    printf("\n %d - %p\n", ((metadata*)a[101])->size, a[101]);
    printf("\n %d - %p\n", ((metadata*)a[102])->size, a[102]);
    printf("\n %d - %p\n", ((metadata*)a[103])->size, a[103]);
    printf("\n %d - %p\n", ((metadata*)a[104])->size, a[104]);
    printf("Freeing a[101]");
    myfree(a[101]);
    printf("\n %d - %p\n", ((metadata*)a[99])->size, a[99]);
    printf("\n %d - %p\n", ((metadata*)a[100])->size, a[100]);
    printf("\n %d - %p\n", ((metadata*)a[101])->size, a[101]);
    printf("\n %d - %p\n", ((metadata*)a[102])->size, a[102]);
    printf("\n %d - %p\n", ((metadata*)a[103])->size, a[103]);
    printf("\n %d - %p\n", ((metadata*)a[104])->size, a[104]);
    printf("Freeing a[102]");
    myfree(a[103]);
    printf("\n %d - %p\n", ((metadata*)a[99])->size, a[99]);
    printf("\n %d - %p\n", ((metadata*)a[100])->size, a[100]);
    printf("\n %d - %p\n", ((metadata*)a[101])->size, a[101]);
    printf("\n %d - %p\n", ((metadata*)a[102])->size, a[102]);
    printf("\n %d - %p\n", ((metadata*)a[103])->size, a[103]);
    printf("\n %d - %p\n", ((metadata*)a[104])->size, a[104]);
    printf("Freeing a[103]");
    myfree(a[102]);
    printf("\n %d - %p\n", ((metadata*)a[99])->size, a[99]);
    printf("\n %d - %p\n", ((metadata*)a[100])->size, a[100]);
    printf("\n %d - %p\n", ((metadata*)a[101])->size, a[101]);
    printf("\n %d - %p\n", ((metadata*)a[102])->size, a[102]);
    printf("\n %d - %p\n", ((metadata*)a[103])->size, a[103]);
    printf("\n %d - %p\n", ((metadata*)a[104])->size, a[104]);

            /*
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
    */
}