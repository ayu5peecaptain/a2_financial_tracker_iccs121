typedef struct Node{
	int data; 
	struct Node* next;
}Node;

Node* createNode(int data); 
void add_income(Node** head_ref,int income);
void add_expense(Node** head_ref,int expense);
void delete(Node** head_ref, int key); 
void print(Node* node);
void quit();
char* budgetStatus(int balance, int expense); 
