#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

void createAccount(unordered_map<string, string>& accounts) {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    if (accounts.find(username) != accounts.end()) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "Enter a new password: ";
    cin >> password;
    accounts[username] = password;
    cout << "Account created successfully!\n";
}

bool login(const unordered_map<string, string>& accounts) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (accounts.find(username) != accounts.end() && accounts.at(username) == password) {
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

int getChoice(int accountcheck) {
    int choice;
    if (accountcheck == 1) {
        while (true) {
            cout << "\n--- Menu ---\n";
            cout << "1. Create another Account\n";
            cout << "2. You are logged in. If you have another account, press 2 to switch accounts.\n";
            cout << "3. Start\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;
            //Substitution of values
            if (choice == 4) {
                choice = 3;
            }
            else if(choice == 3){
                choice = 4;
            }

            if (cin.fail() || choice < 1 || choice > 3) {
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
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
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                return choice;
            }
        }
    }
}

int main() {
    unordered_map<string, string> accounts;
    int accountcheck;
    accountcheck = 0;
    while (true) {
        int choice = getChoice(accountcheck);

        if (choice == 1) {
            createAccount(accounts);
        }
        else if (choice == 2) {
            if (login(accounts)) {
                cout << "Welcome to the system!\n";
                accountcheck = 1;
            }
        }
        else if (choice == 3) {
            cout << "Exiting the program.\n";
            break;
        }
        else if (choice == 4) {
            cout << "I'm here to ask you a couple of questions and then show you some statistics.\n";
            break;
        }
        if (choice == 4) {
            double budget, expectation;
            cout << "What is your monthly budget?\n";
            cin >> budget;
            cout << "What amount would you like to set aside as savings for the future?\n";
            cin >> expectation;
            if (expectation * 5 >= budget) {
                cout << "It is evident that you are making thoughtful decisions regarding your future.\n";
            }
            cout << "Would you like to enter your information?\n";
        }
    }
    // base for data analys part
        /*double calendar[12][31];
        calendar[11][27] = 5;
        calendar[11][28] = 6;
        calendar[11][29] = 7;
        calendar[11][31] = 9;
        cout << "Hello World!";
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 31; j++) {
                cout << calendar[i][j] << endl;
            }
        }

    }
    */
    return 0;
}