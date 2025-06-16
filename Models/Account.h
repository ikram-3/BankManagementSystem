#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
using namespace std;

class Account {
protected:
    int accountNumber;
    string name;
    string cnic;
    string phone;
    string dob;
    string accountType;   // Savings / Current
    string password;
    string pin;
    double balance;
    bool isActive;

public:
    Account();

    // Getters
    int getAccountNumber() const;
    string getName() const;
    string getCNIC() const;
    string getPhone() const;
    string getDOB() const;
    string getAccountType() const;
    string getPassword() const;
    string getPIN() const;
    double getBalance() const;
    bool getStatus() const;

    // Setters / Modifiers
    void setName(const string&);
    void setPhone(const string&);
    void setPassword(const string&);
    void setPIN(const string&);
    void setStatus(bool);
    void setBalance(double);

    // Other methods
    void loadFromLine(const string& line);
    string toLine() const;
    void displayAccountInfo(bool showSensitive = false) const;
};

#endif
