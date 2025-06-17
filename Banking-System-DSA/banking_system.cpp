#include <iostream>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;
public:
    BankAccount(int n, string name, double b) {
        accountNumber = n;
        accountHolderName = name;
        balance = b;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn. New Balance: " << balance << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    virtual void calculateInterest() {
    }

    void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
    double interestRate;
public:
    SavingsAccount(int n, string name, double b, double rate)
        : BankAccount(n, name, b), interestRate(rate) {}

    void calculateInterest() {
        double interest = balance * interestRate / 100;
        cout << "Interest (Savings): " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
    double overdraftLimit;
public:
    CheckingAccount(int n, string name, double b, double limit)
        : BankAccount(n, name, b), overdraftLimit(limit) {}

    void calculateInterest() {
        cout << "No interest for Checking Account." << endl;
    }
};

class FixedDepositAccount : public BankAccount {
    int term;
public:
    FixedDepositAccount(int n, string name, double b, int t)
        : BankAccount(n, name, b), term(t) {}

    void calculateInterest() {
        double interest = balance * 5 * term / 100;
        cout << "Interest (Fixed Deposit): " << interest << endl;
    }
};

int main() {
    SavingsAccount savings(1, "Ram", 5000, 4);
    CheckingAccount checking(2, "Shyam", 3000, 1000);
    FixedDepositAccount fixed(3, "Geeta", 10000, 12);

    BankAccount* acc = nullptr;
    int choice;

    while (true) {
        cout << "\nChoose Account:\n1. Savings\n2. Checking\n3. Fixed Deposit\n4. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) acc = &savings;
        else if (choice == 2) acc = &checking;
        else if (choice == 3) acc = &fixed;
        else break;

        int action;
        cout << "\nChoose Action:\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Interest\n5. Account Info\nAction: ";
        cin >> action;

        if (action == 1) {
            double amt;
            cout << "Amount to deposit: ";
            cin >> amt;
            acc->deposit(amt);
        } else if (action == 2) {
            double amt;
            cout << "Amount to withdraw: ";
            cin >> amt;
            acc->withdraw(amt);
        } else if (action == 3) {
            cout << "Balance: " << acc->getBalance() << endl;
        } else if (action == 4) {
            acc->calculateInterest();
        } else if (action == 5) {
            acc->displayAccountInfo();
        }
    }

    return 0;
}
