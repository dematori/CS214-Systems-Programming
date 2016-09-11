// Jeffrey Huang
// NetID: jh1127
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 0 - Due September 18, 2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
	char *word;
	struct node *next;
};

//helper method that merges two linked lists in sorted order
struct node* sortedMerge(struct node* a, struct node* b);

//splits linked list into two
void frontBackSplit(struct node* source, struct node** frontRef, struct node** backRef);

//Merge sort
void mergesort(struct node** headRef) {
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	if((head == NULL) || (head->next == NULL)) {
		return;
	}

	frontBackSplit(head, &a, &b);

	mergesort(&a);
	mergesort(&b);

	*headRef = sortedMerge(a, b);
}

struct node* sortedMerge(struct node* a, struct node*b) {
	struct node* result = NULL;
	if(a == NULL) {
		return(b);
	} else if(b == NULL) {
		return(a);
	}

	if(strcmp(a->word, b->word) < 0) {
		result = a;
		result->next = sortedMerge(a->next, b);
	} else {
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return result;
}

void frontBackSplit(struct node* source, struct node** frontRef, struct node** backRef) {
	struct node* fast;
	struct node* slow;
	if(source == NULL || source->next == NULL) {
		*frontRef = source;
		*backRef = NULL;
	} else {
		slow = source;
		fast = source->next;

		while(fast != NULL) {
			fast = fast->next;
			if(fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

struct node * createLinkedList(char* str) {
}

void printLinkedList(struct node *root) {
	while(root != NULL) {
		printf("%s\n", root->word);
		root = root->next;
	}
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
	char *token = strtok(inputString, " ");
	char **words = malloc(count);

	struct node *root, *ptr, *parent;
	root = malloc(sizeof(struct node));
	root->next = NULL;
	root->word = token;
	ptr = root;

	while(token) {
		struct node *newNode;
		newNode = malloc(sizeof(struct node));
		ptr->next = newNode;
		token = strtok(NULL, " ");
		newNode->next = NULL;
		newNode->word = token;
		parent = ptr;
		ptr = ptr->next;
	}
	parent->next = NULL;

	mergesort(&root);

	printLinkedList(root);

	return 0;
}
