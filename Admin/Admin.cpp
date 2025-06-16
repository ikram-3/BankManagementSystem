#include "Admin.h"
#include "../Utils/FileManager.h"
#include "../Utils/Validation.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

Admin::Admin() {
    // Load default credentials (can also load from file if needed)
    adminUsername = "admin";
    adminPassword = "admin123";
}

bool Admin::login(const string& username, const string& password) {
    return (username == adminUsername && password == adminPassword);
}

void Admin::changePassword() {
    string oldPass, newPass;
    cout << "Enter current password: ";
    cin >> oldPass;

    if (oldPass != adminPassword) {
        cout << "Incorrect password!\n";
        return;
    }

    cout << "Enter new password (min 6 chars): ";
    cin >> newPass;

    if (!Validation::isValidPassword(newPass)) {
        cout << "Invalid password length!\n";
        return;
    }

    adminPassword = newPass;
    cout << "Password changed successfully.\n";
}

// ==================== ACCOUNT MANAGEMENT ====================

void Admin::viewAllAccounts() {
    vector<Account> accounts = FileManager::loadAllAccounts();

    cout << left << setw(12) << "Acc No"
         << setw(20) << "Name"
         << setw(15) << "Phone"
         << setw(10) << "Type"
         << setw(10) << "Balance" << endl;
    cout << string(70, '-') << endl;

    for (const auto& acc : accounts) {
        if (acc.getStatus()) {
            cout << left << setw(12) << acc.getAccountNumber()
                 << setw(20) << acc.getName()
                 << setw(15) << acc.getPhone()
                 << setw(10) << acc.getAccountType()
                 << setw(10) << fixed << setprecision(2) << acc.getBalance() << endl;
        }
    }
}

void Admin::searchAccountByNumber(int accNo) {
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (const auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo) {
            acc.displayAccountInfo(true);
            return;
        }
    }
    cout << "Account not found.\n";
}

void Admin::deleteAccount(int accNo) {
    vector<Account> accounts = FileManager::loadAllAccounts();
    bool deleted = false;

    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo && acc.getStatus()) {
            acc.setStatus(false);
            deleted = true;

            // Log
            Transaction tx(accNo, "2025-06-16", "Deleted", 0, acc.getBalance());
            FileManager::logTransaction(tx);

            break;
        }
    }

    FileManager::saveAllAccounts(accounts);

    if (deleted) cout << "Account marked as deleted.\n";
    else cout << "Account not found or already deleted.\n";
}

void Admin::editAccount(int accNo) {
    vector<Account> accounts = FileManager::loadAllAccounts();
    bool edited = false;

    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo && acc.getStatus()) {
            string newName, newPhone;

            cout << "Current Name: " << acc.getName() << "\nNew Name: ";
            cin.ignore(); getline(cin, newName);
            cout << "Current Phone: " << acc.getPhone() << "\nNew Phone: ";
            getline(cin, newPhone);

            if (!Validation::isValidPhone(newPhone)) {
                cout << "Invalid phone number format!\n";
                return;
            }

            acc.setName(newName);
            acc.setPhone(newPhone);
            edited = true;

            // Log
            Transaction tx(accNo, "2025-06-16", "Edit Info", 0, acc.getBalance());
            FileManager::logTransaction(tx);
            break;
        }
    }

    FileManager::saveAllAccounts(accounts);

    if (edited) cout << "Account info updated.\n";
    else cout << "Account not found.\n";
}

// ==================== TRANSACTIONS ====================

void Admin::viewAccountTransactions(int accNo) {
    vector<Transaction> txs = FileManager::loadTransactions(accNo);

    if (txs.empty()) {
        cout << "No transaction history found.\n";
        return;
    }

    cout << "\nTransaction History for Account #" << accNo << ":\n";
    cout << left << setw(15) << "Date"
         << setw(15) << "Type"
         << setw(15) << "Amount"
         << setw(15) << "Balance" << endl;
    cout << string(60, '-') << endl;

    for (const auto& tx : txs) {
        tx.display();
    }
}

void Admin::showAccountStatement(int accNo) {
    vector<Account> accounts = FileManager::loadAllAccounts();
    Account acc;
    bool found = false;

    for (const auto& a : accounts) {
        if (a.getAccountNumber() == accNo && a.getStatus()) {
            acc = a;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
        return;
    }

    cout << "\n=========== BANK STATEMENT ===========\n";
    acc.displayAccountInfo(false);
    cout << "\n------ TRANSACTION HISTORY ------\n";
    viewAccountTransactions(accNo);
    cout << "======================================\n";
}
