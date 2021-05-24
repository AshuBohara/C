#include <stdio.h>
#include <windows.h>

typedef struct {
	char name[30];
	int account_no;
	int balance;
	char address[30];

} bank_account;

int no_account = 0;

void create_account() {
	char temp;
	bank_account acc;
	gets(&temp);
	printf("      Enter your name:    ");
	scanf_s("%[^\n]", acc.name, 30);
	printf("      Enter your address: ");
	gets(&temp);
	scanf_s("%[^\n]", acc.address, 30);

	acc.account_no = 101 + no_account;
	acc.balance = 0;

	FILE* datafile = fopen("accounts.txt", "a");
	fseek(datafile, 0, SEEK_END);
	fprintf(datafile, "%s\t%d\t%d\t%s\n", acc.name,
										acc.account_no,
										acc.balance,
										acc.address);

	fclose(datafile);

	printf("Your account has been created, %s. Your account number is %d. Please remember this number.\n", acc.name, acc.account_no);

}

void update(int number, int change) {
	FILE* file = fopen("accounts.txt", "r");
	FILE* copy = fopen("temp.txt", "a+");
	bank_account temp;
	int updated = 0, new_num, new_change;

	while (!feof(file)) {
		fscanf(file, "%[^\t]\t", temp.name);
		fscanf(file, "%d\t", &temp.account_no);
		fscanf(file, "%d\t", &temp.balance);
		fscanf(file, "%[^\t^\n]\n", temp.address);

		if (temp.account_no == number){
            if((temp.balance+change)<0){
                do{
                    printf("Insufficient Balance!\n");
                    printf("Please enter a value less than your balance (Rs %d): ",temp.balance);
                    scanf("%d",&new_change);
                    change = (-1)*new_change;
                }while ((temp.balance+change)<0);
            }
            temp.balance += change;
            updated = 1;
            if (change<0){
                printf("You withdrew Rs %d from your account. Your new balance is Rs %d.", (-1)*change, temp.balance);
            }
            else{
                printf("You deposited Rs %d in your account. Your new balance is Rs %d.", change, temp.balance);
            }
		}

		fprintf(copy, "%s\t%d\t%d\t%s\n", temp.name,
										temp.account_no,
										temp.balance,
										temp.address);
	}
    if (!updated){
        printf("The account number you entered did not match with the existing account numbers.\nPlease enter another number or press 0 to cancel. ");
        scanf("%d", &new_num);
        if (new_num == 0){
            fclose(copy);
            fclose(file);
            remove("accounts.txt");
            rename("temp.txt", "accounts.txt");
            return;
        }
        else{
            update(new_num, change);
        }
    }
	fclose(copy);
	fclose(file);
	remove("accounts.txt");
	rename("temp.txt", "accounts.txt");
	return;



}

void show_balance(int account_number) {
	int present = 0;
	bank_account acc;
	FILE* temp = fopen("accounts.txt", "r");
	while(!feof(temp)){
        fscanf(temp, "%[^\t]\t", acc.name);
		fscanf(temp, "%d\t", &acc.account_no);
		fscanf(temp, "%d\t", &acc.balance);
		if(acc.account_no == account_number){
            printf("Your balance is Rs %d.\n", acc.balance);
            present = 1;
            break;
		}
	}
	fclose(temp);
	if (!present){
            int new_num;
        printf("The account number you entered is not found in our database.\nPlease enter another number or enter 0 to cancel.");
        scanf("%d",&new_num);
        if (new_num == 0){
            return;
        }
        else{
            show_balance(new_num);
        }
	}
}

/*void deposit_balance(int account_number) {
	for (int i = 0; i < no_account; i++) {
		if (account[i].account_no == account_number) {
			int amount;
			printf("How much would you like to deposit, %s? ", account[i].name);
			scanf_s("%d", &amount);
			account[i].balance += amount;
			printf("You deposited Rs.%d in your account. Your new balance is Rs.%d.", amount, account[i].balance);
		}
	}
	int amount;
	printf("How much would you like to deposit? ");
	scanf_s("%d", &amount);
	bank_account info = update(account_number, amount);
	printf("You deposited %d in your account, %s. Your new balance is %d.", info.name, info.balance);

}*/

/*void withdraw(int account_number) {
    FIlE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("copy.txt", "a");
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

	int amount;
	printf("How much would you like to withdraw? Your current balance is Rs.%d.",account[i].balance);
	if(amount)
    do {
        printf("How much would you like to withdraw? Your current balance is Rs.%d.",account[i].balance);
        scanf_s("%d", &amount);
    } while (amount > account[i].balance);
}*/

int main(){
	//bank_account* account;
	//account = (bank_account*)malloc(sizeof(bank_account) * max_accounts);
	FILE* datafile = fopen("accounts.txt", "a+");
	if (datafile == NULL) { printf("Unable to open the file. Please restart the program.\n"); }

	/*while (!feof(datafile)) {
		fscanf(datafile, "%[^\t]\t", account->name);
		fscanf(datafile, "%d\t", &account->account_no);
		fscanf(datafile, "%d\t", &account->balance);
		fscanf(datafile, "%[^\t]\t", account->address);
		no_account++;
		if((max_accounts - no_account)<2){
            max_accounts += 50;
            account = (bank_account*)realloc(account, max_accounts*sizeof(bank_account));
		}
	}*/

	while(!feof(datafile)){
        char temp;
        temp = getc(datafile);
        if (temp == '\n'){
            no_account++;
        }
	}

	fclose(datafile);

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
			create_account();
			printf("Please press any key to continue.");
			no_account++;
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 2) {
			int account_number;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			show_balance(account_number);
			printf("\nPlease press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 3) {
			int account_number, amount;
			char key;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			printf("How much would you like to deposit?");
			scanf("%d",&amount);
			update(account_number, amount);
			printf("\nPlease press any key to continue.");
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 4) {
			int account_number, amount;
			printf("Please enter your account number: ");
			scanf_s("%d", &account_number);
			printf("How much would you like to withdraw?");
			scanf_s("%d", &amount);
			update(account_number, (-1)*amount);
			printf("\nPlease press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
		else if (choice == 5) {
			break;
		}
		else {
			printf("Invalid Input\n");
			printf("Please press any key to continue.");
			char key;
			scanf("%c", &key);
			scanf("%c", &key);
		}
	}


return 0;

}
