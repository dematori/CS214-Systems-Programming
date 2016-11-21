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

int *findSplits(int fileSize);                              // Method to find the partitions for the multipart compression
void startCompression(int *splitLength);                    // starts the compressions after the partitions are found
void compress(char* str, int fileNum);                      // compresses the part and prints it to the output file
FILE *generateOutFile(int fileNum);                         // generates the output file when it doesn't exist and removes any previously existing files

char *filename;
char *fileString;
int breaks;
int firstFile = 0;

/*
* Main method to get the user input for which file to compress and how many parts to compress the file into.
*/
int main(int argc, char* argv[]){
    if (argc != 3){                                                                                                 // Number of arguments must be 2 (one for file name and one for the number of parts)
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments.\n", (argc-1));     // Error message to inform user that there are only supposed to be two arguments
        return 0;                                                                                                   // exit the program if the number of arguments is incorrect
    }
    filename = argv[1];                                                                                             // extracts the filename from the arguments
    breaks = atoi(argv[2]);                                                                                         // extracts the parts from the arguments and converts it to an integer
    FILE *file = fopen(filename, "r");                                                                              // opening the file that is instructed to be read-only
    if(file == NULL){                                                                                               // if the file does not exist in the current directory
       fprintf(stderr, "ERROR: Cannot open file >> %s\n", filename);                                                // informs the user that the file does not exist in the director
       exit(1);                                                                                                     // exits the program on missing file
    }
    fseek(file, 0, SEEK_END);                                                                                       // finding the end of the file
    int fileSize = ftell(file);                                                                                     // finding the length of the file
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
        char compStr[tempLen + 1];
        memcpy(compStr, &fileString[currentIndex], tempLen+1);
        compStr[tempLen] = '\0';
        compress(compStr, i, splitLength);
        currentIndex += tempLen;
    }
}

void compress(char *src, int fileNum){
    FILE *output = generateOutFile(fileNum);
    int len = strlen(src);
    int i;
    char currCounting = src[0];
    int counter = 1;
    for(i = 1; i <= len; i++){
        if(!isalpha(currCounting)){
            currCounting = src[i];
            counter = 1;
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