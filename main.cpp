#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

// ANSI color codes for better console output
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";

// Structure to store information about an expense
struct Expense {
    string description;
    double amount;
    bool isTaxDeductible;
};

// Function prototypes
void createAccount(unordered_map<string, string>& accounts);
bool login(const unordered_map<string, string>& accounts);
int getChoice(int accountcheck);
void addExpense(vector<Expense>& expenses);
double calculateDeductibleExpenses(const vector<Expense>& expenses);
double calculateTax(double income, double deductibleExpenses, double taxRate);
void displayExpenses(const vector<Expense>& expenses);
void financialQuiz();
void dataAnalysis();

int main() {
    unordered_map<string, string> accounts;
    bool loggedIn = false;
    int accountcheck = 0;
    vector<Expense> expenses;

    while (true) {
        int choice = getChoice(accountcheck);

        if (choice == 1) {
            createAccount(accounts);
        }
        else if (choice == 2) {
            loggedIn = login(accounts);
            if (loggedIn) {
                cout << GREEN << "Welcome to the system!\n" << RESET;
                accountcheck = 1;
            }
        }
        else if (choice == 3) {
            cout << GREEN << "Exiting the program.\n" << RESET;
            break;
        }
        else if (choice == 4 && loggedIn) {
            double budget, expectation;
            cout << YELLOW << "What is your monthly budget?\n" << RESET;
            cin >> budget;
            cout << YELLOW << "What amount would you like to set aside as savings for the future?\n" << RESET;
            cin >> expectation;

            if (expectation * 5 >= budget) {
                cout << GREEN << "It is evident that you are making thoughtful decisions regarding your future.\n" << RESET;
            }

            // Perform financial data analysis
            dataAnalysis();
        }

        if (loggedIn) {
            // Sub-menu for additional features
            int subChoice;
            do {
                cout << CYAN << "\n--- Financial Tools Menu ---\n" << RESET;
                cout << "1. Add an Expense\n";
                cout << "2. View Expenses\n";
                cout << "3. Calculate Tax Estimate\n";
                cout << "4. Take Financial Quiz\n";
                cout << "5. Exit to Main Menu\n";
                cout << YELLOW << "Enter your choice: " << RESET;
                cin >> subChoice;

                if (subChoice == 1) {
                    addExpense(expenses);
                }
                else if (subChoice == 2) {
                    displayExpenses(expenses);
                }
                else if (subChoice == 3) {
                    double income, taxRate;
                    cout << "Enter your annual income: ";
                    cin >> income;
                    cout << "Enter your tax rate (as a decimal, e.g., 0.25 for 25%): ";
                    cin >> taxRate;
                    double deductibleExpenses = calculateDeductibleExpenses(expenses);
                    double estimatedTax = calculateTax(income, deductibleExpenses, taxRate);

                    cout << "\nTotal Tax-Deductible Expenses: $" << deductibleExpenses << "\n";
                    cout << "Estimated Tax: $" << estimatedTax << "\n";
                }
                else if (subChoice == 4) {
                    financialQuiz();
                }
                else if (subChoice == 5) {
                    cout << "Returning to the main menu...\n";
                }
                else {
                    cout << RED << "Invalid choice. Please try again.\n" << RESET;
                }
            } while (subChoice != 5);
        }
    }

    return 0;
}

// Function to create an account
void createAccount(unordered_map<string, string>& accounts) {
    string username, password;
    cout << BLUE << "Enter a new username: " << RESET;
    cin >> username;

    if (accounts.find(username) != accounts.end()) {
        cout << RED << "Username already exists. Try a different one.\n" << RESET;
        return;
    }

    cout << BLUE << "Enter a new password: " << RESET;
    cin >> password;
    accounts[username] = password;
    cout << GREEN << "Account created successfully!\n" << RESET;
}

// Function to login
bool login(const unordered_map<string, string>& accounts) {
    string username, password;
    cout << BLUE << "Enter username: " << RESET;
    cin >> username;
    cout << BLUE << "Enter password: " << RESET;
    cin >> password;

    if (accounts.find(username) != accounts.end() && accounts.at(username) == password) {
        cout << GREEN << "Login successful! Welcome, " << username << "!\n" << RESET;
        return true;
    }
    else {
        cout << RED << "Invalid username or password.\n" << RESET;
        return false;
    }
}

// Function to get a valid choice from the user
int getChoice(int accountcheck) {
    int choice;
    if (accountcheck == 1) {
        while (true) {
            cout << "\n--- Menu ---\n";
            cout << "1. Create another Account\n";
            cout << "2. You are logged in. Press 2 to switch accounts.\n";
            cout << "3. Start\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;
            if (choice == 4) choice = 3;
            else if (choice == 3) choice = 4;

            if (cin.fail() || choice < 1 || choice > 3) {
                cout << RED << "Invalid choice. Please enter 1, 2, or 3.\n" << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                return choice;
            }
        }
    }
    else {
        while (true) {
            cout << "\n--- Menu ---\n";
            cout << "1. Create Account\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                cout << RED << "Invalid choice. Please enter 1, 2, or 3.\n" << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                return choice;
            }
        }
    }
}


void addExpense(vector<Expense>& expenses) {
    string description;
    double amount;
    char deductible;

    cout << "Enter expense description: ";
    cin.ignore();
    getline(cin, description);

    cout << "Enter expense amount: ";
    cin >> amount;

    cout << "Is this expense tax-deductible? (y/n): ";
    cin >> deductible;

    expenses.push_back({ description, amount, deductible == 'y' || deductible == 'Y' });
}

// Function to calculate total deductible expenses
double calculateDeductibleExpenses(const vector<Expense>& expenses) {
    double total = 0.0;
    for (const auto& expense : expenses) {
        if (expense.isTaxDeductible) total += expense.amount;
    }
    return total;
}

// Function to calculate the estimated tax
double calculateTax(double income, double deductibleExpenses, double taxRate) {
    double taxableIncome = income - deductibleExpenses;
    if (taxableIncome < 0) taxableIncome = 0;
    return taxableIncome * taxRate;
}

// Function to display all expenses
void displayExpenses(const vector<Expense>& expenses) {
    cout << "\nList of Expenses:\n";
    cout << setw(30) << left << "Description" << setw(10) << "Amount" << setw(15) << "Tax Deductible" << "\n";
    cout << "-------------------------------------------------------\n";
    for (const auto& expense : expenses) {
        cout << setw(30) << expense.description << setw(10) << expense.amount << setw(15) << (expense.isTaxDeductible ? "Yes" : "No") << "\n";
    }
}


void financialQuiz() {
    int score = 0;
    string answer;
    cout << CYAN << "\n--- Financial Quiz ---\n" << RESET;

    string questions[] = {
        "1. How often do you spend money on things you don’t use later?",
        "2. How often do you fail to follow your budget?",
        "3. How often do you save less than 20% of your income?",
        "4. How often do you buy things impulsively?",
        "5. How often do you skip comparing prices for big purchases?",
        "6. How often do you fail to track your monthly expenses?",
        "7. How often do you avoid investing any savings",
        "8. How often do you use credit cards for non-essential items?",
        "9. How often do you lack an emergency fund of 3-6 months' expenses?",
        "10. How often do you neglect learning about personal finance?"
    };

    for (int i = 0; i < 10; ++i) {
        cout << questions[i] << " (often/rarely): " << BLUE;
        cin >> answer;
        cout << RESET;

        if (answer == "often" || answer == "Often") {
            score++;
        }
        else if (answer != "rarely" && answer != "Rarely") {
            cout << RED << "Invalid answer. Please enter 'often' or 'rarely'.\n" << RESET;
            i--;
        }
    }

    cout << CYAN << "\n--- Quiz Feedback ---\n" << RESET;
    if (score >= 8) {
        cout << RED << "You have many habits that could harm your financial stability. "
            << "Consider making changes to improve your financial habits.\n" << RESET;
    }
    else if (score >= 5) {
        cout << YELLOW << "You have some good financial habits, but there’s room for improvement. "
            << "Try to minimize impulsive spending and increase savings.\n" << RESET;
    }
    else {
        cout << GREEN << "Great job! You have strong financial habits. Keep it up!\n" << RESET;
    }

    cout << CYAN << "Quiz completed. Press Enter to return to the main menu.\n" << RESET;
    cin.ignore(); // Clear the newline character from the input buffer
    cin.get(); // Wait for the user to press Enter
}

// Function to perform basic data analysis
void dataAnalysis() {
    double calendar[12][31] = { 0 };
    calendar[11][27] = 5;
    calendar[11][28] = 6;
    calendar[11][29] = 7;
    calendar[11][30] = 9;

    cout << CYAN << "\n--- Data Analysis ---\n" << RESET;
    cout << "Sample data for December:\n";

    for (int i = 27; i <= 30; i++) {
        cout << "December " << i + 1 << ": " << calendar[11][i] << " units\n";
    }

    cout << CYAN << "Data analysis completed. Press Enter to return to the main menu.\n" << RESET;
    cin.ignore();
    cin.get();
}