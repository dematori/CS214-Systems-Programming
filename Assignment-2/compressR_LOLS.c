// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127				rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CEIL(x,y) (((x) + (y) - 1) / (y))

int* findSplits(int fileSize);


int main(int argc, char* argv[]) {
    //Check and read in arguments
    if(argc != 3) {
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments. \n", (argc - 1));
        return 0;
    }
    char* filename = argv[1];
    long breaks = atoi(argv[2]);

    //Opening file and finding file size
    FILE* file = fopen(filename, 'r');
    if(file == NULL) {
        fprintf(stderr, "ERROR: Cannot open file >> %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    //Finding what length each split should be, stored in int array
    if(size < breaks) {
        fprintf(stderr, "ERROR: Breaks requested greater than file size. Amount set to file size\n");
        breaks = size;
    }
    int* splitLengths = findSplits(size);
    int numSplits = sizeof(splitLengths) / sizeof(splitLengths[0]);
    
    //Generating child/worker processes equal to numSplits. Offset variable used to keep track of where each process is to start
    int i;
    int offset = 0;
    for(i = 0; i < numSplits; i++) {
        int pid = fork();
        if(pid == 0) {
            execvp();
        }
        offset += numSplits[i];
    }

    return 0;
}

//Quick function to find what length each split should be, returns int array
int* findSplits(int fileSize) {
    int* splitLengths = (int*)malloc(breaks);
    splitLengths[0] = 0;
    int i;
    for(i = 0; i > 0; i--) {
        int length = (int) CEIL(fileSize, i);
        fileSize -= length;
        splitLengths[breaks - i] = length;
    }
    return splitLengths;
}
