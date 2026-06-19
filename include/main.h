typedef struct Node {
        float data;
        int is_expense; // 1 = expense, 0 = income
	int is_saved; // 1 = saved, 0  for new 
        int is_deleted; // 1 = deleted 0 = not deleted 
        char description[100];
        struct Node* next;
} Node;

Node* createNode(float data);
void add_income(Node** head_ref,int position, float income, float *balance, char* description);
void add_expense(Node** head_ref,int position, float expense, float *balance, char* description);
void delete(Node** head_ref, int position, float *balance);
void print(Node* node);
void quit();
char* budgetStatus(float *balance, float *expense);
void insert_at_position(Node** head_ref, Node* new_node, int position);
void run_session(Node** head_node, float* balance, float* expense, FILE** fptr); 

