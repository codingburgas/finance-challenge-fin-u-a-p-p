#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;
int main()
{
    double calendar[12][31];
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

int getChoice() {
    int choice;
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

int main() {
    unordered_map<string, string> accounts;

    while (true) {
        int choice = getChoice();

        if (choice == 1) {
            createAccount(accounts);
        }
        else if (choice == 2) {
            if (login(accounts)) {
                cout << "Welcome to the system!\n";
            }
        }
        else if (choice == 3) {
            cout << "Exiting the program.\n";
            break;
        }
    }

    return 0;
}