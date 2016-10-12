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

    // -- WORKLOAD C ---
    printf("\n==========WORKLOAD C==========\n");
    printf("-Randomly allocating or freeing 1 byte pointers (3000 times each)\n");

    for(i = 0; i < 6000; i++){
        int choice = rand() % 2;
        if(choice == 1){
            
        }
    }
}