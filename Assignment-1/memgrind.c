#include <stdio.h>
#include "mymalloc.h"

void main(){
    char* a[3000];
    int x = 0;
    printf("Allocating 1 byte pointers - 3000 times\n");
    for(x = 0; x < 3000; x++){
        printf("%d - ", (x+1));
        a[x] = (char*) mymalloc(1);
    }
    printf("Freeing 1 byte pointers - 3000 times\n");
    for(x = 0; x < 3000; x++){
        printf("%d - ", (x+1));
        myfree(a[x]);
    }
}