#ifndef ADMIN_H
#define ADMIN_H

#include "../Models/Account.h"
#include "../Models/Transaction.h"
#include <vector>
#include <string>

class Admin {
private:
    string adminUsername;
    string adminPassword;

public:
    Admin();

    // Admin authentication
    bool login(const string& username, const string& password);
    void changePassword();

    // Account management
    void viewAllAccounts();
    void searchAccountByNumber(int accNo);
    void deleteAccount(int accNo);
    void editAccount(int accNo); // Edit name, phone, etc.

    // Transactions
    void viewAccountTransactions(int accNo);
    void showAccountStatement(int accNo); // Professional look
};

#endif
