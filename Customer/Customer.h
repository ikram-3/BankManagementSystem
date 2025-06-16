#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../Models/Account.h"
#include "../Models/Transaction.h"
#include <string>

class Customer {
private:
    Account account;

public:
    Customer();

    // Login and registration
    bool registerAccount();            // Must be 18+
    bool login(int accNo, const string& pin);

    // Core banking features
    void deposit(double amount);
    void withdraw(double amount);
    void viewBalance() const;
    void viewTransactionHistory() const;
    void showAccountStatement() const;

    // Personal info update
    void changePassword();
    void changePIN();
    void updateName();
    void updatePhone();

    // Account management
    void deleteOwnAccount();

    // Load/save
    int getAccountNumber() const;
};

#endif
