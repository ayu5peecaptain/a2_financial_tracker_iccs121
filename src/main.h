typedef struct Node {
        float data;
        int is_expense; // 1 = expense, 0 = income
        char description[100];
        struct Node* next;
} Node;

Node* createNode(float data);
void add_income(Node** head_ref, float income, float *balance, char* description);
void add_expense(Node** head_ref, float expense, float *balance, char* description);
void delete(Node** head_ref, float key, float *balance, char* description);
void print(Node* node);
void quit();
char* budgetStatus(float *balance, float *expense);