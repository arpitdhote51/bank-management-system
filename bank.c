#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define INITIAL_ACCOUNT_COUNT 10

typedef struct {
    int accountNumber;
    char accountHolder[MAX_NAME_LENGTH];
    double balance;
} BankAccount;

int main() {
    int accountCapacity = INITIAL_ACCOUNT_COUNT, accountCount = 0, choice;
    BankAccount *accounts = malloc(accountCapacity * sizeof(BankAccount));

    if (!accounts) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    do {
        printf("\nBank of Koradi - Welcome!\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Display Accounts\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (accountCount >= accountCapacity) {
                accountCapacity *= 2;
                accounts = realloc(accounts, accountCapacity * sizeof(BankAccount));
                if (!accounts) {
                    printf("Memory reallocation failed.\n");
                    break;
                }
            }
            BankAccount *newAccount = &accounts[accountCount++];
            newAccount->accountNumber = accountCount;
            printf("Enter account holder name: ");
            scanf(" %[^\n]", newAccount->accountHolder);
            newAccount->balance = 0.0;
            printf("Account created successfully! Account number: %d\n", newAccount->accountNumber);
        } else if (choice == 2 || choice == 3) {
            int accountNumber, found = 0;
            double amount;
            printf("Enter account number: ");
            scanf("%d", &accountNumber);

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].accountNumber == accountNumber) {
                    found = 1;
                    printf("Enter amount to %s: ", choice == 2 ? "deposit" : "withdraw");
                    scanf("%lf", &amount);
                    if (amount <= 0) {
                        printf("Invalid amount. Please enter a positive value.\n");
                    } else if (choice == 3 && accounts[i].balance < amount) {
                        printf("Insufficient funds. Current balance: %.2lf\n", accounts[i].balance);
                    } else {
                        accounts[i].balance += (choice == 2 ? amount : -amount);
                        printf("%s successful! New balance: %.2lf\n",
                               choice == 2 ? "Deposit" : "Withdrawal", accounts[i].balance);
                    }
                    break;
                }
            }
            if (!found) printf("Account not found.\n");
        } else if (choice == 4) {
            printf("\nAll Bank Accounts:\n");
            for (int i = 0; i < accountCount; i++) {
                printf("Account Number: %d\nAccount Holder: %s\nBalance: %.2lf\n", 
                       accounts[i].accountNumber, accounts[i].accountHolder, accounts[i].balance);
                printf("----------------------\n");
            }
        } else if (choice != 5) {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free(accounts);
    printf("Exiting the program. Thank you for visiting Bank of Koradi!\n");
    return 0;
}
