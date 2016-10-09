#include <stdio.h>
#include "mymalloc.h"

void main(){
    int input;
    int repeat;
    scanf("%d %d", &input, &repeat);
    printf("=====================\n");
    int i;
    for(i = 0; i < repeat; i++){
        printf("%d - ALLOCATING: %d\n", (i+1), input);
        mymalloc(input);
    }
    printf("=====================\n");
    return;
}