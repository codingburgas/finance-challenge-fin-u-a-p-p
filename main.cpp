#include <iostream>
#include <unordered_map>
#include <vector>
#include "Account.h"
#include "Expense.h"
#include "FinancialQuiz.h"
#include "DataAnalysis.h"
#include "Color.h"

using namespace std;

int main() {
    unordered_map<string, string> accounts;
    vector<Expense> expenses;
    bool loggedIn = false;

    while (true) {
        setColor(CYAN);
        cout << "\n--- Main Menu ---\n";
        setColor(RESET);
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        setColor(YELLOW);
        cout << "Enter your choice: ";
        setColor(RESET);
        int choice;
        cin >> choice;

        if (choice == 1) {
            createAccount(accounts);
        }
        else if (choice == 2) {
            loggedIn = login(accounts);
            if (loggedIn) {
                setColor(GREEN);
                cout << "Welcome to the system!\n";
                setColor(RESET);

                // Sub-menu
                int subChoice;
                do {
                    setColor(CYAN);
                    cout << "\n--- Financial Tools Menu ---\n";
                    setColor(RESET);
                    cout << "1. Add an Expense\n";
                    cout << "2. View Expenses\n";
                    cout << "3. Calculate Tax Estimate\n";
                    cout << "4. Take Financial Quiz\n";
                    cout << "5. Data Analysis\n";
                    cout << "6. Exit to Main Menu\n";
                    setColor(YELLOW);
                    cout << "Enter your choice: ";
                    setColor(RESET);
                    cin >> subChoice;

                    if (subChoice == 1) {
                        addExpense(expenses);
                    }
                    else if (subChoice == 2) {
                        displayExpenses(expenses);
                    }
                    else if (subChoice == 3) {
                        double income, taxRate;
                        setColor(YELLOW);
                        cout << "Enter your income: ";
                        setColor(RESET);
                        cin >> income;
                        setColor(YELLOW);
                        cout << "Enter tax rate (as a decimal(%)): ";
                        setColor(RESET);
                        cin >> taxRate;
                        double deductibleExpenses = calculateDeductibleExpenses(expenses);
                        double tax = calculateTax(income, deductibleExpenses, taxRate);
                        setColor(GREEN);
                        cout << "Estimated tax: $" << tax << "\n";
                        setColor(RESET);
                    }
                    else if (subChoice == 4) {
                        financialQuiz();
                    }
                    else if (subChoice == 5) {
                        dataAnalysis();
                    }
                } while (subChoice != 6);
            }
        }
        else if (choice == 3) {
            setColor(MAGENTA);
            cout << "Exiting program. Goodbye!\n";
            setColor(RESET);
            break;
        }
        else {
            setColor(RED);
            cout << "Invalid choice. Please try again.\n";
            setColor(RESET);
        }
    }

    return 0;
}
