// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127				rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#define CEIL(x,y) (((x) + (y) - 1) / (y))

int* findSplits(int fileSize, int breaks);

int main(int argc, char* argv[]) {
    //Check and read in arguments
    if(argc != 3) {
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments. \n", (argc - 1));
        return 0;
    }
    char* filename = argv[1];
    long breaks = atoi(argv[2]);

    //Recording runtime
    struct timeval t0;
    struct timeval t1;
    long elapsed;
    gettimeofday(&t0, 0);

    //Opening file and finding file size
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "ERROR: Cannot open file >> %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    //Finding what length each split should be, stored in int array
    if(size < breaks) {
        fprintf(stderr, "ERROR: Breaks requested greater than file size. Amount set to file size\n");
        breaks = size;
    }
    int* splitLengths = findSplits(size, breaks);
    int numSplits = breaks;
    
    //Generating child/worker processes equal to numSplits. Offset variable used to keep track of where each process is to start
    //Child process takes parameters {FILE* file, int offset, int length, int num, NULL}, each parameter as a string
    int i;
    int offset = 0;
    int pid = 1;
    for(i = 0; i < numSplits; i++) {
        pid = fork();
        if(pid == 0) {
            char* args[6];
            args[0] = "./bar";
            args[1] = filename;
            int tmp = offset;
            int len = 1;
            while(tmp != 0) {
                tmp /= 10;
                len++;
            }
            char tmp1[len];
            len = 1;
            tmp = i;
            while(tmp != 0) {
                tmp /= 10;
                len++;
            }
            char tmp2[len];
            len = 1;
            tmp = splitLengths[i];
            while(tmp != 0) {
                tmp /= 10;
                len++;
            }
            char tmp3[len];
            sprintf(tmp1, "%d", offset);
            sprintf(tmp2, "%d", splitLengths[i]);
            sprintf(tmp3, "%d", i);
            args[2] = tmp1;
            args[3] = tmp2;
            args[4] = tmp3;
            args[5] = NULL;
            execv(args[0], args);
        }
        offset += splitLengths[i];
    }

    while(pid = waitpid(-1, NULL, 0)) {
        if(errno == ECHILD) {
            break;
        }
    }

    gettimeofday(&t1, 0);
    elapsed = (t1.tv_sec-t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
    printf("Runtime for compressR_LOLS.c >> %ld microseconds \n", elapsed / 100);

    free(splitLengths);

    return 0;
}

//Quick function to find what length each split should be, returns int array
int* findSplits(int fileSize, int breaks) {
    int* splitLengths = (int*)malloc(sizeof(int) * breaks);
    splitLengths[0] = 0;
    int i;
    for(i = breaks; i > 0; i--) {
        int length = (int) CEIL(fileSize, i);
        fileSize -= length;
        splitLengths[breaks - i] = length;
    }
    return splitLengths;
}
