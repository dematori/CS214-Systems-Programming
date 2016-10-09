#include <stdio.h>
#include "mymalloc.h"

void main(){
    printf("=====================\nALLOCATING: 400\n");
    int i;
    for(i = 0; i < 5; i++){
        printf("%d - ALLOCATING: 1\n", (i+1));
        mymalloc(1);
    }
    printf("=====================\n");
}