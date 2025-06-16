
# 💳 Bank Management System (BMS)

A console-based **Bank Management System** built using **C++**, applying key Object-Oriented Programming concepts with file-based storage. This project features secure login, customer/admin roles, transaction history, and editable accounts.

---

## 🧰 Features

### 🔐 Admin Panel
- Login with username/password
- View/Search/Delete accounts
- Edit account name or phone
- View transaction history
- Show full account statement
- Change admin password

### 👤 Customer Panel
- Register (must be 18+)
- Login using account number and 4-digit PIN
- Deposit and Withdraw money
- Check balance
- View transaction history
- Show account statement
- Change password/PIN
- Update name/phone
- Delete own account

---

## 🧠 Technologies Used

- Language: **C++**
- Concepts: Classes, Inheritance, Encapsulation, File Handling
- Storage: `accounts.txt`, `transactions.txt`, `logins.txt`
- UI: Clean, console-based interaction

---

## 📁 File Structure

```

BankManagementSystem/
│
├── main.cpp
├── README.md
│
├── Admin/
│   ├── Admin.h
│   └── Admin.cpp
│
├── Customer/
│   ├── Customer.h
│   └── Customer.cpp
│
├── Models/
│   ├── Account.h
│   └── Transaction.h
│
├── Utils/
│   ├── Validation.h
│   └── FileManager.h
│
└── data/
├── accounts.txt
├── transactions.txt
└── logins.txt

````

---

## ⚙️ Quick Setup (Create Folder & Files Automatically)

> 🪟 For Windows PowerShell users — run this command to generate all folders and empty files:

```powershell
mkdir BankManagementSystem; cd BankManagementSystem;
New-Item main.cpp -ItemType File;
mkdir Admin; New-Item Admin/Admin.h, Admin/Admin.cpp -ItemType File;
mkdir Customer; New-Item Customer/Customer.h, Customer/Customer.cpp -ItemType File;
mkdir Utils; New-Item Utils/Validation.h, Utils/FileManager.h -ItemType File;
mkdir Models; New-Item Models/Account.h,Models/Account.cpp,Models/Transaction.h -ItemType File;
mkdir data; New-Item data/accounts.txt, data/transactions.txt, data/logins.txt -ItemType File;
New-Item README.md -ItemType File;
tree /F
````

---

## 🧪 How to Compile & Run

```bash
g++ main.cpp Admin/Admin.cpp Customer/Customer.cpp -o bms
```
## Run 
```
./bms
```

✅ Make sure your `data/` folder and `.txt` files exist before running.

---

## ✍ Author

**Muhammad Ikram**
Swat, Pakistan
📚 Passionate Learner | 💻 Data Science & Software Engineering Student

---

## 📌 License

Open for educational and learning purposes. Give credit if you reuse, enhance, or publish.


