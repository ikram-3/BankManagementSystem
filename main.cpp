#include <iostream>
#include <string>
#include "Admin/Admin.h"
#include "Customer/Customer.h"

using namespace std;

void adminMenu() {
    Admin admin;
    string username, password;

    cout << "\n--- Admin Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!admin.login(username, password)) {
        cout << "Access Denied.\n";
        return;
    }

    int choice, accNo;
    while (true) {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. View All Accounts\n";
        cout << "2. Search Account\n";
        cout << "3. Delete Account\n";
        cout << "4. Edit Account Info\n";
        cout << "5. View Account Transactions\n";
        cout << "6. Show Account Statement\n";
        cout << "7. Change Admin Password\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: admin.viewAllAccounts(); break;
            case 2:
                cout << "Enter Account No: "; cin >> accNo;
                admin.searchAccountByNumber(accNo);
                break;
            case 3:
                cout << "Enter Account No: "; cin >> accNo;
                admin.deleteAccount(accNo);
                break;
            case 4:
                cout << "Enter Account No: "; cin >> accNo;
                admin.editAccount(accNo);
                break;
            case 5:
                cout << "Enter Account No: "; cin >> accNo;
                admin.viewAccountTransactions(accNo);
                break;
            case 6:
                cout << "Enter Account No: "; cin >> accNo;
                admin.showAccountStatement(accNo);
                break;
            case 7:
                admin.changePassword();
                break;
            case 0:
                cout << "Logging out...\n"; return;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void customerMenu() {
    Customer customer;
    int choice, accNo;
    string pin;

    cout << "\n1. Register New Account\n2. Login to Existing Account\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        if (!customer.registerAccount())
            return;
    }

    cout << "\n--- Customer Login ---\n";
    cout << "Account Number: ";
    cin >> accNo;
    cout << "PIN: ";
    cin >> pin;

    if (!customer.login(accNo, pin)) {
        cout << "Invalid login.\n";
        return;
    }

    while (true) {
        cout << "\n--- Customer Dashboard ---\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transaction History\n";
        cout << "5. Account Statement\n";
        cout << "6. Change Password\n";
        cout << "7. Change PIN\n";
        cout << "8. Update Name\n";
        cout << "9. Update Phone\n";
        cout << "10. Delete My Account\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        double amt;
        switch (choice) {
            case 1: customer.viewBalance(); break;
            case 2:
                cout << "Amount to deposit: ";
                cin >> amt;
                customer.deposit(amt);
                break;
            case 3:
                cout << "Amount to withdraw: ";
                cin >> amt;
                customer.withdraw(amt);
                break;
            case 4: customer.viewTransactionHistory(); break;
            case 5: customer.showAccountStatement(); break;
            case 6: customer.changePassword(); break;
            case 7: customer.changePIN(); break;
            case 8: customer.updateName(); break;
            case 9: customer.updatePhone(); break;
            case 10: customer.deleteOwnAccount(); return;
            case 0: cout << "Logging out...\n"; return;
            default: cout << "Invalid option.\n";
        }
    }
}

int main() {
    int mainChoice;
    while (true) {
        cout << "\n====== Bank Management System ======\n";
        cout << "1. Admin Panel\n";
        cout << "2. Customer Panel\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: adminMenu(); break;
            case 2: customerMenu(); break;
            case 0:
                cout << "Thank you. Exiting...\n";
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
}
