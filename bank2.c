#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define INITIAL_ACCOUNT_COUNT 10

// Define a structure for bank accounts
typedef struct {
    int accountNumber;
    char accountHolder[MAX_NAME_LENGTH];
    double balance;
} BankAccount;

// Function prototypes
void createAccount(BankAccount **accounts, int *accountCount, int *accountCapacity);
void deposit(BankAccount *accounts, int accountCount);
void withdraw(BankAccount *accounts, int accountCount);
void displayAccounts(BankAccount *accounts, int accountCount);
int findAccount(BankAccount *accounts, int accountCount, int accountNumber);

// Main program loop
int main() {
    // Dynamic memory allocation for account list
    int accountCapacity = INITIAL_ACCOUNT_COUNT;
    BankAccount *accounts = malloc(accountCapacity * sizeof(BankAccount));
    if (accounts == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int accountCount = 0;
    int choice;

    do {
        printf("\nBank of Koradi - Welcome!\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Accounts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(&accounts, &accountCount, &accountCapacity);
                break;
            case 2:
                deposit(accounts, accountCount);
                break;
            case 3:
                withdraw(accounts, accountCount);
                break;
            case 4:
                displayAccounts(accounts, accountCount);
                break;
            case 5:
                printf("Exiting the program. Thank you for visiting Bank of Koradi!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Free dynamically allocated memory
    free(accounts);

    return 0;
}

// Function to create a new bank account
void createAccount(BankAccount **accounts, int *accountCount, int *accountCapacity) {
    // Check if memory reallocation is needed
    if (*accountCount >= *accountCapacity) {
        *accountCapacity *= 2;
        BankAccount *temp = realloc(*accounts, *accountCapacity * sizeof(BankAccount));
        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            return;
        }
        *accounts = temp;
    }

    BankAccount *newAccount = &(*accounts)[*accountCount];
    newAccount->accountNumber = *accountCount + 1;
    printf("Enter account holder name: ");
    scanf(" %[^\n]", newAccount->accountHolder);
    newAccount->balance = 0.0;

    printf("Account created successfully! Account number: %d\n", newAccount->accountNumber);
    (*accountCount)++;
}

// Function to handle deposits
void deposit(BankAccount *accounts, int accountCount) {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    // Find the account
    int index = findAccount(accounts, accountCount, accountNumber);

    // Check if account is found
    if (index == -1) {
        printf("Account not found. Please try again.\n");
        return;
    }

    // Get the deposit amount
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);

    // Validate deposit amount
    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Perform deposit
    accounts[index].balance += amount;
    printf("Deposit successful! New balance: %.2lf\n", accounts[index].balance);
}

// Function to handle withdrawals
void withdraw(BankAccount *accounts, int accountCount) {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    // Find the account
    int index = findAccount(accounts, accountCount, accountNumber);

    // Check if account is found
    if (index == -1) {
        printf("Account not found. Please try again.\n");
        return;
    }

    // Get the withdrawal amount
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    // Validate withdrawal amount
    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Check for sufficient balance
    if (accounts[index].balance < amount) {
        printf("Insufficient funds. Your current balance is %.2lf\n", accounts[index].balance);
        return;
    }

    // Perform withdrawal
    accounts[index].balance -= amount;
    printf("Withdrawal successful! New balance: %.2lf\n", accounts[index].balance);
}

// Function to display all bank accounts
void displayAccounts(BankAccount *accounts, int accountCount) {
    printf("\nAll Bank Accounts:\n");
    for (int i = 0; i < accountCount; i++) {
        printf("Account Number: %d\n", accounts[i].accountNumber);
        printf("Account Holder: %s\n", accounts[i].accountHolder);
        printf("Balance: %.2lf\n", accounts[i].balance);
        printf("----------------------\n");
    }
}

// Function to find an account by account number
int findAccount(BankAccount *accounts, int accountCount, int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i; // Account found, return index
        }
    }
    return -1; // Account not found
}
