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


char* budgetStatus(int *balance, int *expense){
	if (*balance >= *expense){
		return "Within Budget";
	} else return "Over Budget!";
}


void add_income(Node** head_ref, int income, int* balance, char* description){
	Node* new_node = createNode(income);
	new_node->next = NULL;
	new_node->is_expense = 0;
	strcpy(new_node->description,description);
	if (*head_ref == NULL){
		*head_ref = new_node; // list was empty
	} else{
		Node *temp = *head_ref; 
		while (temp->next != NULL){
			temp = temp -> next;
		}
		temp -> next = new_node; // attach to tail
	}
	*balance += income;
	
	
}

void add_expense(Node** head_ref, int expense, int *balance, char* description){
	Node* new_node = createNode(-expense);
	new_node->next = NULL;
	strcpy(new_node->description, description);
	new_node->is_expense = 1;
	if (*head_ref == NULL){ 
		*head_ref = new_node; // list was empty
        } else{ 
		Node *temp = *head_ref;
                while (temp->next != NULL){ 
                        temp = temp -> next;
                }
                temp -> next = new_node; // attach to tail
	}
	*balance -= expense; 
}

// Need to fix on changing the balance after deleting the transaction. 
void delete(struct Node** head_ref, int key_trans, int *balance, char* description){
	Node *temp = *head_ref, *prev=NULL; 
	if (temp != NULL && temp->data == key_trans && strcmp(temp->description,description) == 0){
		*head_ref = temp->next; // change head
		*balance -= temp->data; 
		free(temp);
		return; 
	}
	// Search for the key to be deleted
	// Keep track of the previous node as we need to change 'prev->next'	
	while((temp != NULL && temp->data != key_trans) && (strcmp(temp->description, description) != 0)){
		prev = temp; 
		temp = temp->next; 	
	}
	// If key awas not present in linked list
	if (temp == NULL){
		return;
	}
	
	// Unlink the node from linked list
	prev->next = temp->next;
	*balance -= temp->data; 
	free(temp);
}

void print(Node* node){
	int i = 1;
	while (node != NULL){
		if(node->is_expense){
			printf("%d. %-20s%+6d\n", i, node->description, node->data);
		}else{
			printf("%d. %-20s%+6d\n", i, node->description, node->data);		
		}
		i = i + 1; 
		node = node -> next;
	}

}




int main(){

	char resumeChoice;
	char command[20];
	char description[100]; 
	int balance = 0, expense = 0, amount=0;
	int key_trans;
	
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
 
			Node *head_node = createNode(balance);

			printf("\nTransaction loaded\n");
			printf("Current balance: $%d\n", balance);
			printf("Budget Status: %s\n", budgetStatus(&balance,& expense));
			strcpy(head_node->description,"Initial Transaction");			

			int running = 1; // flag 
			while (running){
				//Add income, expenses, delete
				printf("Enter command: "); 
				scanf(" %19[^\n]", command);
			
				//condition to function
				//Add Income feature 
				if (strcmp(command, "add income") == 0){
					printf("Enter income description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
					scanf("%d", &amount); 
					add_income(&head_node, amount, &balance, description);
					printf("\nCurrent balance: $%d\n", balance);
                        		printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Add Expense Feature
				 } else if(strcmp(command, "add expense") == 0){
					printf("Enter expense description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
                                        scanf("%d", &amount);
                                        add_expense(&head_node, amount, &balance, description);
                                        printf("\nCurrent balance: $%d\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Quit the program 	
				} else if(strcmp(command, "quit") == 0) {
					running = 0; //Not running

				//Delete Transaction Feature
				} else if(strcmp(command, "delete") == 0){
					printf("With transaction you want to delete? (Enter the amount): ");
					scanf("%d", &key_trans);
					printf("In which description?: ");
					scanf(" %99[^\n]", description);
					delete(&head_node, key_trans, &balance, description);               		  
					printf("\nTransaction deleted\n");
					printf("\nCurrent balance: $%d\n", balance);
					printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Print Transaction feature
				} else if (strcmp(command, "print") == 0) {
					print(head_node);
				}
			}
		}
	} else if (resumeChoice == 'n'){
		printf("User doesn't want to resume\n");
	}
	


	return 0;
}
