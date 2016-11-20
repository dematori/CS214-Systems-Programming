// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127              rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "ERROR: Incorrect number of arguments given >> %d. Expected 2 arguments.\n", (argc-1));
        return 0;
    }
    char *filename = argv[1];
    int breaks = atoi(argv[2]);
    printf("\nFilename: \"%s\"", filename);
    printf("\nNumber of breaks: %d\n", breaks);
    FILE *file = fopen(filename, "r");
    if(file == NULL){
       fprintf(stderr, "ERROR: Cannot open file >> %s", filename);
       exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* fileString = (char *) malloc(fileSize + 1);
    fread(fileString, fileSize, 1, file);
    fclose(file);
    fileString[fileSize] = 0;
    printf("String to be compressed >> %s\n", fileString);
    printf("END OF PROGRAM\n");
    return 0;
}