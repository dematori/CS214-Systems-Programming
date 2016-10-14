#include <stdio.h>
#include <time.h>
#include "mymalloc.h"

void workloadA() {
    //printf("\n==========WORKLOAD A==========\n");
    char* a[3000];
    int i = 0;
    int lineSplitter = 8;
    //printf("-Allocating 1 byte pointers - 3000 times");
    for(i = 0; i < 3000; i++){
        /*if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));*/
        a[i] = (char *) malloc(1);
    }
    
    for(i = 0; i < 3000; i++){
        /*if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));*/
        free(a[i]);
    }
}

void workloadB() {
    //printf("\n==========WORKLOAD B==========\n");
    //printf("-Allocating 1 byte pointer - 1 time\n\t");
    //printf("%7s - ", "b");
    int i;
    int lineSplitter = 8;
    char* b = (char *) malloc(1);
    //printf("\n-Freeing 1 byte pointer - 3000 times");    
    for(i = 0; i < 3000; i++){
        /*if((i)%lineSplitter == 0){
            printf("\n\t");
        }
        printf("%7d - ", (i+1));*/
        free(b);
    }
    //printf("\n");
}

void workloadC() {
    //printf("\n==========WORKLOAD C==========\n");
    //printf("-Randomly allocating or freeing 1 byte pointers (3000 times each)\n");

    int mallocCount;
    int freeCount;

    int front = 0;
    int rear = -1;
    char * arr[3000];
    memset(&arr[0], 0, sizeof(arr));

    mallocCount = 0;
    freeCount = 0;
    srand(time(NULL));

    while(mallocCount < 3000 && freeCount < 3000) {
		int choose;
		choose = rand();
		if(choose % 2 == 0) {
			arr[rear + 1] = (char *) malloc(1);
			if(arr[rear + 1] != NULL) {
				rear++;
				mallocCount++;
			}
			//printf("Malloc Count: %d\n", rear - front + 2);
		}
		else {
			free(arr[front]);
			freeCount++;
			//printf("Free Count: %d\n", rear - front + 2);
			if(mallocCount > front) {
				front++;
			}
		}
    }
    while(mallocCount < 3000) {
	    arr[rear + 1] = (char *) malloc(1);
	    mallocCount++;
	    if(arr[rear + 1] != NULL) {
			rear++;
	    }
	    //printf("Malloc Count: %d\n", rear - front + 2);
    }
    while(front < rear) {
	    free(arr[front]);
	    freeCount++;
	    //printf("Free Count: %d\n", rear - front + 2);
	    if(mallocCount > front) {
		    front++;
	    }
    }
    //printf("Total mallocs done: %d\n", mallocCount);
    //printf("Total frees done: %d\n", freeCount);
 }

void workloadD() {
	//printf("\n==========WORKLOAD D==========\n");
	int mallocCount;
	int freeCount;
	
	int front = 0;
	int rear = -1;
	char * arr[3000];
	memset(&arr[0], 0, sizeof(arr));

	mallocCount = 0;
	freeCount = 0;
	srand(time(NULL));

	while(mallocCount < 3000 && freeCount < 3000) {
		int choose;
		choose = rand();
		int size;
		size = rand();
		if(choose % 2 == 0) {
			arr[rear + 1] = (char *) malloc(size % 5000);
			//printf("Attempting to malloc: %d\n", size % 5000);
			//printf("Malloced count: %d\n", rear - front + 2);
			if(arr[rear + 1] != NULL) {
				rear++;
			}
			mallocCount++;
		}
		else {
			free(arr[front]);
			freeCount++;
			//printf("Malloced count: %d\n", rear - front + 2);
			if(mallocCount > front) {
				front++;
			}
		}
	}
	while(mallocCount < 3000) {
		int size = rand();
		arr[rear + 1] = (char *) malloc(size % 5000);
		//printf("Attempting to malloc: %d\n", size % 5000);
		//printf("Malloced count: %d\n", rear - front + 2);
		if(arr[rear + 1] != NULL) {
			rear++;
		}
		mallocCount++;
	}
	while(front < rear) {
		free(arr[front]);
		freeCount++;
		//printf("Malloced count: %d\n", rear - front + 2);
		if(mallocCount > front) {
			front++;
		}
	}
	//printf("Total mallocs done: %d\n", mallocCount);
	//printf("Total frees done: %d\n", freeCount);
}

void workloadE() {
	//printf("\n==========WORKLOAD E==========\n");
	int i = 0;
	char * arr[1666];
	for(i = 0; i < 1666; i++) {
		arr[i] = (char *) malloc(1);
		//printf("%d\n", i);
	}
	for(i = 0; i < 1666; i += 2) {
		free(arr[i]);
	}
	char * test = (char *) malloc(2);
	//printf(test);
	char * test2 = (char *) malloc(1);
	//printf(test2);
	for(i = 0; i < 1666; i++) {
		free(arr[i]);
	}
	free(test2);
}

void workloadF() {
	//printf("\n==========WORKLOAD F==========\n");
	int i = 0;
	for(i = 0; i < 3000; i++) {
		char * a = (char *) malloc(1);
		free(a);
	}
}

void main(){
	int i = 0;
	struct timeval t0;
	struct timeval t1;
	long elapsed;
	gettimeofday(&t0, 0);
	for(i = 0; i < 100; i++) {
		workloadA();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWorkload A:\nmalloc 1 byte 3000 times, then free 1 byte 3000 times");
	printf("\nWorkload A average runtime: %ld microseconds\n", elapsed/100);

	gettimeofday(&t0, 0);	
	for(i = 0; i < 100; i++) {
		workloadB();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWorkload B:\nmalloc 1 byte, then free 1 byte 3000 times");
	printf("\nWorkload B average runtime: %ld microseconds\n", elapsed/100);

	gettimeofday(&t0, 0);
	for(i = 0; i < 100; i++) {
		workloadC();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWordload C:\nrandomly malloc or free 1 byte 6000 times with a 3000 limit for malloc and free the rest");
	printf("\nWorkload C average runtime: %ld microseconds\n", elapsed/100);

	gettimeofday(&t0, 0);
	for(i = 0; i < 100; i++) {
		workloadD();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWorkload D:\nrandomly malloc or free randomly sized bytes 6000 times with a 3000 limit for malloc and free the rest");
	printf("\nWorkload D average runtime: %ld microseconds\n", elapsed/100);

	gettimeofday(&t0, 0);
	for(i = 0; i < 100; i++) {
		workloadE();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWorkload E:\nmalloc 1 byte 3000 times, free every other allocation then try to malloc 2 bytes then malloc 1 byte");
	printf("\nWorkload E average runtime: %ld microseconds\n", elapsed/100);

	gettimeofday(&t0, 0);
	for(i = 0; i < 100; i++) {
		workloadF();
	}
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//printf("\nWorkload F:\nmalloc 1 byte then free that 1 byte, then repeat");
	printf("\nWorkload F average runtime: %ld microseconds\n\n", elapsed/100);

	return;
}

