// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127              rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define CEIL(x,y) (((x) + (y) - 1) / (y))
// Method to find the partitions for the multipart compression
int *findSplits(int fileSize);
// starts the compressions after the partitions are found
void *startCompression(int *splitLength);
// compresses the part and prints it to the output file
void *compress(void *source);
// generates the output file when it doesn't exist and removes any previously existing files
FILE *generateOutFile(int fileNum);

// structure to hold the information that is passed to other threads
typedef struct _args{
    int fileN;
    int index;
    int size;
} args;

char *filename;
char *fileString;
int threads;
int firstFile = 0;

/*
* Main method to get the user input for which file to compress and how many parts to compress the file into.
*/
int main(int argc, char* argv[]){
    // Recording the runtime of the program
    struct timeval t0;
    struct timeval t1;
    long elapsed;
    gettimeofday(&t0, 0);
    // Checking input arguments making sure that user has typed the proper command
    if (argc != 3){
        printf("ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments.\n", (argc-1));
        return 0;
    }
    // Opening and finding the file size, exit program if there is no file found.
    filename = argv[1];
    threads = atoi(argv[2]);
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
    int fileLen = strlen(filename);
    if(fileLen == 0){
        printf("WARNING: File is empty.");
    }
    // Changing the filename to be renamed for the requested output file name
    int q;
    for(q = 0; q < fileLen; q++){
        if(filename[q] == '.'){
            filename[q] = '_';
        }
    }
    // String manipulation of finding how long each string segment should be
    int* splits = findSplits(fileSize);
    // Calling the compression method
    startCompression(splits);
    free(fileString);
    free(splits);
    gettimeofday(&t1, 0);  
    elapsed = (t1.tv_sec - t0.tv_sec) * 10000000 + t1.tv_usec - t0.tv_usec;
    printf("Runtime for compressT_LOLS.c >> %ld milliseconds\n", elapsed/100);
    return 0;
}
/*
* Helper method that splits the length of the string into sublength but does not manipulate the string
* ie: string length of 19 -> split into 3 parts -> findSplits returns [7, 6, 6]
*/
int *findSplits(int fileSize){
    if(fileSize < threads){
        printf("WARNING: Requested number of compressed chunks exceeds the length of uncompressed.\n");
        printf("         Parts that resulted in no compressions are automatically removed.\n");
        threads = fileSize;
    }
    int *splits = (int *) malloc(sizeof(int) * threads);
    int i;
    for(i = threads; i > 0; i--){
        int length = (int) CEIL(fileSize, i);
        fileSize -= length;
        splits[threads-i] = length;
    }
    return splits;
}

/*
* Method that starts passes the necessary information to the threads by creating the number of threads
* as requested by the user indicated by the number of files to be created.
*/
void *startCompression(int *splitLength){
    pthread_t pth[threads];
    int currentIndex = 0;
    int i;
    for(i = 0; i < threads; i++){
        args *target = (args *)malloc(sizeof(args) + 1);
        target->fileN = i;
        target->index = currentIndex;
        target->size = splitLength[i];
        pthread_create(&pth[i], NULL, compress, target);
        currentIndex += splitLength[i];
        free(target);
    }
    for(i = 0; i < threads; i++){
        pthread_join(pth[i],NULL);
    }
    return NULL;
}
/*
* Method to compress given the information about the starting index, and the length of the substring to 
* be compressed into the file as requested. 
*/
void *compress(void *source){
    args* input = (args *) source;
    int fileNum = input->fileN;
    int currentIndex = input->index;
    int len = input->size;
    char src[len + 1];
    memcpy(src, &fileString[currentIndex], len);
    src[len] = '\0';
    FILE *output = generateOutFile(fileNum);
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
    return NULL;
}
/* 
* Method to create the file that is being written for the compressed data
* ie: input: bigfile.txt -> output: bigfile_txt_LOLS_S#
*/
FILE *generateOutFile(int fileNum){
    char *outname = (char*) malloc(sizeof(filename) + sizeof(char) * 6 + sizeof(int));
    sprintf(outname, "%s_LOLS%d", filename, fileNum);
    remove(outname);
    FILE *fp;
    fp = fopen(outname, "a");
    free(outname);
    return fp;
}