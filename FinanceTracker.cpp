#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Transaction {
    string name;
    string date;
    string description;
    double amount;
    string category;
};
const int MAX_TRANSACTIONS = 10;
Transaction transactions[MAX_TRANSACTIONS];
int numTransactions = 0;

bool validateAmount(double amount) {
    return (amount >= 0 && amount <= 10000);
}
 //Add Transaction
void addTransaction() {
    if (numTransactions < MAX_TRANSACTIONS) {
        Transaction newTransaction;

        cout << "Enter Your Full Name: ";
        cin.ignore();
        getline(cin, newTransaction.name);
        
        cout << "Enter Date (YYYY/MM/DD): ";
        cin.ignore();
        getline(cin, newTransaction.date);

        cout << "Enter description(purpose): "; 
        cin.ignore();
        getline(cin, newTransaction.description);
		
        cout << "Enter category(Tax,Savings,personal spending): ";
        getline(cin, newTransaction.category);

        string amountStr;
        do {
            cout << "Enter amount (0-10000): ";
            getline(cin, amountStr);
            stringstream(amountStr) >> newTransaction.amount;
            if (!validateAmount(newTransaction.amount)) {
                cout << "Invalid input! Amount must be between 0 and 10000." << endl;
            }
        } while (!validateAmount(newTransaction.amount));

        transactions[numTransactions++] = newTransaction;
        cout << "Transaction added successfully!" << endl;
    } else {
        cout << "Transaction limit reached." << endl;
    }
}

 //Find transaction
void findTransaction(const string& name) {
    bool found = false;
    for (int i = 0; i < numTransactions; ++i) {
        if (transactions[i].name == name) {
            cout << "Record found:" << endl;
            cout << "Name: " << transactions[i].name << endl;
            cout << "Date: " << transactions[i].date << endl;
            cout << "Description: " << transactions[i].description << endl;
            cout << "Category: " << transactions[i].category << endl;
            cout << "Amount: " << transactions[i].amount << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Transaction not found." << endl;
}
 //Display Transaction
void displayTransactions() {
    if (numTransactions == 0) {
        cout << "No Transactions found" << endl;
        return;
    }
    cout << "List of Transactions:" << endl;
    for (int i = 0; i < numTransactions; ++i) {
        cout << "Date: " << transactions[i].date << endl;
        cout << "Description: " << transactions[i].description << endl;
        cout << "Amount: " << transactions[i].amount << endl;
        cout << "Category: " << transactions[i].category << endl;
    }
}
 //Save Transaction
void saveTransactions() {
    ofstream file("Transactions.txt");
    if (file.is_open()) {
        for (int i = 0; i < numTransactions; ++i) {
            file << "Name: " << transactions[i].name << endl;
            file << "Date: " << transactions[i].date << endl;
            file << "Description: " << transactions[i].description << endl;
            file << "Amount: " << transactions[i].amount  << endl;
            file << "Category: " << transactions[i].category << endl;
        }
        file.close();
        cout << "Transactions saved to file." << endl;
    } else {
        cout << "Unable to open Transactions file." << endl;
    }
}
 //Update Transaction
void updateTransaction(const string& name) {
    bool recordFound = false;
    for (int i = 0; i < numTransactions; ++i) {
        if (transactions[i].name == name) {
            cout << "Enter new data: " << endl;
            cout << "Name: ";
            cin >> transactions[i].name;
            cout << "Date: ";
            cin >> transactions[i].date;
            cout << "Description: ";
            cin.ignore();
            getline(cin, transactions[i].description);
            cout << "Category: ";
            getline(cin, transactions[i].category);
            do {
                cout << "Enter amount (0-10000): ";
                cin >> transactions[i].amount;
                if (!validateAmount(transactions[i].amount)) {
                    cout << "Invalid input! Amount must be between 0 and 10000." << endl;
                }
            } while (!validateAmount(transactions[i].amount));

            cout << "Transaction updated successfully!" << endl;
            recordFound = true;
            break;
        }
    }
    if (!recordFound) {
        cout << "Record not found." << endl;
    }
}
 //Delete Transaction
void deleteTransaction(const string& name) {
    bool found = false;
    for (int i = 0; i < numTransactions; ++i) {
        if (transactions[i].name == name) {
            found = true;

            for (int j = i; j < numTransactions - 1; ++j) {
                transactions[j] = transactions[j + 1];
            }

            numTransactions--;
            cout << "Transaction deleted successfully" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Transaction not found" << endl;
    }
}
 //Load Transaction
void loadTransactions() {
    ifstream file("Transactions.txt");
    if (file.is_open()) {
        while (numTransactions < MAX_TRANSACTIONS &&
               file >> transactions[numTransactions].name >> 
               transactions[numTransactions].date >>
               transactions[numTransactions].description>>
               transactions[numTransactions].category >> 
               transactions[numTransactions].amount)
        {
            numTransactions++;
        }
        file.close();
        cout << "Transactions loaded from file." << endl;
    } else {
        cout << "No Transactions found." << endl;
    }
}

int main() {
    loadTransactions();

    char choice;
    string name;
    do {
        cout << "\nChoose an option:" << endl;
        cout << "1. Add Transaction" << endl;
        cout << "2. Find Transaction by name" << endl;
        cout << "3. Display all Transactions" << endl;
        cout << "4. Save Transactions to file" << endl;
        cout << "5. Update Transaction" << endl;
        cout << "6. Delete Transaction by name" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            addTransaction();
            break;
        case '2':
            cout << "Enter name to find Transaction: ";
            cin >> name;
            findTransaction(name);
            break;
        case '3':
            displayTransactions();
            break;
        case '4':
            saveTransactions();
            break;
        case '5':
            cout << "Enter name to update Transaction: ";
            cin >> name;
            updateTransaction(name);
            break;
        case '6':
            cout << "Enter name to delete Transaction: ";
            cin >> name;
            deleteTransaction(name);
            break;
        case '7':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '7');
    return 0;
}

