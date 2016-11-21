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
#include <pthread.h>

#define CEIL(x,y) (((x) + (y) - 1) / (y))

int *findSplits(int fileSize);                              // Method to find the partitions for the multipart compression
void *startCompression(int *splitLength);                    // starts the compressions after the partitions are found
void *compress(void *source);                                 // compresses the part and prints it to the output file
FILE *generateOutFile(int fileNum);                         // generates the output file when it doesn't exist and removes any previously existing files

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
    if (argc != 3){                                                                                                 // Number of arguments must be 2 (one for file name and one for the number of parts)
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments.\n", (argc-1));     // Error message to inform user that there are only supposed to be two arguments
        return 0;                                                                                                   // exit the program if the number of arguments is incorrect
    }
    filename = argv[1];                                                                                             // extracts the filename from the arguments
    threads = atoi(argv[2]);                                                                                         // extracts the parts from the arguments and converts it to an integer
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
    startCompression(findSplits(fileSize));        
    return 0;
}

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

void *startCompression(int *splitLength){
    pthread_t pth[threads];
    int currentIndex = 0;
    int i;
    for(i = 0; i < threads; i++){
        args *target = (args *)malloc(sizeof(args) + 1);
        target->fileN = i;
        target->index = currentIndex;
        target->size = splitLength[i];
        printf(">> input data %p - %d - %d - %d\n", target, target->fileN, target->index, target->size);
        pthread_create(&pth[i], NULL, compress, target);
        currentIndex += splitLength[i];
    }
    for(i = 0; i < threads; i++){
        pthread_join(pth[i],NULL);
    }
    return NULL;
}

void *compress(void *source){
    args* input = (args *) source;
    int fileNum = input->fileN;
    int currentIndex = input->index;
    int len = input->size;
    char src[len + 1];
    memcpy(src, &fileString[currentIndex], len);
    src[len] = '\0';
    printf("<< source data %p - %d - %d - %s\n", source, fileNum, len, src);
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
    printf("%s\n", outname);
    remove(outname);
    FILE *fp;
    fp = fopen(outname, "a");
    return fp;
}