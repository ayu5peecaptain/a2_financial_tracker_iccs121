#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "main.h"

Node* createNode(int data){ 
	Node* newNode=(Node*)malloc(sizeof(Node)); 
	if (newNode == NULL){
		printf("Allocation failed\n");
		exit(0);
	}
	newNode -> data = data; 
	newNode -> next = NULL;
	return newNode; 
}

char* budgetStatus(int balance, int expense){
	if (balance >= expense){
		return "Within Budget";
	} else return "Over Budget!";
}


int main(){

	char resumeChoice;
	int balance = 0, expense = 0;
	
	FILE* fptr; 

	printf("Welcome to your Personal Finance Tracker!\n"); 
	printf("\nWould you like to resume your previous session? (y/n): ");
	scanf("%c", &resumeChoice);
	
	// Check User's choice of resuming a previous session or not
	if (resumeChoice == 'y'){
		printf("Resuming from last session...");
		fptr = fopen("transaction_log.txt", 'r');
		if (fptr == NULL){
			printf("Opening File Failed\n");
			printf("Inititalizing a new linked list...\n"); 
			Node *head_Node = createNode(0);
			printf("Transaction loaded\n");
			printf("Current Balance: $%d\n", balance); 
			printf("Budget Status: %s\n", budgetStatus(balance, expense)); 
		}
	} else if (resumeChoice == 'n'){
		printf("User doesn't want to resume\n");
	}
	


	return 0;
}
