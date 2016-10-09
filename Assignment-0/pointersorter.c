// Name:	Jeffrey Huang		Richard Li
// NetID:	jh1127				rl606
// CS214 - Systems Programming
// Section 2 - Professor Andrew Tjang
// Assignment 0 - Due September 18, 2016 (Sunday)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Implementation to ignore case when comparing the strings to keep lexicographical order.
int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

// Structure for linked list node that is to contain a string of one word.
struct node {
	char *word;
	struct node *next;
};

// Helper method to merge two linked list in sorted order.
struct node* sortedMerge(struct node* a, struct node* b);

// Splits the linked list into two halfs
void frontBackSplit(struct node* source, struct node** frontRef, struct node** backRef);

// Merge sort implementation
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

	if(strcicmp(a->word, b->word) < 0) {
		result = a;
		result->next = sortedMerge(a->next, b);
	} else {
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return result;
}

// Splits the linked list into a front and a back reference
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
// Method to print the linked list
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
		printf("Expected number of arguments: 1\nNumber of arguments you have: %d\ni.e. ./pointersorter \"This is a sample line\"\n", (argc-1));
		return 0;
	}
	// Getting length of the string argument.
	int stringSize = strlen(argv[1]) + 1;
	// Moving command string to variable string.
	char* inputString;
	// Creating limited space to hold the string.
	inputString = malloc(stringSize);
	inputString = strcat(inputString, argv[1]);
	int i = 0;
	int count = 0;
	// Replacing all non-alphabet characters with spaces.
	while (inputString[i]) {
		if (!(isalpha(inputString[i]))){
			inputString[i] = ' ';
			if (isalpha(inputString[i+1])) {
				count++;
			}
		}
		if (inputString[i++] == '\0') {
			count++;
		}
	}
	// If the string is only filled with non-alpha characters.
	// the program terminates with a NULL list and prints nothing.
	if(count == 0){
		return 0;
	}

	// Allocating multiple nodes and the appropriate memory space for each node.
	// Initializes the node as  well as the first word in the string.
	char *token = strtok(inputString, " ");
	struct node *root = (struct node*) malloc(sizeof(struct node));
	struct node *ptr = (struct node*) malloc(sizeof(struct node));
	struct node *parent = (struct node*) malloc(sizeof(struct node));
	root->next = NULL;
	root->word = token;
	ptr = root;
	// Tokenizing the input string into a linked list with one word per node.
	while(token) {
		struct node *newNode;
		newNode = malloc(sizeof(struct node));
		ptr->next = newNode;
		token = strtok(NULL, " ");
		newNode->next = NULL;
		newNode->word = malloc(sizeof(token));
		newNode->word = token;
		parent = ptr;
		ptr = ptr->next;
	}
	// Terminating the linked list to ensure no trash is appended at the end.
	parent->next = NULL;
	// Sending linked list to sort method to be sorted by lexicographical order 
	// (a.k.a - dictionary order).
	mergesort(&root);
	// Sending linked list to print method to print to console for user to see.
	printLinkedList(root);

	return 0;
}
