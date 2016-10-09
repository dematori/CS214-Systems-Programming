#include <stdio.h>
#include "mymalloc.h"

int main(){
    printf("ALLOCATING: 400\n");
    mymalloc(400);
    printf("ALLOCATING: 600\n");
    mymalloc(600);
    printf("ALLOCATING: 1000\n");
    mymalloc(1000);
    printf("ALLOCATING: 3000\n");
    mymalloc(3000);
    int i;
    for(i = 0; i < 5000; i++){
        printf("%d - ALLOCATING: 1\n", (i+1));
        mymalloc(1);
    }
   
    return 0;
}