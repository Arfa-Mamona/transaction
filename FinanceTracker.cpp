#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <algorithm> 
#include <limits>
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
    return (amount >= 0 && amount <= 100000);
}

// Terminating program

void terminate (int exitcode = 0) {
	exit (exitcode);
}

// Add Transaction
void addTransaction() {
    if (numTransactions < MAX_TRANSACTIONS) {
        Transaction newTransaction;

		cout << "Enter Your Transaction Name: ";
    	getline(cin, newTransaction.name); 
    	newTransaction.name;
        
        cout << "Enter Date (DD/MM/YYYY): ";
        getline(cin, newTransaction.date);

        cout << "Enter description (purpose): "; 
        getline(cin, newTransaction.description);
		
        cout << "Enter category (Tax, Savings, personal spending): ";
        getline(cin, newTransaction.category);

        string amountStr;
        do {
            cout << "Enter amount (0-100000): ";
            getline(cin, amountStr);
            stringstream(amountStr) >> newTransaction.amount;
            if (!validateAmount(newTransaction.amount)) {
                cout << "Invalid input! Amount must be between 0 and 100000." << endl;
            }
        } while (!validateAmount(newTransaction.amount));

        transactions[numTransactions++] = newTransaction;
        cout << "Transaction added successfully!" << endl;
    } else {
        cout << "Transaction limit reached." << endl;
    }
}

// Find transaction
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

// Display Transaction
void displayTransaction() {
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

// Calculate Balance
double calculateBalance() {
    double balance = 0.0;
    for (int i = 0; i < numTransactions; ++i) {
        balance += transactions[i].amount;
    }
    return balance;
}
// Display Balance
void displayBalance() {
    cout << "Current Balance: " << calculateBalance() << endl;
}

// Display Category Spendings
void categorySpendings() {
    map<string, double> categorySpendings;

	// Calculate category-wise spending
    for (int i = 0; i < numTransactions; ++i) {
        const Transaction& transaction = transactions[i];
        categorySpendings[transaction.category] += transaction.amount;
    }

    // Display category-wise spending using iterators
    cout << "Category wise spending summary:" << endl;
    for (map<string, double>::const_iterator it = categorySpendings.begin(); it != categorySpendings.end(); ++it) {
    cout << it->first << ": " << fixed << setprecision(2) << it->second << endl;
}
    }

 //Budget Planning
void budgetPlanning() {
    map<string, double> categoryBudgets;

    cout << "Enter budget for each category:" << endl;
    cout << "Food: ";
    cin >> categoryBudgets["Food"];
    cout << "Health: ";
    cin >> categoryBudgets["Health"];
    cout << "Utilities: ";
    cin >> categoryBudgets["Utilities"];
    cout <<"----------------------" << endl;

 // Display budgets
    cout << "Category wise Budgets:" << endl;
    cout << "Food: " << categoryBudgets["Food"] << endl;
    cout << "Health: " << categoryBudgets["Health"] << endl;
    cout << "Utilities: " << categoryBudgets["Utilities"] << endl;
}

// Save Budgets to File
void saveBudgets(const map<string, double>& categoryBudgets) {
    ofstream file("Budgets.txt", ios::app);
    if (file.is_open()) {
        for (map<string, double>::const_iterator it = categoryBudgets.begin(); it != categoryBudgets.end(); ++it) {
            file << it->first << ": " << it->second << endl;
        }
        file.close();
        cout << "Budgets saved to file." << endl;
    } else {
        cout << "Unable to open Budgets file." << endl;
    }
}

// Load Budgets from File
void loadBudgets(map<string, double>& categoryBudgets) {
    ifstream file("Budgets.txt");
    if (file.is_open()) {
        string category;
        double budget;
        while (file >> category >> budget) {
            categoryBudgets[category] = budget;
        }
        file.close();
        cout << "Budgets loaded from file." << endl;
    } else {
        cout << "No Budgets found." << endl;
    }
}

// Save Transaction
void saveTransaction() {
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

// Update Transaction
void updateTransaction(const string& name) {
    bool recordFound = false;
    for (int i = 0; i < numTransactions; ++i) {
        if (transactions[i].name == name) {
            cout << "Enter new data: " << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, transactions[i].name);
            cout << "Date: ";
            getline(cin, transactions[i].date);
            cout << "Description: ";
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

// Delete Transaction
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

// Load Transaction
void loadTransaction() {
    ifstream file("Transactions.txt");
    if (file.is_open()) {
    		while (file >> transactions[numTransactions].name >> 
              transactions[numTransactions].date >>
              transactions[numTransactions].description>>
              transactions[numTransactions].category >> 
              transactions[numTransactions].amount && numTransactions < MAX_TRANSACTIONS)

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
    loadTransaction();

	char choice;
    string name;
    map<string, double> categoryBudgets;
    loadBudgets(categoryBudgets);  
    
    cout << "\nChoose an option:" << endl;
    cout << "--------------------" << endl;
    cout << "1. Add Transaction" << endl;
    cout << "2. Find Transaction by name" << endl;
    cout << "3. Display all Transaction" << endl;
    cout << "4. Save Transaction to file" << endl;
    cout << "5. Update Transaction" << endl;
    cout << "6. Delete Transaction by name" << endl;
    cout << "7. Budget Planning" << endl;
    cout << "8. Display Category-wise Spending" << endl;
    cout << "9. Calculate Balance and Display Balance" << endl;
    cout << "10. Exit" << endl;
    cout << "--------------------" << endl;

    do {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch(choice) {
            case '1':
                addTransaction();
                break;
            case '2':
                cout << "Enter name to find Transaction: ";
                getline(cin, name);
                findTransaction(name);
                break;
            case '3':
                displayTransaction();
                break;
            case '4':
                saveTransaction();
                break;
            case '5':
                cout << "Enter name to update Transaction: ";
                getline(cin, name);
                updateTransaction(name);
                break;
            case '6':
                cout << "Enter name to delete Transaction: ";
                getline(cin, name);
                deleteTransaction(name);
                break;
            case '7':
                budgetPlanning();
                break;
            case '8':
                categorySpendings();
                break;
            case '9':
                displayBalance();
                break;
            case '10':
            	terminate(1);
            	break;
        		default:
            cout << "Invalid choice. Please try again." << endl;
    }
} while (true);

    return 0;
}
