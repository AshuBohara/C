#include <stdio.h>
#include <windows.h>


typedef struct {
	int year;
	int month;
	int day;
} date;

typedef struct {
	char name[30];
	int account_no;
	date date_of_birth;
	int balance;
	char address[30];

} bank_account;

int max_accounts = 100;
int no_account = 0;
bank_account account[100];

int create_account() {
	char temp;
	gets(&temp);
	printf("Enter your name: \n");	
	scanf_s("%29[^\n]", account[no_account].name, 30);
	printf("Enter your year of birth: \n");
	scanf_s("%d", &account[no_account].date_of_birth.year);
	printf("Enter your month of birth: \n");
	scanf_s("%d", &account[no_account].date_of_birth.month);
	printf("Enter your day of birth: \n");
	scanf_s("%d", &account[no_account].date_of_birth.day);
	printf("Please enter your address: \n");
	gets(&temp);
	scanf_s("%29[^\n]", account[no_account].address, 30);

	account[no_account].balance = 0;
	account[no_account].account_no = 101 + no_account;
	no_account++;
	return account[no_account - 1].account_no;

}

void show_balance(int account_number) {
	for (int i = 0; i < no_account; i++) {
		if (account[i].account_no == account_number) {
			printf("Welcoome, %s . Your current balance is Rs.%d.", account[i].name, account[i].balance);
		}
	}
}

void deposit_balance(int account_number) {
	for (int i = 0; i < no_account; i++) {
		if (account[i].account_no == account_number) {
			int amount;
			printf("How much would you like to deposit, %s?", account[i].name);
			scanf_s("%d", &amount);
			account[i].balance += amount;
			printf("You deposited Rs.%d in your account. Your new balance is Rs.%d.", amount, account[i].balance);
		}
	}
}

void withdraw(int account_number) {
	for (int i = 0; i < no_account; i++) {
		if (account[i].account_no == account_number) {
			int amount;
			do {
				printf("How much would you like to withdraw? Your current balance is Rs.%d.",account[i].balance);
				scanf_s("%d", &amount);
			} while (amount > account[i].balance);
			account[i].balance -= amount;
			printf("You withdrew Rs.%d from your account. Your new balance is Rs.%d.", amount, account[i].balance);
		}
	}
}

int main(){
	while (1) {
		system("cls");

		int choice;
		printf("Hello, welcome to our bank.\n");
		printf("======================================\n");
		printf("What would you like to do?\n");
		printf("1: Create a new account.\n");
		printf("2: Check your balance.\n");
		printf("3: Deposit money.\n");
		printf("4: Withdraw money.\n");
		printf("5: Exit.\n");

		printf("Please enter the number associated with your choice: ");
		scanf_s("%d", &choice);

		if (choice == 1) {
			printf("Your account has been created. Your account number is %d. Please remember this number.\n", create_account());
			printf("Please press any key to continue.");
			Sleep(100);
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 2) {
			int account_number;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			show_balance(account_number);
			printf("Please press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 3) {
			int account_number;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			deposit_balance(account_number);
			printf("Please press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 4) {
			int account_number;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			withdraw(account_number);
			printf("Please press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 5) {
			break;
		}
		else {
			printf("Invalid Input");
			printf("Please press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
	}
	
	
return 0;

}