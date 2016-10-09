#include <stdio.h>
#include "mymalloc.h"

void main(){
    printf("=====================\nALLOCATING: 400\n");
    mymalloc(400); 
    printf("ALLOCATING: 400\n");
    mymalloc(400);
    printf("ALLOCATING: 200\n");
    mymalloc(200);
    printf("ALLOCATING: 4000\n");
    mymalloc(4000);
/**    int i;
    for(i = 0; i <= 500; i++){
        printf("%d - ALLOCATING: 1\n", (i+1));
        mymalloc(1);
    }
**/
    printf("=====================\n");
}