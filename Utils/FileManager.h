#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../Models/Account.h"
#include "../Models/Transaction.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace FileManager {

    // 🔁 Load all accounts from file
    inline vector<Account> loadAllAccounts(const string& path = "data/accounts.txt") {
        vector<Account> accounts;
        ifstream file(path);
        string line;

        while (getline(file, line)) {
            Account acc;
            acc.loadFromLine(line);
            accounts.push_back(acc);
        }

        file.close();
        return accounts;
    }

    // 💾 Save all accounts (overwrite)
    inline void saveAllAccounts(const vector<Account>& accounts, const string& path = "data/accounts.txt") {
        ofstream file(path);
        for (const auto& acc : accounts) {
            file << acc.toLine() << endl;
        }
        file.close();
    }

    // 🔁 Load transactions for specific account
    inline vector<Transaction> loadTransactions(int accNo, const string& path = "data/transactions.txt") {
        vector<Transaction> txs;
        ifstream file(path);
        string line;

        while (getline(file, line)) {
            Transaction tx;
            tx.loadFromLine(line);
            if (tx.getAccountNumber() == accNo)
                txs.push_back(tx);
        }

        file.close();
        return txs;
    }

    inline void logTransaction(const Transaction& tx, const string& path = "data/transactions.txt") {
        ofstream file(path, ios::app);
        file << tx.toLine() << endl;
        file.close();
    }
}

#endif
