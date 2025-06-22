#include <iostream>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;
public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual void calculateInterest() {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }

    virtual void withdraw(double amount) {
        if (amount > balance)
            cout << "Insufficient balance." << endl;
        else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        }
    }

    double getBalance() { return balance; }
    int getAccountNumber() { return accountNumber; }
    virtual void display() {
        cout << "-----------------------------" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance       : $" << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
    double interestRate;
public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal), interestRate(rate) {}

    void calculateInterest() override {
        double interest = getBalance() * interestRate / 100;
        cout << "Interest (Savings): $" << interest << endl;
    }

    void display() override {
        BankAccount::display();
        cout << "Account Type   : Savings" << endl;
        cout << "-----------------------------" << endl;
    }
};

class CheckingAccount : public BankAccount {
    double overdraft;
public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal), overdraft(limit) {}

    void withdraw(double amount) override {
        if (amount <= getBalance() + overdraft) {
            double bal = getBalance();
            if (amount > bal) {
                cout << "Withdrawn: $" << bal << endl;
                cout << "Overdraft used: $" << amount - bal << endl;
            } else {
                cout << "Withdrawn: $" << amount << endl;
            }
        } else {
            cout << "Overdraft limit exceeded." << endl;
        }
    }

    void calculateInterest() override {
        cout << "No interest for Checking Account." << endl;
    }

    void display() override {
        BankAccount::display();
        cout << "Account Type   : Checking" << endl;
        cout << "-----------------------------" << endl;
    }
};

class FixedDepositAccount : public BankAccount {
    int term;
public:
    FixedDepositAccount(int accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal), term(t) {}

    void calculateInterest() override {
        double interest = getBalance() * 5 * term / 100;
        cout << "Interest (Fixed Deposit): $" << interest << endl;
    }

    void display() override {
        BankAccount::display();
        cout << "Account Type   : Fixed Deposit" << endl;
        cout << "Term Duration  : " << term << " months" << endl;
        cout << "-----------------------------" << endl;
    }
};

int main() {
    BankAccount* accounts[10];
    int count = 0;
    int choice;

    do {
        cout << endl;
        cout << "=== BANKING SYSTEM MENU ===" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Display All Accounts" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Display Balance" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo; string name; double bal, rate;
            cout << "Enter Account Number: "; cin >> accNo;
            cout << "Enter Account Holder Name: "; cin >> name;
            cout << "Enter Initial Balance: "; cin >> bal;
            cout << "Enter Interest Rate (%): "; cin >> rate;
            accounts[count++] = new SavingsAccount(accNo, name, bal, rate);
            cout << "Savings Account created successfully." << endl;
        } else if (choice == 2) {
            int accNo; string name; double bal, limit;
            cout << "Enter Account Number: "; cin >> accNo;
            cout << "Enter Account Holder Name: "; cin >> name;
            cout << "Enter Initial Balance: "; cin >> bal;
            cout << "Enter Overdraft Limit: "; cin >> limit;
            accounts[count++] = new CheckingAccount(accNo, name, bal, limit);
            cout << "Checking Account created successfully." << endl;
        } else if (choice == 3) {
            int accNo, term; string name; double bal;
            cout << "Enter Account Number: "; cin >> accNo;
            cout << "Enter Account Holder Name: "; cin >> name;
            cout << "Enter Initial Balance: "; cin >> bal;
            cout << "Enter Term Duration (months): "; cin >> term;
            accounts[count++] = new FixedDepositAccount(accNo, name, bal, term);
            cout << "Fixed Deposit Account created successfully." << endl;
        } else if (choice == 4) {
            int index; double amt;
            cout << "Enter Account Index (0 to " << count-1 << "): "; cin >> index;
            cout << "Enter Amount to Deposit: "; cin >> amt;
            accounts[index]->deposit(amt);
        } else if (choice == 5) {
            int index; double amt;
            cout << "Enter Account Index (0 to " << count-1 << "): "; cin >> index;
            cout << "Enter Amount to Withdraw: "; cin >> amt;
            accounts[index]->withdraw(amt);
        } else if (choice == 6) {
            for (int i = 0; i < count; i++) {
                cout << "--- Account [" << i << "] ---" << endl;
                accounts[i]->display();
            }
        } else if (choice == 7) {
            for (int i = 0; i < count; i++) {
                accounts[i]->calculateInterest();
            }
        } else if (choice == 8) {
            for (int i = 0; i < count; i++) {
                cout << "Balance for Account [" << i << "]: $" << accounts[i]->getBalance() << endl;
            }
        } else if (choice == 9) {
            cout << "Thank you for using the Banking System." << endl;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 9);

    for (int i = 0; i < count; i++) {
        delete accounts[i];
    }

    return 0;
}
