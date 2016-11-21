// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127              rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CEIL(x,y) (((x) + (y) - 1) / (y))

int *findSplits(int fileSize);
void startCompression(int *splitLength);
void compress(char* str, int fileNum, int* splitLength);
FILE *generateOutFile(int fileNum);

char *filename;
char *fileString;
int breaks;
int firstFile = 0;

int main(int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments.\n", (argc-1));
        return 0;
    }
    filename = argv[1];
    breaks = atoi(argv[2]);
    FILE *file = fopen(filename, "r");
    if(file == NULL){
       fprintf(stderr, "ERROR: Cannot open file >> %s\n", filename);
       exit(1);
    }
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fileString = (char *) malloc(fileSize + 1);
    fread(fileString, fileSize, 1, file);
    fclose(file);
    fileString[fileSize] = '\0';
    int *parts = findSplits(fileSize);
    startCompression(parts);
    return 0;
}

int *findSplits(int fileSize){
    if(fileSize < breaks){
        printf("WARNING: Requested number of compressed chunks exceeds the length of uncompressed.\n");
        printf("         Parts that resulted in no compressions are automatically removed.\n");
        breaks = fileSize;
    }
    int *splits = (int *) malloc(sizeof(int) * breaks);
    int i;
    for(i = breaks; i > 0; i--){
        int length = (int) CEIL(fileSize, i);
        fileSize -= length;
        splits[breaks-i] = length;
    }
    return splits;
}

void startCompression(int *splitLength){
    int currentIndex = 0;
    int i;
    for(i = 0; i < breaks; i++){
        int tempLen = splitLength[i];
        //printf("           INDEX: %d\n", currentIndex);
        char compStr[tempLen + 1];
        memcpy(compStr, &fileString[currentIndex], tempLen+1);
        compStr[tempLen] = '\0';
        //printf("        SPLITSTR: %s\n", compStr);
        compress(compStr, i, splitLength);
        currentIndex += tempLen;
    }
}

void compress(char *src, int fileNum, int* splitLength){
    FILE *output = generateOutFile(fileNum);
    int len = strlen(src);
    int i;
    char currCounting = src[0];
    int counter = 1;
    for(i = 1; i <= len; i++){
        if(!isalpha(currCounting)){
            currCounting = src[i];
        }else{
            if(currCounting == src[i]){
                counter++;
            }else{
                if(counter == 1){
                    fprintf(output, "%c", currCounting);
                }else if(counter == 2){
                    fprintf(output, "%c%c", currCounting, currCounting);
                }else{
                    fprintf(output, "%d%c", counter, currCounting);
                }
                currCounting = src[i];
                counter = 1;
            }
        }
    }
    fclose(output);
}

FILE *generateOutFile(int fileNum){
    if(firstFile == 0){
        int fileLen = strlen(filename);
        int q;
        for(q = 0; q < fileLen; q++){
            if(filename[q] == '.'){
                filename[q] = '_';
            }
        }
        firstFile = 1;
    }
    char *outname = (char*) malloc(sizeof(filename) + sizeof(char) * 6 + sizeof(int));
    sprintf(outname, "%s_LOLS%d", filename, fileNum);
    remove(outname);
    FILE *fp;
    fp = fopen(outname, "a");
    return fp;
}