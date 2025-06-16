#include "Customer.h"
#include "../Utils/FileManager.h"
#include "../Utils/Validation.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

Customer::Customer() {}

bool Customer::registerAccount() {
    string name, cnic, phone, dob, accType, password, pin;
    double initialDeposit;
    int accNo;

    cout << "Enter Name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter CNIC (xxxxx-xxxxxxx-x): ";
    getline(cin, cnic);
    if (!Validation::isValidCNIC(cnic)) {
        cout << "Invalid CNIC format!\n";
        return false;
    }

    cout << "Enter Phone (03XXXXXXXXX): ";
    getline(cin, phone);
    if (!Validation::isValidPhone(phone)) {
        cout << "Invalid phone format!\n";
        return false;
    }

    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    getline(cin, dob);
    if (!Validation::isAdult(dob)) {
        cout << "You must be at least 18 years old.\n";
        return false;
    }

    cout << "Enter Account Type (Savings/Current): ";
    getline(cin, accType);

    cout << "Create a password (min 6 chars): ";
    getline(cin, password);
    if (!Validation::isValidPassword(password)) {
        cout << "Password too short.\n";
        return false;
    }

    cout << "Create 4-digit PIN: ";
    getline(cin, pin);
    if (!Validation::isValidPIN(pin)) {
        cout << "PIN must be 4 digits.\n";
        return false;
    }

    cout << "Enter Initial Deposit: ";
    cin >> initialDeposit;

    // Generate unique account number
    vector<Account> accounts = FileManager::loadAllAccounts();
    accNo = (accounts.empty()) ? 1001 : accounts.back().getAccountNumber() + 1;

    // Set up account
    account = Account();
    account.setName(name);
    account.setPhone(phone);
    account.setStatus(true);
    account.setBalance(initialDeposit);

    // Set private values via loading
    string line = to_string(accNo) + "," + name + "," + cnic + "," + phone + "," + dob + "," +
                  accType + "," + password + "," + pin + "," + to_string(initialDeposit) + ",1";
    account.loadFromLine(line);
    accounts.push_back(account);
    FileManager::saveAllAccounts(accounts);

    // Log initial transaction
    Transaction tx(accNo, "2025-06-16", "Account Created", initialDeposit, initialDeposit);
    FileManager::logTransaction(tx);

    cout << "Account created successfully! Your account number is: " << accNo << endl;
    return true;
}

bool Customer::login(int accNo, const string& pin) {
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (const auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo && acc.getPIN() == pin && acc.getStatus()) {
            account = acc;
            return true;
        }
    }
    return false;
}

void Customer::deposit(double amount) {
    double newBalance = account.getBalance() + amount;
    account.setBalance(newBalance);
    FileManager::logTransaction(Transaction(account.getAccountNumber(), "2025-06-16", "Deposit", amount, newBalance));

    // Save to file
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setBalance(newBalance);
    FileManager::saveAllAccounts(accounts);

    cout << "Deposit successful. New balance: " << newBalance << endl;
}

void Customer::withdraw(double amount) {
    if (amount > account.getBalance()) {
        cout << "Insufficient balance.\n";
        return;
    }

    double newBalance = account.getBalance() - amount;
    account.setBalance(newBalance);
    FileManager::logTransaction(Transaction(account.getAccountNumber(), "2025-06-16", "Withdraw", amount, newBalance));

    // Save to file
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setBalance(newBalance);
    FileManager::saveAllAccounts(accounts);

    cout << "Withdraw successful. New balance: " << newBalance << endl;
}

void Customer::viewBalance() const {
    cout << "Your current balance: Rs. " << fixed << setprecision(2) << account.getBalance() << endl;
}

void Customer::viewTransactionHistory() const {
    auto txs = FileManager::loadTransactions(account.getAccountNumber());
    if (txs.empty()) {
        cout << "No transaction history.\n";
        return;
    }

    cout << "\n--- Transaction History ---\n";
    cout << left << setw(15) << "Date" << setw(15) << "Type"
         << setw(15) << "Amount" << setw(15) << "Balance" << endl;
    cout << string(60, '-') << endl;

    for (const auto& tx : txs)
        tx.display();
}

void Customer::showAccountStatement() const {
    cout << "\n=========== ACCOUNT STATEMENT ===========\n";
    account.displayAccountInfo(false);
    viewTransactionHistory();
    cout << "=========================================\n";
}

void Customer::changePassword() {
    string oldPass, newPass;
    cout << "Enter current password: ";
    cin >> oldPass;

    if (oldPass != account.getPassword()) {
        cout << "Incorrect password.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPass;
    if (!Validation::isValidPassword(newPass)) {
        cout << "Too short.\n";
        return;
    }

    account.setPassword(newPass);
    cout << "Password updated.\n";

    // Save
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setPassword(newPass);
    FileManager::saveAllAccounts(accounts);
}

void Customer::changePIN() {
    string oldPIN, newPIN;
    cout << "Enter current PIN: ";
    cin >> oldPIN;

    if (oldPIN != account.getPIN()) {
        cout << "Incorrect PIN.\n";
        return;
    }

    cout << "Enter new 4-digit PIN: ";
    cin >> newPIN;
    if (!Validation::isValidPIN(newPIN)) {
        cout << "Invalid format.\n";
        return;
    }

    account.setPIN(newPIN);
    cout << "PIN updated.\n";

    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setPIN(newPIN);
    FileManager::saveAllAccounts(accounts);
}

void Customer::updateName() {
    string newName;
    cout << "Enter new name: ";
    cin.ignore(); getline(cin, newName);

    account.setName(newName);
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setName(newName);
    FileManager::saveAllAccounts(accounts);

    cout << "Name updated.\n";
}

void Customer::updatePhone() {
    string newPhone;
    cout << "Enter new phone: ";
    cin >> newPhone;

    if (!Validation::isValidPhone(newPhone)) {
        cout << "Invalid format.\n";
        return;
    }

    account.setPhone(newPhone);
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts)
        if (acc.getAccountNumber() == account.getAccountNumber())
            acc.setPhone(newPhone);
    FileManager::saveAllAccounts(accounts);

    cout << "Phone updated.\n";
}

void Customer::deleteOwnAccount() {
    vector<Account> accounts = FileManager::loadAllAccounts();
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == account.getAccountNumber()) {
            acc.setStatus(false);
            FileManager::logTransaction(Transaction(acc.getAccountNumber(), "2025-06-16", "Customer Delete", 0, acc.getBalance()));
            cout << "Your account has been deactivated.\n";
            break;
        }
    }
    FileManager::saveAllAccounts(accounts);
}

int Customer::getAccountNumber() const {
    return account.getAccountNumber();
}
