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
	newNode -> is_saved = 0; 
	return newNode; 
}


char* budgetStatus(float *balance, float *expense){
	if (*balance >= *expense){
		return "Within Budget";
	} else return "Over Budget!";
}

void insert_at_position(Node** head_ref, Node* new_node, int position){
	// Case 1: Inserting at the very front (Position 1)
	if (position == 1 || *head_ref == NULL){
		new_node -> next = *head_ref; 
		*head_ref = new_node;
		return;
	}
	// Case 2: Inserting in the middle or at the end
	Node* temp = *head_ref;
	for(int i = 1; temp-> next != NULL && i < position - 1; i++){
		temp = temp -> next;
	}
	// Link the new node into the list
	new_node -> next = temp -> next; 
	temp->next = new_node; 
}

void add_income(Node** head_ref,int position, float income, float* balance, char* description){
	Node* new_node = createNode(income);
	new_node->next = NULL;
	new_node->is_expense = 0;
	strcpy(new_node->description,description);
	
	// Call insertion helper 
	insert_at_position(head_ref, new_node, position);
	*balance += income;
	
	
}

void add_expense(Node** head_ref,int position, float expense, float *balance, char* description){
	Node* new_node = createNode(-expense);
	new_node->next = NULL;
	strcpy(new_node->description, description);
	new_node->is_expense = 1;

	// Call insertion helper
	insert_at_position(head_ref, new_node,position);	

	*balance -= expense; 
}

// Need to fix on changing the balance after deleting the transaction. 
void delete(Node** head_ref, int position, float *balance){
	// check  if the list is empty
	if (*head_ref == NULL || position < 1){
		printf("Error: Invalid position or empty list!\n");
		return;
	}	

	Node* temp = *head_ref;
	
	// case 1: Deleting the very first node (head)
	if(position == 1){
		*head_ref = temp->next; 
		*balance -= temp->data;
		free(temp);
		printf("Transaction deleted.\n");
		return; 
	}
	
	// case 2: Deleting middle or end node 
	Node* prev = NULL;
	for(int i = 1; temp != NULL && i < position; i++) {
		prev = temp;
		temp = temp->next;
	}
	
	// If position is greater than the number of nodes in the list
	if (temp == NULL){
		printf("Error: Position out of bounds!\n");
		return;
	}
	// Unlink the node from the linked list 
	prev->next = temp->next; 
	
	// Update Balance and free memory 
	*balance -= temp->data; 
	free(temp);
	printf("Transaction deleted");

}



void print(Node* node){
	int i = 1;
	printf("[ Transactions ]\n");
	while (node != NULL){
		if(node->is_expense){
			printf("%d. %-20s%+8.2f%15s\n", i, node->description, node->data, node->is_saved ? "(saved)" : "(new)");
		}else{
			printf("%d. %-20s%+8.2f%15s\n", i, node->description, node->data, node->is_saved ? "(saved)" : "(new)");		
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
	// float key_trans;
	int position;
	
	
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
					while(scanf("%f", &amount) != 1 || amount <= 0){
						printf("Invalid input! Try again: ");
						while(getchar() != '\n'); // clear the corrupted input buffer line
					} 
					while (getchar() != '\n'); // clear remaining newline character

					printf("Insert at position: ");
					scanf("%d", &position);
					add_income(&head_node,position, amount, &balance, description);
					printf("Income added.\n\n");
					printf("\nCurrent balance: $%.2f\n", balance);
                        		printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Add Expense Feature
				 } else if(strcmp(command, "add expense") == 0){
					printf("Enter expense description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
                    while(scanf("%f", &amount) != 1 || amount <= 0){
						printf("Invalid input! Try again: ");
						while(getchar() != '\n'); // clear the corrupted input buffer line
					} 
					while (getchar() != '\n'); // clear remaining newline character

					
					printf("Insert at Position: ");
					scanf("%d", &position ); 
                                        add_expense(&head_node,position, amount, &balance, description);
					printf("Expense added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Quit the program 	
				  } else if(strcmp(command, "quit") == 0) {

                    			fclose(fptr);
                    			fptr = fopen("transaction_log.txt", "w");
                   	 		// fptr validation
                    			if (fptr == NULL){
                       	 			printf("Error: Could not open file for saving!\n");
                        			running = 0;
                        			return 0;
                    			}
                    		// temporary pointer starting at head
                    		Node* current = head_node;
                		printf("Saving transactions to file...\n");
                    		while(current != NULL){  
                        		if(current -> is_expense == 0){
                            			fprintf(fptr, "INC|%s|%.2f\n", current->description, current->data);
                        		}else {
                                        
                            			//change negative numbers in memory to positive
                            			float save_amount = current->data < 0 ? -current->data: current->data;
                            			fprintf(fptr, "EXP|%s|%.2f\n", current->description,save_amount);
                                 
                        		}
                        		current = current->next;
                    		}
                                        
                    		fclose(fptr);
                    		printf("Done. Exiting Program.\n");
                    		running = 0; //Not running
					
					
				//Delete Transaction Feature
				} else if(strcmp(command, "delete") == 0){
					printf("Which transaction you want to delete? (Enter position): ");
					scanf("%d", &position);
					delete(&head_node, position, &balance);
					printf("\nCurrent balance: $%.2f\n", balance);
					printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Print Transaction feature
				} else if (strcmp(command, "print") == 0) {
					print(head_node);
					printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
				}
			}
		} else if(fptr != NULL){
			// Retrieve the amount of balance
			char content[1000];
			char type[4]; 
			char desc[100]; 
			float amount;
			Node *head_node = NULL;
			int file_pos = 1; 
			while(fgets(content, 1000, fptr) != NULL){
				sscanf(content, "%3[^|]|%99[^|]|%f", type, desc, &amount);
				if(strcmp(type, "INC") == 0){
					add_income(&head_node,file_pos, amount, &balance, desc);
				} else if(strcmp(type, "EXP") == 0){
					add_expense(&head_node,file_pos, amount, &balance, desc); 
				}
				file_pos++;
				Node* temp = head_node;
				while(temp != NULL && temp->next != NULL){
					temp = temp-> next; 
				}
				if(temp != NULL){
					temp->is_saved = 1; // Mark as saved from file
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
                                        while(scanf("%f", &amount) != 1 || amount <= 0){
											printf("Invalid input! Try again: ");
											while(getchar() != '\n'); // clear the corrupted input buffer line
										} 
										while (getchar() != '\n'); // clear remaining newline character

										printf("Insert at position: ");
										scanf("%d", &position);
										add_income(&head_node,position, amount, &balance, description);
										printf("Income added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
                                
                                // Add Expense Feature
                                 } else if(strcmp(command, "add expense") == 0){
                                        printf("Enter expense description: ");
                                        scanf(" %99[^\n]", description);
                                        printf("Enter amount: ");
                                        while(scanf("%f", &amount) != 1 || amount <= 0){
											printf("Invalid input! Try again: ");
											while(getchar() != '\n'); // clear the corrupted input buffer line
										} 
										while (getchar() != '\n'); // clear remaining newline character

										printf("Insert at postion: ");
										scanf("%d", &position);
                                        add_expense(&head_node,position, amount, &balance, description);
										printf("Expense added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

                                // Quit the program
                                } else if(strcmp(command, "quit") == 0) {
					fclose(fptr);
					fptr = fopen("transaction_log.txt", "w");
					// fptr validation
					if (fptr == NULL){
						printf("Error: Could not open file for saving!\n");
						running = 0;
						return 0;
					}
                                        // temporary pointer starting at head
                                        Node* current = head_node;
					printf("Saving transactions to file...\n");
                                        while(current != NULL){
                                                if(current -> is_expense == 0){
                                                        fprintf(fptr, "INC|%s|%.2f\n", current->description, current->data);
						}else {

							//change negative numbers in memory to positive
							float save_amount = current->data < 0 ? -current->data: current->data;
							fprintf(fptr, "EXP|%s|%.2f\n", current->description,save_amount);

						}
						current = current->next; 
					}

                                        fclose(fptr);
					printf("Done. Exiting Program.\n");
                                        running = 0; //Not running
                                
                                //Delete Transaction Feature
                                } else if(strcmp(command, "delete") == 0){
                                        printf("Which transaction you want to delete? (Enter position): ");
                                        scanf("%d", &position);
                                        delete(&head_node, position, &balance);
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
                                
                                // Print Transaction feature
                                } else if (strcmp(command, "print") == 0) {
                                        print(head_node);
					printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
                                }
                        }
		}
	} else if (resumeChoice == 'n'){
		printf("Initializing a new session...");
		fptr = fopen("transaction_log.txt", "w");
		if (fptr == NULL){
			printf("\nOpening File Failed\n");
			printf("\nInititalizing a new linked list...\n");
 
			Node *head_node = NULL;
			

			printf("\nNew Session Created\n");
			printf("Current balance: $%.2f\n", balance);
			printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
			strcpy(head_node->description,"Initial Transaction");		

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
					while(scanf("%f", &amount) != 1 || amount <= 0){
						printf("Invalid input! Try again: ");
						while(getchar() != '\n'); // clear the corrupted input buffer line
					} 
					while (getchar() != '\n'); // clear remaining newline character

					printf("Insert at position: ");
					scanf("%d", &position);
					add_income(&head_node,position, amount, &balance, description);
					printf("Income added.\n\n");
					printf("\nCurrent balance: $%.2f\n", balance);
                        		printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Add Expense Feature
				 } else if(strcmp(command, "add expense") == 0){
					printf("Enter expense description: ");
					scanf(" %99[^\n]", description);
					printf("Enter amount: ");
                    while(scanf("%f", &amount) != 1 || amount <= 0){
						printf("Invalid input! Try again: ");
						while(getchar() != '\n'); // clear the corrupted input buffer line
					} 
					while (getchar() != '\n'); // clear remaining newline character

					
					printf("Insert at Position: ");
					scanf("%d", &position ); 
                                        add_expense(&head_node,position, amount, &balance, description);
					printf("Expense added.\n\n");
                                        printf("\nCurrent balance: $%.2f\n", balance);
                                        printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Quit the program 	
				  } else if(strcmp(command, "quit") == 0) {

                    			fclose(fptr);
                    			fptr = fopen("transaction_log.txt", "w");
                   	 		// fptr validation
                    			if (fptr == NULL){
                       	 			printf("Error: Could not open file for saving!\n");
                        			return 0;
                    			}
                    		// temporary pointer starting at head
                    		Node* current = head_node;
                		printf("Saving transactions to file...\n");
                    		while(current != NULL){  
                        		if(current -> is_expense == 0){
                            			fprintf(fptr, "INC|%s|%.2f\n", current->description, current->data);
                        		}else {
                                        
                            			//change negative numbers in memory to positive
                            			float save_amount = current->data < 0 ? -current->data: current->data;
                            			fprintf(fptr, "EXP|%s|%.2f\n", current->description,save_amount);
                                 
                        		}
                        		current = current->next;
                    		}
                                        
                    		fclose(fptr);
                    		printf("Done. Exiting Program.\n");
                    		running = 0; //Not running
					
					
				//Delete Transaction Feature
				} else if(strcmp(command, "delete") == 0){
					printf("Which transaction you want to delete? (Enter position): ");
					scanf("%d", &position);
					delete(&head_node, position, &balance);
					printf("\nCurrent balance: $%.2f\n", balance);
					printf("Budget Status: %s\n", budgetStatus(&balance,&expense));

				// Print Transaction feature
				} else if (strcmp(command, "print") == 0) {
					print(head_node);
					printf("\nCurrent balance: $%.2f\n", balance);
                    printf("Budget Status: %s\n", budgetStatus(&balance,&expense));
				}
			}
	} else{
		printf("Invalid input. Try again\n");
	}
	


	return 0;
} 
}

