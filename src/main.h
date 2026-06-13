typedef struct Node {
	int data;
	int is_expense; // 1 = expense, 0 = income
	char description[100];
	struct Node* next;
} Node;

Node* createNode(int data);
void add_income(Node** head_ref, int income, int *balance, char* description);  
void add_expense(Node** head_ref, int expense, int* balance, char* description);              
void delete(Node** head_ref, int key, int *balance, char* description);
void print(Node* node);
void quit();
char* budgetStatus(int *balance, int *expense);
