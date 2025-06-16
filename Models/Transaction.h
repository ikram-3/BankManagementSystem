#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Transaction {
private:
    int accountNumber;
    string date;
    string type;         // Deposit, Withdraw, Create, Delete, etc.
    double amount;
    double balanceAfter;

public:
    Transaction() {}

    Transaction(int accNo, string d, string t, double amt, double balAfter)
        : accountNumber(accNo), date(d), type(t), amount(amt), balanceAfter(balAfter) {}

    // Converts to line for file writing
    string toLine() const {
        return to_string(accountNumber) + "," + date + "," + type + "," +
               to_string(amount) + "," + to_string(balanceAfter);
    }

    // Load from CSV line
    void loadFromLine(const string& line) {
        size_t pos = 0;
        string tokens[5];
        string temp = line;
        for (int i = 0; i < 5; ++i) {
            pos = temp.find(',');
            tokens[i] = temp.substr(0, pos);
            temp.erase(0, pos + 1);
        }

        accountNumber = stoi(tokens[0]);
        date = tokens[1];
        type = tokens[2];
        amount = stod(tokens[3]);
        balanceAfter = stod(tokens[4]);
    }

    // Display transaction info
    void display() const {
        cout << left << setw(15) << date
             << setw(15) << type
             << setw(15) << amount
             << setw(15) << balanceAfter << endl;
    }

    int getAccountNumber() const { return accountNumber; }
};

#endif
