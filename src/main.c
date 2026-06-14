#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "main.h"

Node* createNode(float data){ 
	Node* newNode=(Node*)malloc(sizeof(Node)); 
	if (newNode == NULL){
		printf("Allocation failed\n");
		exit(0);
	}
	newNode -> data = data; 
	newNode -> next = NULL;
	return newNode; 
}


char* budgetStatus(float *balance, float *expense){
	if (*balance >= *expense){
		return "Within Budget";
	} else return "Over Budget!";
}


void add_income(Node** head_ref, float income, float* balance, char* description){
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

void add_expense(Node** head_ref, float expense, float *balance, char* description){
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
void delete(struct Node** head_ref, float key_trans, float *balance, char* description){
	Node *temp = *head_ref, *prev=NULL; 
	if (temp != NULL && temp->data == key_trans && strcmp(temp->description,description) == 0){
		*head_ref = temp->next; // change head
		*balance -= temp->data; 
		free(temp);
		return; 
	}
	// Search for the key to be deleted
	// Keep track of the previous node as we need to change 'prev->next'	
	while((temp != NULL) && (temp->data != key_trans || strcmp(temp->description, description) != 0)){
		prev = temp; 
		temp = temp->next; 	
	}
	// If key was not present in linked list
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
	printf("[ Transactions ]\n");
	while (node != NULL){
		if(node->is_expense){
			printf("%d. %-20s%+8.2f\t(new)\n", i, node->description, node->data);
		}else{
			printf("%d. %-20s%+8.2f\t(new)\n", i, node->description, node->data);		
		}
		i = i + 1; 
		node = node -> next;
	}

}




int main(){

	char resumeChoice;
	char command[20];
	char description[100]; 
	float balance = 0.0, expense = 0.0, amount = 0.0;
	float key_trans;
	
	
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
 
			Node *head_node = createNode(0);
			

			printf("\nTransaction loaded\n");
			printf("Current balance: $%.2f\n", balance);
			printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
			strcpy(head_node->description,"Initial Transaction");

			// Create a transaction_log.txt in write mode
			fptr = fopen("transaction_log.txt", "w");			

			int running = 1; // flag 
			while (running){
				//Add income, expenses, delete
				printf("List of Commands:\n> add income\n> add expense\n> print\n> delete\n> quit\n");
				printf("Enter command: "); 
				scanf(" %19[^\n]", command);
			
				//condition to function
				//Add Income feature 
				if (strcmp(command, "add income") == 0){
					printf("Enter income description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
					scanf("%f", &amount); 
					add_income(&head_node, amount, &balance, description);
					printf("Income added.\n\n");
					printf("\nCurrent balance: $%.2f\n", balance);
                        		printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Add Expense Feature
				 } else if(strcmp(command, "add expense") == 0){
					printf("Enter expense description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
                                        scanf("%f", &amount);
                                        add_expense(&head_node, amount, &balance, description);
					printf("Expense added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Quit the program 	
				} else if(strcmp(command, "quit") == 0) {
					// temporary pointer starting at head
					Node* current = head_node; 
					printf("Saving transaction to file...\n");
					while(current != NULL){
						if(current -> is_expense == 0){
							fprintf(fptr, "INC|%s|%.2f\n", current->description, current->data);
							current = current -> next;
						} else if (current -> is_expense == 1){
							fprintf(fptr, "EXP|%s|%.2f\n", current->description, current->data);
							current = current -> next;
						}
					}
					fclose(fptr);
					printf("Done. Exiting program.\n");					
					running = 0; //Not running
					
				//Delete Transaction Feature
				} else if(strcmp(command, "delete") == 0){
					printf("With transaction you want to delete? (Enter the amount): ");
					scanf("%f", &key_trans);
					printf("In which description?: ");
					scanf(" %99[^\n]", description);
					delete(&head_node, key_trans, &balance, description);               		  
					printf("\nTransaction deleted\n");
					printf("\nCurrent balance: $%.2f\n", balance);
					printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Print Transaction feature
				} else if (strcmp(command, "print") == 0) {
					print(head_node);
					printf("\n");
				}
			}
		} else if(fptr != NULL){
			// Retrieve the amount of balance
			char content[1000];
			char type[4]; 
			char desc[100]; 
			float amount;
			Node *head_node = NULL; 
			while(fgets(content, 1000, fptr) != NULL){
				sscanf(content, "%3[^|]|%99[^|]|%f", type, desc, &amount);
				if(strcmp(type, "INC") == 0){
					add_income(&head_node, amount, &balance, desc);
				} else if(strcmp(type, "EXP") == 0){
					add_expense(&head_node, -amount, &balance, desc); 
				}
			}
			
			rewind(fptr); // Go back to the beginning of file
			printf("opening file successful!\n");
			printf("Current Log\n");
			printf("========================\n");
			while(fgets(content, 1000, fptr) != NULL){
				printf("%s", content);
			}
			printf("========================\n");
			printf("\nCurrent balance: $%.2f\n", balance);
                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
			int running = 1; // flag
                        while (running){
                                //Add income, expenses, delete
                                printf("List of Commands:\n> add income\n> add expense\n> print\n> delete\n> quit\n");
                                printf("Enter command: ");
                                scanf(" %19[^\n]", command);
                 
                                //condition to function
                                //Add Income feature
                                if (strcmp(command, "add income") == 0){
                                        printf("Enter income description: ");
                                        scanf(" %99[^\n]", description);
                                        printf("Enter amount: ");
                                        scanf("%f", &amount);
                                        add_income(&head_node, amount, &balance, description);
					printf("Income added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
                                
                                // Add Expense Feature
                                 } else if(strcmp(command, "add expense") == 0){
                                        printf("Enter expense description: ");
                                        scanf(" %99[^\n]", description);
                                        printf("Enter amount: ");
                                        scanf("%f", &amount);
                                        add_expense(&head_node, amount, &balance, description);
					printf("Expense added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

                                // Quit the program
                                } else if(strcmp(command, "quit") == 0) {
                                        // temporary pointer starting at head
                                        Node* current = head_node;
					printf("Saving transactions to file...\n");
                                        while(current != NULL){
                                                if(current -> is_expense == 0){
                                                        fprintf(fptr, "INC|%s|%.2f\n", current->description, current->data);
                                                        current = current -> next;
                                                } else if (current -> is_expense == 1){
                                                        fprintf(fptr, "EXP|%s|%.2f\n", current->description, current->data);
                                                        current = current -> next;
                                                }
                                        }
                                        fclose(fptr);
					printf("Done. Exiting Program.\n");
                                        running = 0; //Not running
                                
                                //Delete Transaction Feature
                                } else if(strcmp(command, "delete") == 0){
                                        printf("With transaction you want to delete? (Enter the amount): ");
                                        scanf("%f", &key_trans);
                                        printf("In which description?: ");
                                        scanf(" %99[^\n]", description);
                                        delete(&head_node, key_trans, &balance, description);
                                        printf("\nTransaction deleted\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
                                
                                // Print Transaction feature
                                } else if (strcmp(command, "print") == 0) {
                                        print(head_node);
                                        printf("\n");
                                }
                        }
		}
	} else if (resumeChoice == 'n'){
		printf("User doesn't want to resume\n");
	}
	


	return 0;
}
