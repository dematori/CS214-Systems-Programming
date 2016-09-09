// Jeffrey Huang
// NetID: jh1127
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 0 - Due September 18, 2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmp(const void *a, const void *b) {
	return strcmp(*(char**)a, *(char**)b);
}

int main(int argc, char *argv[]) {
	// Making sure that there are the total of two arguments.
	//		1) ./project --> argv[0]
	//		2) string subjected for analysis --> argv[1]
	if (argc != 2){
		// Informing console user about improper quantity of arguments
		printf("Expected number of arguments: 1\ni.e. ./pointersorter \"This is a sample line\"\n");
		return 0;
	}

	// Getting length of the string argument
	int stringSize = strlen(argv[1]);
	// Moving command string to variable string
	char* inputString;
	// Creating limited space to hold the string
	inputString = malloc(stringSize);
	inputString = strcat(inputString, argv[1]);
	int i = 0;
	int count = 0;
	// Replacing all non-alphabet characters to spaces
	while (inputString[i]) {
		if (!isalpha(inputString[i])){
			inputString[i] = ' ';
			if (isalpha(inputString[i+1])) {
				count++;
			}
		}
		if (inputString[i++] == '\0') {
			count++;
		}
	}
	// Tokenizing the adjusted string to an array.
	// One word per index
	int j = 0;
	char *token;
	char **words = malloc(count);
	for(token = strtok(inputString, " "); token; token = strtok(NULL, " ")) {
		words[j++] = token;
	}
	// Quicksorting through the array of words that was tokenized
	qsort(words, j, sizeof(*words), cmp);
	// Printing out the words for console display
	for (i = 0; i < j; i++) {
		printf("%s\n", words[i]);
	}
	return 0;
}