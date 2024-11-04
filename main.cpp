#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <limits>
#include <cstdlib>
#include <random>
#include "Color.h"
#include "Expense.h"
using namespace std;

void createAccount(unordered_map<string, string>& accounts) {
    string username, password;
    setColor(YELLOW);
    cout << "Enter a new username: ";
    setColor(RESET);
    cin >> username;

    if (accounts.find(username) != accounts.end()) {
        setColor(RED);
        cout << "Username already exists. Try a different one.\n";
        setColor(RESET);
        return;
    }

    setColor(YELLOW);
    cout << "Enter a new password: ";
    setColor(RESET);
    cin >> password;
    accounts[username] = password;

    setColor(GREEN);
    cout << "Account created successfully!\n";
    setColor(RESET);
}

bool login(const unordered_map<string, string>& accounts) {
    string username, password;
    setColor(YELLOW);
    cout << "Enter username: ";
    setColor(RESET);
    cin >> username;
    setColor(YELLOW);
    cout << "Enter password: ";
    setColor(RESET);
    cin >> password;

    if (accounts.find(username) != accounts.end() && accounts.at(username) == password) {
        setColor(GREEN);
        cout << "Login successful! Welcome, " << username << "!\n";
        setColor(RESET);
        return true;
    }
    else {
        setColor(RED);
        cout << "Invalid username or password.\n";
        setColor(RESET);
        return false;
    }
}

void fillYear(vector<vector<double>>& year) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(-500.0, 500.0);
    for (int month = 0; month < year.size(); ++month) {
        for (int day = 0; day < year[month].size(); ++day) {
            year[month][day] = dis(gen);
        }
    }
}

void fillMonth(vector<double>& month) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(-500.0, 500.0);

    for (int day = 0; day < month.size(); ++day) {
        month[day] = dis(gen);
    }
}

// Function for saving data to a file
void saveToFile(const vector<vector<double>>& year, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        vector<string> monthNames = { "January", "February", "March", "April", "May", "June",
                                     "July", "August", "September", "October", "November", "December" };

        for (int month = 0; month < year.size(); ++month) {
            file << monthNames[month] << ": ";
            for (int day = 0; day < year[month].size(); ++day) {
                file << year[month][day];
                if (day < year[month].size() - 1) {
                    file << ", ";
                }
            }
            file << endl;
        }
        file.close();
        cout << "Data saved to file: " << filename << endl;
    }
    else {
        cout << "Failed to open file for writing." << endl;
    }
}

// Function for loading data from a file
bool loadFromFile(vector<vector<double>>& year, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        for (int month = 0; month < year.size() && getline(file, line); ++month) {
            size_t pos = line.find(": ");
            if (pos == string::npos) continue;

            line = line.substr(pos + 2);
            istringstream ss(line);
            string value;
            int day = 0;

            while (getline(ss, value, ',') && day < year[month].size()) {
                try {
                    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
                    year[month][day++] = stod(value);
                }
                catch (const invalid_argument& e) {
                    cout << "Error converting string to double at month " << month + 1
                        << ", day " << day << ": " << e.what() << endl;
                    year[month][day - 1] = 0.0; // Set the default value
                }
            }
        }
        file.close();
        cout << "Data loaded from file successfully." << endl;
        return true;
    }
    return false;
}

// Function for entering expenses with a specific date
void inputExpensesByDate(vector<vector<double>>& year) {
    int month, day;
    string option;

    cout << "Enter your expenses by specifying the date (month and day).\n";
    while (true) {
        cout << "Enter month (1-12): ";
        cin >> month;
        if (month < 1 || month > 12) {
            cout << "Invalid month. Please try again.\n";
            continue;
        }

        cout << "Enter day: ";
        cin >> day;
        if (day < 1 || day > year[month - 1].size()) {
            cout << "Invalid day for this month. Please try again.\n";
            continue;
        }

        double dailyTotal = 0.0;
        string input;
        if (day > 9)
            cout << "Enter expenses for " << day << '.' << month << " (or type 'ND' to finish):\n";
        else
            cout << "Enter expenses for 0" << day << '.' << month << " (or type 'ND' to finish):\n";
        while (true) {
            cout << "Expense: ";
            cin >> input;

            if (input == "ND" || input == "nd") {
                break;
            }

            try {
                dailyTotal += stod(input);
            }
            catch (const invalid_argument&) {
                cout << "Invalid input. Please enter a valid number or 'ND'." << endl;
            }
        }

        year[month - 1][day - 1] = dailyTotal;

        cout << "Choose an option:\n1 - Enter another date\n2 - Stop\n";
        cin >> option;

        if (option == "1") {
            continue;
        }
        else if (option == "2") {
            break;
        }
        else {
            cout << "Invalid option. Stopping input.\n";
            break;
        }
    }
}

// Function for plotting a graph for a month or a year
void plotGraph(const vector<vector<double>>& year) {
    int choice;
    cout << "Enter 1 to plot a graph for a specific month or 2 for the entire year: ";
    cin >> choice;

    FILE* gnuplotPipe = _popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        if (choice == 1) {
            int month;
            cout << "Enter the month number (1-12): ";
            cin >> month;
            if (month < 1 || month > 12) {
                cerr << "Invalid month number." << endl;
                return;
            }

            fprintf(gnuplotPipe, "set title 'Daily Spending for Month %d'\n", month);
            fprintf(gnuplotPipe, "set xlabel 'Day'\n");
            fprintf(gnuplotPipe, "set ylabel 'Amount Spent (Lv)'\n");
            fprintf(gnuplotPipe, "set xrange [0:%zu]\n", year[month - 1].size());
            fprintf(gnuplotPipe, "plot '-' with linespoints title 'Spending'\n");
            for (size_t day = 0; day < year[month - 1].size(); ++day) {
                fprintf(gnuplotPipe, "%zu %f\n", day + 1, year[month - 1][day]);
            }
            fprintf(gnuplotPipe, "e\n");

        }
        else if (choice == 2) {
            vector<double> monthlyTotals(12, 0.0);
            for (int month = 0; month < 12; ++month) {
                for (double dailySpending : year[month]) {
                    monthlyTotals[month] += dailySpending;
                }
            }

            fprintf(gnuplotPipe, "set title 'Monthly Spending for the Year'\n");
            fprintf(gnuplotPipe, "set xlabel 'Month'\n");
            fprintf(gnuplotPipe, "set ylabel 'Amount Spent ($)'\n");
            fprintf(gnuplotPipe, "set xtics ('Jan' 1, 'Feb' 2, 'Mar' 3, 'Apr' 4, 'May' 5, 'Jun' 6, 'Jul' 7, 'Aug' 8, 'Sep' 9, 'Oct' 10, 'Nov' 11, 'Dec' 12)\n");
            fprintf(gnuplotPipe, "set xrange [0.5:12.5]\n");
            fprintf(gnuplotPipe, "plot '-' with linespoints title 'Spending'\n");
            for (size_t i = 0; i < monthlyTotals.size(); ++i) {
                fprintf(gnuplotPipe, "%zu %f\n", i + 1, monthlyTotals[i]);
            }
            fprintf(gnuplotPipe, "e\n");

        }
        else {
            cerr << "Invalid choice." << endl;
        }
        _pclose(gnuplotPipe);
    }
    else {
        cerr << "Error: Could not open GNUplot pipe." << endl;
    }
}

// New function to analyze data
void dataAnalysis() {
    vector<vector<double>> year = {
        vector<double>(31, 0.0), // January
        vector<double>(29, 0.0), // February (leap year)
        vector<double>(31, 0.0), // March
        vector<double>(30, 0.0), // April
        vector<double>(31, 0.0), // May
        vector<double>(30, 0.0), // June
        vector<double>(31, 0.0), // July
        vector<double>(31, 0.0), // August
        vector<double>(30, 0.0), // September
        vector<double>(31, 0.0), // October
        vector<double>(30, 0.0), // November
        vector<double>(31, 0.0)  // December
    };

    string filename = "usersdata.txt";
    char displayData;
    // Load data from file if it exists; otherwise, prompt for input from the keyboard
    if (filesystem::exists(filename)) {
        if (!loadFromFile(year, filename)) {
            cout << "Error loading data from file. Starting with empty data." << endl;
        }
        cout << "Do you want to enter additional data? (Y/N): ";
        cin >> displayData;
        if (toupper(displayData) == 'Y') {
            inputExpensesByDate(year);
        }
    }
    else {
        inputExpensesByDate(year); // Manually enter data if the file is not available
    }

    // Request to display data
    cout << "Would you like to display the data? (Y/N): ";
    cin >> displayData;
    if (toupper(displayData) == 'Y') {
        for (int month = 0; month < year.size(); ++month) {
            cout << "Month " << (month + 1) << ": ";
            for (int day = 0; day < year[month].size(); ++day) {
                cout << year[month][day] << ' ';
            }
            cout << endl;
        }
    }

    // Plotting the graph
    char plotData;
    cout << "Would you like to plot a graph?  (Y/N): ";
    cin >> plotData;
    if (toupper(plotData) == 'Y') {
        plotGraph(year);
    }

    // Saving data to a file
    saveToFile(year, filename);
}
void financialQuiz() {
    int score = 0;
    string answer;
    cout << endl;
    setColor(CYAN);
    cout << setw(35) << "" << "    Financial Quiz    \n" << RESET;
    cout << "___________________________________________________________________________________________" << endl << endl;

    string questions[] = {
        "1. How often do you spend money on things you don’t use later?",
        "2. How often do you fail to follow your budget?",
        "3. How often do you save less than 20% of your income?",
        "4. How often do you buy things impulsively?",
        "5. How often do you skip comparing prices for big purchases?",
        "6. How often do you fail to track your monthly expenses?",
        "7. How often do you avoid investing any savings?",
        "8. How often do you use credit cards for non-essential items?",
        "9. How often do you lack an emergency fund of 3-6 months' expenses?",
        "10. How often do you neglect learning about personal finance?"
    };

    for (int i = 0; i < 10; ++i) {
        setColor(YELLOW);
        cout << questions[i] << " (often/rarely): ";
        setColor(RESET);

        cin >> answer;

        if (answer == "often" || answer == "Often") {
            score++;
        }
        else if (answer != "rarely" && answer != "Rarely") {
            setColor(RED);
            cout << "Invalid answer. Please enter  " << '"' << "often" << '"' << " or " << '"' << "rarely" << '"' << " .\n";
            setColor(RESET);
            i--;
        }
    }
    cout << "___________________________________________________________________________________________" << endl << endl;

    setColor(CYAN);

    string line = "----------------------------------------";
    cout << "\n" << "" << line << "\n";  // Top border
    cout << "" << "|             Quiz Feedback            |\n";
    cout << "" << line << "\n";  // Bottom border
    setColor(RESET);

    if (score >= 8) {
        setColor(RED);
        cout << "" << "| You have many habits that could harm |\n";
        cout << "" << "| your financial stability. Consider   |\n";
        cout << "" << "| making changes to improve your       |\n";
        cout << "" << "| financial habits.                    |\n";
    }
    else if (score >= 5) {
        setColor(YELLOW);
        cout << "" << "| You have some good financial habits, |\n";
        cout << "" << "| but there’s room for improvement. Try|\n";
        cout << "" << "| to minimize impulsive spending and   |\n";
        cout << "" << "| increase savings.                    |\n";
    }
    else {
        setColor(GREEN);
        cout << "" << "| Great job! You have strong financial |\n";
        cout << "" << "| habits. Keep it up!                  |\n";
    }

    setColor(CYAN);
    cout << "" << line << "\n";
    cout << endl;
    cout << "Quiz completed. Press Enter to return to the main menu.\n" << RESET;
    cin.ignore();
    cin.get();
}
void printMainMenuHeader() {
    setColor(CYAN);
    cout << " -------------------------------------------------------" << endl;
    cout << " |                     Financial App                   |" << endl;
    cout << " -------------------------------------------------------" << endl;
    setColor(RESET);
}

void printFinancialToolsMenuHeader() {
    setColor(CYAN);
    cout << " -------------------------------------------------------" << endl;
    cout << " |                 Financial Tools Menu                |" << endl;
    cout << " -------------------------------------------------------" << endl;
    setColor(RESET);
}

void printLine() {
    cout << " -------------------------------------------------------" << endl;
}

void printOption(const string& text) {
    cout << " | " << text;
    for (size_t i = text.length(); i < 52; i++) {
        cout << " ";  // Padding for uniformity
    }
    cout << "|" << endl;
}

void addExpense(vector<Expense>& expenses) {
    string description;
    double amount;
    char deductible;

    cout << CYAN << "|---------------------------------------------|\n" << RESET;
    cout << CYAN << "| Enter expense description: " << RESET;
    cin.ignore();  // Clear the newline left in the input buffer
    getline(cin, description);

    cout << CYAN << "| Enter expense amount: " << RESET;
    cin >> amount;

    cout << CYAN << "| Is this expense tax-deductible? (y/n): " << RESET;
    cin >> deductible;

    expenses.push_back({ description, amount, deductible == 'y' || deductible == 'Y' });
    cout << CYAN << "|---------------------------------------------|\n" << RESET;
}

double calculateDeductibleExpenses(const vector<Expense>& expenses) {
    double total = 0.0;
    for (const auto& expense : expenses) {
        if (expense.isTaxDeductible) total += expense.amount;
    }
    return total;
}

double calculateTax(double income, double deductibleExpenses, double taxRate) {
    double taxableIncome = income - deductibleExpenses;
    if (taxableIncome < 0) taxableIncome = 0;
    return taxableIncome * taxRate;
}

void displayExpenses(const vector<Expense>& expenses) {
    cout << GREEN << "\n|---------------- List of Expenses ----------------|\n" << RESET;
    cout << GREEN << "|" << setw(30) << left << "Description"
        << "|" << setw(10) << "Amount(lv)"
        << "|" << setw(15) << "Tax Deductible" << "|\n" << RESET;
    cout << "|--------------------------------------------------|\n";

    for (const auto& expense : expenses) {
        cout << "|" << setw(30) << expense.description
            << "|" << setw(10) << fixed << setprecision(2) << expense.amount
            << "|" << setw(8) << (expense.isTaxDeductible ? "Yes" : "No") << "|\n";
    }
    cout << "|--------------------------------------------------|\n";

    cout << endl << endl;
}

int main() {
    unordered_map<string, string> accounts;
    vector<Expense> expenses;
    bool loggedIn = false;

    while (true) {
        printMainMenuHeader();
        printLine();
        printOption("1. Create Account");
        printOption("2. Login");
        printOption("3. Exit");
        printLine();
        setColor(YELLOW);
        cout << " | Enter your choice: ";
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
                cout << " | Welcome to the system!" << endl;
                setColor(RESET);

                // Sub-menu
                int subChoice;
                do {
                    printFinancialToolsMenuHeader();
                    printLine();
                    printOption("1. Add an Expense");
                    printOption("2. View Expenses");
                    printOption("3. Calculate Tax Estimate");
                    printOption("4. Take Financial Quiz");
                    printOption("5. Data Analysis");
                    printOption("6. Exit and Logg out");
                    printLine();
                    setColor(YELLOW);
                    cout << " | Enter your choice: ";
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
                        cout << " | Enter your income: ";
                        setColor(RESET);
                        cin >> income;
                        setColor(YELLOW);
                        cout << " | Enter tax rate (as a decimal): ";
                        setColor(RESET);
                        cin >> taxRate;
                        double deductibleExpenses = calculateDeductibleExpenses(expenses);
                        double tax = calculateTax(income, deductibleExpenses, taxRate);
                        setColor(GREEN);
                        cout << " | Estimated tax: $" << tax << endl;
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
            cout << " | Exiting program. Goodbye!" << endl;
            setColor(RESET);
            break;
        }
        else {
            setColor(RED);
            cout << " | Invalid choice. Please try again." << endl;
            setColor(RESET);
        }
    }

    return 0;
}
