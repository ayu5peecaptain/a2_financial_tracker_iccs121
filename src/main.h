typedef struct Node{
	int data; 
	struct Node* next;
}Node;

Node* createNode(int data); 
int add_income(int income);
int add_expense(int expense);
Node* delete(Node NodePosition); 
void print();
void quit();
char* budgetStatus(int balance, int expense); 
