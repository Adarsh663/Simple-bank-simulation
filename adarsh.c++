#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ATM {
private:
    string accNo, name, pin;
    double balance;

public:
    ATM() : balance(0.0) {}

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Set 4-digit PIN: ";
        cin >> pin;
        balance = 0.0;
        saveToFile();
        cout << "Account created successfully!\n";
    }

    bool login(string acc, string p) {
        ifstream fin("accounts.txt");
        string a, n, pw;
        double b;
        while (fin >> a >> n >> pw >> b) {
            if (a == acc && pw == p) {
                accNo = a;
                name = n;
                pin = pw;
                balance = b;
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }

    void menu() {
        int choice;
        do {
            cout << "\n==== ATM MENU ====";
            cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Balance: ₹" << balance << endl;
                    break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: saveToFile(); cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    void deposit() {
        double amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
        cout << "Deposited successfully!\n";
    }

    void withdraw() {
        double amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        if (amt > balance)
            cout << "Insufficient balance!\n";
        else {
            balance -= amt;
            cout << "Withdrawal successful!\n";
        }
    }

    void saveToFile() {
        ifstream fin("accounts.txt");
        ofstream temp("temp.txt");
        string a, n, p;
        double b;
        bool found = false;
        while (fin >> a >> n >> p >> b) {
            if (a == accNo) {
                temp << accNo << " " << name << " " << pin << " " << balance << "\n";
                found = true;
            } else
                temp << a << " " << n << " " << p << " " << b << "\n";
        }
        fin.close();
        if (!found)
            temp << accNo << " " << name << " " << pin << " " << balance << "\n";
        temp.close();
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
};

int main() {
    ATM atm;
    int choice;
    string acc, pin;
    cout << "==== WELCOME TO SIMPLE ATM SYSTEM ====" << endl;
    cout << "1. Create Account\n2. Login\nEnter choice: ";
    cin >> choice;
    if (choice == 1) atm.createAccount();
    else if (choice == 2) {
        cout << "Enter Account Number: ";
        cin >> acc;
        cout << "Enter PIN: ";
        cin >> pin;
        if (atm.login(acc, pin)) atm.menu();
        else cout << "Invalid login details!\n";
    } else cout << "Invalid choice!\n";
    return 0;
}
