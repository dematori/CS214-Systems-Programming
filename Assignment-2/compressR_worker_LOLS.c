// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127				rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 2 - Due November 22, 2016 (Tuesday)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    //Opening file and getting arguments
    FILE* file = fopen(argv[1], "r");
    int offset = atoi(argv[2]);
    int length = atoi(argv[3]);
    int fileNum = atoi(argv[4]);
    fseek(file, offset, SEEK_SET);
    char str[length + 1];
    fread(str, 1, length, file);
    str[length + 1] = '\0';
    fclose(file);

    //Creating a new file
    char* outname = (char*) malloc(sizeof(argv[1]) + 4 + sizeof(argv[4]));
    char* filename = argv[1];
    int fileLen = strlen(filename);
    int i;
    for(i = 0; i < fileLen; i++) {
        if(filename[i] == '.') {
            filename[i] = '_';
        }
    }
    sprintf(outname, "%s_LOLS%s", argv[1], argv[4]);
    remove(outname);
    FILE* newfile = fopen(outname, "a");

    //Encoding algorithm
    i = 1;
    char currCounting = str[0];
    int count = 1;
    for(i = 1; i <= length; i++) {
        if(!isalpha(currCounting)) {
            currCounting = str[i];
        }
        else {
            if(currCounting == str[i]) {
                count++;
            }
            else {
                if(count == 1) {
                    fprintf(newfile, "%c", currCounting);
                }
                else if(count == 2) {
                    fprintf(newfile, "%c%c", currCounting, currCounting);
                }
                else {
                    fprintf(newfile, "%d%c", count, currCounting);
                }
                currCounting = str[i];
                count = 1;
            }
        }
    }
    fclose(newfile);
    return 0;
}
