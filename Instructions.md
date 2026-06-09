# A02: Advanced Personal Finance Tracker (student ver.)

---

============================================================================================

**IMPORTANT NOTE REGARDING THE LATE TOKEN:**
- You have one (1) late token that can be used only for this assignment.
- This token provides a one-week extension from the original deadline.
- Please note: The extension is calculated from the original due date, regardless of when you notify us. For example, if you inform me or a TA 5 days after the deadline, you will only have 2 additional days to submit.

============================================================================================

**Objective:**

In this task, you will develop a **Personal Finance Tracker** in C that allows users to track income and expenses while maintaining a **linked list of transactions**. The program will **read previous logs from a file and store transactions in a linked list**, enabling users to modify the list before saving updates back to the file.

Additionally, you must create a **Makefile** to automate the compilation process. The output executable must be named **`fintrack`**.

**Folder Structure & File Organization**

Your project should be organized as follows:

```
/                     # Root project directory
├── dist/             # Distribution folder (final ZIP file will be here)
│   ├── fintrack.zip
├── release/          # Executable location
│   ├── fintrack
├── src/              # Source code files
│   ├── main.c        # Main program entry point
│   └── *.c           # Additional source files (to be created by student)
├── include/          # Header files
│   └── *.h           # Header files (to be created by student)
├── logs/             # Transaction logs
│   ├── transaction_log.txt
├── report/           # Documentation folder
│   ├── summary.pdf   # Student's project summary report
├── Makefile          # Build automation script
```

**Folders Structure:**

- **`src/`** → Contains all .c source files.
- **`include/`** → Contains all .h header files.
- **`logs/`** → Stores the transaction log file (transaction_log.txt). The program should read from and write to this file.
- **`release/`** → Stores the compiled executable (fintrack).
- **`dist/`** → Stores the final ZIP file containing the required files for submission.
- **`Makefile`** → Automates the compilation process and ensures a structured build.

**Requirements**

**1. Initial Setup**

- At the start of the program, ask the user if they want to **resume a previous session** by reading the transaction log (logs/transaction_log.txt).
- If resuming, read the previous transactions from the file and store them in a **linked list**.
- If no log file exists, start with an empty linked list.

**2. Transaction Management (Using a Linked List)**

- The program must maintain all transactions dynamically using a **linked list**.
- Users can **insert** a new transaction at any position (beginning, middle, or end).
- Users can **delete** any specific transaction by its position in the list.
- Transactions should not be immediately written to the file—only updated in the **linked list** while the program is running.

**3. User Commands**

The program should provide the following commands:

1. **`add income`** – Add an income transaction (with a description and amount). After adding, displays whether the user is within budget or in debt.
2. **`add expense`** – Add an expense transaction (with a description and amount). After adding, displays whether the user is within budget or in debt.
3. **`delete <position>`** – Remove a transaction from the linked list (position is based on list order).
4. **`print`** – Display all transactions in the linked list.
5. **`quit`** – Save all transactions to `logs/transaction_log.txt` and exit the program.

**Note on Input Handling:** Students may implement one of two valid UI paradigms.
- A menu-driven interface, where the user is presented with a list of options and selects one by entering its corresponding number.
- A command-driven interface, where the user inputs the command directly as a string (e.g., add income, delete 3).

**4. File Handling**

- **Transactions should only be written to the log file when the user quits.**
- If the program stops unexpectedly, the log file should **remain unchanged**.
- When quitting, **overwrite the existing log file** with the latest linked list data.

**5. Transaction Display Format**

- The print command should display transactions with symbols indicating modifications:
- **`+++ i`** → Newly inserted transactions (not yet saved to the file).
- **`--- d`** → Transactions marked for deletion (removed from the linked list but not yet from the file).
- Ensure a **clear and structured output format** (see sample below).

**6. Input Validation (Must be Robust)**

- **Reject negative values** for income and expenses.
- **Reject non-numeric inputs** for amounts.
- **Handle invalid delete positions gracefully** (e.g., deleting an out-of-range entry should not crash the program).

**7. Makefile Requirement**

You must create a **Makefile** that:

- Compiles all .c files and generates an executable named **fintrack** in the release/ directory.
- Supports make clean to remove all .o files and the executable.
- Supports `make dist` to create a ZIP archive (dist/fintrack.zip) containing src/, include/, logs/transaction_log.txt, report/, and Makefile.
- Running `make` without arguments should execute clean, compile the executable, and create the distribution ZIP.

**8. Code Structure and Organization**

- **Split code into multiple files** (.c and .h files) and organize them into folders (src/, include/).
- Use **descriptive function and variable names**.
- Include **comments** explaining the purpose of functions and structures.
- Ensure the program is **modular and professional**—this will be part of your grade.

**9. Submission Requirements**

- Submit all **source files** via GitHub Classroom.
- Include a **PDF report** explaining how the program works:
- Describe the **linked list implementation** and its advantages.
- Showcase all **features** implemented.
- Include screenshots or logs demonstrating program behavior

**Grading Criteria**

| **Criteria** | **Points** |
| --- | --- |
| Properly implemented linked list | 15 |
| Supports all required commands | 15 |
| Correct file handling (delayed save) | 10 |
| Proper input validation | 10 |
| Modular and well-structured code with appropriate comments | 10 |
| Clear, professional formatting in print output | 10 |
| Makefile correctly compiles and organizes output | 10 |
| PDF report with explanations and screenshots | 10 |
| Handles edge cases (e.g., invalid delete position) | 10 |
| **Total** | **100** |

**Example Interaction & Expected Output:**

---

**Starting the Program (Loading Previous Transactions)**

**Original Log File (logs/transaction_log.txt) Before Running the Program:**

```
# Format: TYPE|DESCRIPTION|AMOUNT
# TYPE: INC (Income) or EXP (Expense)
# AMOUNT: Positive decimal number

INC|Freelance Project|250.00
EXP|Phone Bill|-45.00
EXP|Electricity Bill|-100.00
```

**Program Startup Output:**

```
Welcome to your Personal Finance Tracker!

Would you like to resume your previous session? (y/n): y

Resuming from last session...
Previous transactions loaded.

Current Balance: $105.00
Budget Status: Within Budget
```

**Adding Transactions & Checking Balance**

```
Enter command: add income
Enter income description: Salary
Enter amount: 1200
Income added.

Current Balance: $1305.00
Budget Status: Within Budget
```

```
Enter command: add expense
Enter expense description: Rent
Enter amount: 800
Expense added.

Current Balance: $505.00
Budget Status: Within Budget
```

```
Enter command: add expense
Enter expense description: Groceries
Enter amount: 150
Expense added.

Current Balance: $355.00
Budget Status: Within Budget
```

```
Enter command: add expense
Enter expense description: Car Payment
Enter amount: 400
Expense added.

Current Balance: -$45.00
Budget Status: Over Budget!
```

```
Enter command: add expense
Enter expense description: Dining Out
Enter amount: 100
Expense added.

Current Balance: -$145.00
Budget Status: Over Budget!
```

**Printing Transactions (Reflecting New vs. Saved Entries)**

```
Enter command: print
[ Transactions ]
1. Freelance Project  +250.00    (saved)
2. Phone Bill        -45.00     (saved)
3. Electricity Bill  -100.00    (saved)
4. Salary           +1200.00    (new)
5. Rent            -800.00     (new)
6. Groceries       -150.00     (new)
7. Car Payment     -400.00     (new)
8. Dining Out      -100.00     (new)

Current Balance: -$145.00
Budget Status: Over Budget!
```

**Inserting a Transaction in the Middle & Deleting One**

```
Enter command: add expense
Enter expense description: Internet Bill
Enter amount: 50
Insert at position: 5
Expense added at position 5.

Current Balance: -$195.00
Budget Status: Over Budget!
```

```
Enter command: delete 3
Transaction at position 3 marked for deletion.

Current Balance: -$95.00
Budget Status: Over Budget!
```

```
Enter command: print
[ Transactions ]
1. Freelance Project  +250.00    (saved)
2. Phone Bill        -45.00     (saved)
3. Electricity Bill  -100.00    --- d
4. Salary           +1200.00    (new)
5. Internet Bill     -50.00      +++ i
6. Rent            -800.00     (new)
7. Groceries       -150.00     (new)
8. Car Payment     -400.00     (new)
9. Dining Out      -100.00     (new)

Current Balance: -$95.00
Budget Status: Over Budget!
```

**Quitting & Saving to File**

```
Enter command: quit
Saving transactions to file...
Done. Exiting program.
```

**Updated Transaction Log (logs/transaction_log.txt) After Quitting**

- **Electricity Bill (-100.00) was removed**
- **Internet Bill (-50.00) was inserted at position 5**

```
# Format: TYPE|DESCRIPTION|AMOUNT
# TYPE: INC (Income) or EXP (Expense)
# AMOUNT: Positive decimal number

INC|Freelance Project|250.00
EXP|Phone Bill|-45.00
INC|Salary|1200.00
EXP|Internet Bill|-50.00
EXP|Rent|-800.00
EXP|Groceries|-150.00
EXP|Car Payment|-400.00
EXP|Dining Out|-100.00
```
