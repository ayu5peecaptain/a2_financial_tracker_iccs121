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

void add_income(Node** head_ref, int income){
	Node* new_node = createNode(income);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
	
}

void add_expense(Node** head_ref, int expense){
	Node* new_node = createNode(expense);
	new_node->next = (*head_ref);
	(*head_ref) = new_node; 
}

void delete(struct Node** head_ref, int key_trans){
	Node *temp = *head_ref, *prev=NULL; 
	if (temp != NULL && temp->data == key_trans){
		*head_ref = temp->next; // change head 
		free(temp);
		return; 
	}
	// Search for the key to be deleted
	// Keep track of the previous node as we need to change 'prev->next'	
	while(temp != NULL && temp->data != key_trans){
		prev = temp; 
		temp = temp->next; 	
	}
	// If key awas not present in linked list
	if (temp == NULL){
		return;
	}
	
	// Unlink the node from linked list
	prev->next = temp->next; 
	free(temp);
}

void print(Node* node){
	while (node != NULL){
		printf(" %d ", node->data);
		node = node -> next;
	}

}




int main(){

	char resumeChoice;
	char command[20]; 
	int balance = 0, expense = 0;
	
	FILE* fptr; 

	printf("Welcome to your Personal Finance Tracker!\n"); 
	printf("\nWould you like to resume your previous session? (y/n): ");
	scanf("%c", &resumeChoice);
	
	// Check User's choice of resuming a previous session or not
	if (resumeChoice == 'y'){
		printf("Resuming from last session...\n");
		fptr = fopen("transaction_log.txt", "r");
		if (fptr == NULL){
			printf("\nOpening File Failed\n");
			printf("\nInititalizing a new linked list...\n"); 
			Node *head_Node = createNode(balance);
			printf("\nTransaction loaded\n");
			printf("Current Balance: $%d\n", balance); 
			printf("Budget Status: %s\n", budgetStatus(balance, expense));
			printf("\nInitial Transaction: $%d\n", head_Node -> data);
			
			//Add income, expenses, delete
			printf("Enter command: "); 
			scanf(" %19[^\n]", command);
			
			//condition to function 
			if (command == "add income"){
				printf()
			}
		}
	} else if (resumeChoice == 'n'){
		printf("User doesn't want to resume\n");
	}
	


	return 0;
}
