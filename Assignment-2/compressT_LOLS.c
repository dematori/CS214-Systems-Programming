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
void compress(char* str, int fileNum);
char *filename;
char *fileString;
int breaks;

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
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fileString = (char *) malloc(fileSize + 1);
    fread(fileString, fileSize, 1, file);
    fclose(file);
    fileString[fileSize] = 0;
    int *splitLength = findSplits(fileSize);
    startCompression(splitLength);
    return 0;
}

int *findSplits(int fileSize){
    if(fileSize < breaks){
        printf("WARNING: Requested number of compressed chunks exceeds the length of uncompressed.\n");
        printf("         There will be a lot of empty files.\n");
    }
    int *splitLength = (int *) malloc(breaks);
    splitLength[0] = 0;
    int i;
    for(i = breaks; i > 0; i--){
        int length = (int) CEIL(fileSize, i);
        fileSize -= length;
        splitLength[breaks-i] = length;
    }
    return splitLength;
}

void startCompression(int *splitLength){
    int currentIndex = 0;
    int i;
    for(i = 0; i < breaks; i++){
        char compStr[splitLength[i] + 1];
        memcpy(compStr, &fileString[currentIndex], splitLength[i]);
        compStr[splitLength[i]] = '\0';
        //printf("%2d - %2d - %s\n", currentIndex, splitLength[i], compStr);
        compress(compStr, i);
        currentIndex += splitLength[i];
    }
}

void compress(char *src, int fileNum){
    //generateOutFile(fileNum);
    int counter = 0;
    int len = strlen(src);
    printf(">> COMPRESSING << %2d - %s\n", fileNum, src);
    char *temp = (char *) malloc(sizeof(char) * len);
    char *dest = (char *) malloc(sizeof(src));
    int i, j = 0, k;
    char currCounting = src[0];
    for(i = 1; i < len; i++){
        if(isalpha(currCounting)){
            if(currCounting == src[i]){
                counter++;
                printf("%2d >> char - %c - %d\n", fileNum, currCounting, counter);
            }else{
                if(counter == 0){
                    sprintf(temp, "%c", currCounting);
                }else if(counter == 1){
                    sprintf(temp, "%c%c", currCounting, currCounting);
                }else{
                    sprintf(temp, "%d%c", counter, currCounting);
                }
                for(k = 0; k < strlen(temp); k++, j++){
                    dest[j] = temp[k];
                }
                currCounting = src[i];
                counter = 0;
                printf("Current output >> %s\n", dest);
            }   
        }
    }
}