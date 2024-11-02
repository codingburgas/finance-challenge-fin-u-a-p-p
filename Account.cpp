#include "Account.h"
#include "Color.h"
#include <iostream>

void createAccount(std::unordered_map<std::string, std::string>& accounts) {
    std::string username, password;
    setColor(YELLOW);
    std::cout << "Enter a new username: ";
    setColor(RESET);
    std::cin >> username;

    if (accounts.find(username) != accounts.end()) {
        setColor(RED);
        std::cout << "Username already exists. Try a different one.\n";
        setColor(RESET);
        return;
    }

    setColor(YELLOW);
    std::cout << "Enter a new password: ";
    setColor(RESET);
    std::cin >> password;
    accounts[username] = password;

    setColor(GREEN);
    std::cout << "Account created successfully!\n";
    setColor(RESET);
}

bool login(const std::unordered_map<std::string, std::string>& accounts) {
    std::string username, password;
    setColor(YELLOW);
    std::cout << "Enter username: ";
    setColor(RESET);
    std::cin >> username;
    setColor(YELLOW);
    std::cout << "Enter password: ";
    setColor(RESET);
    std::cin >> password;

    if (accounts.find(username) != accounts.end() && accounts.at(username) == password) {
        setColor(GREEN);
        std::cout << "Login successful! Welcome, " << username << "!\n";
        setColor(RESET);
        return true;
    }
    else {
        setColor(RED);
        std::cout << "Invalid username or password.\n";
        setColor(RESET);
        return false;
    }
}
