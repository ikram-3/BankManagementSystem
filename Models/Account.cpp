#include "Account.h"
#include <sstream>
#include <iostream>

Account::Account() {
    accountNumber = 0;
    name = cnic = phone = dob = accountType = password = pin = "";
    balance = 0;
    isActive = true;
}

int Account::getAccountNumber() const { return accountNumber; }
string Account::getName() const { return name; }
string Account::getCNIC() const { return cnic; }
string Account::getPhone() const { return phone; }
string Account::getDOB() const { return dob; }
string Account::getAccountType() const { return accountType; }
string Account::getPassword() const { return password; }
string Account::getPIN() const { return pin; }
double Account::getBalance() const { return balance; }
bool Account::getStatus() const { return isActive; }

void Account::setName(const string& newName) { name = newName; }
void Account::setPhone(const string& newPhone) { phone = newPhone; }
void Account::setPassword(const string& newPass) { password = newPass; }
void Account::setPIN(const string& newPIN) { pin = newPIN; }
void Account::setStatus(bool status) { isActive = status; }
void Account::setBalance(double newBalance) { balance = newBalance; }

void Account::loadFromLine(const string& line) {
    stringstream ss(line);
    string token;

    getline(ss, token, ','); accountNumber = stoi(token);
    getline(ss, name, ',');
    getline(ss, cnic, ',');
    getline(ss, phone, ',');
    getline(ss, dob, ',');
    getline(ss, accountType, ',');
    getline(ss, password, ',');
    getline(ss, pin, ',');
    getline(ss, token, ','); balance = stod(token);
    getline(ss, token); isActive = (token == "1");
}

string Account::toLine() const {
    return to_string(accountNumber) + "," + name + "," + cnic + "," + phone + "," +
           dob + "," + accountType + "," + password + "," + pin + "," +
           to_string(balance) + "," + (isActive ? "1" : "0");
}

void Account::displayAccountInfo(bool showSensitive) const {
    cout << "\n--- Account Details ---\n";
    cout << "Account #: " << accountNumber << "\n";
    cout << "Name     : " << name << "\n";
    cout << "CNIC     : " << cnic << "\n";
    cout << "Phone    : " << phone << "\n";
    cout << "DOB      : " << dob << "\n";
    cout << "Type     : " << accountType << "\n";
    cout << "Balance  : Rs. " << balance << "\n";
    if (showSensitive) {
        cout << "Password : " << password << "\n";
        cout << "PIN      : " << pin << "\n";
    }
}
