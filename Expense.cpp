#include "Expense.h"
#include <iostream>
#include <iomanip>

void addExpense(std::vector<Expense>& expenses) {
    std::string description;
    double amount;
    char deductible;
    std::cout << "Enter expense description: ";
    std::cin.ignore();
    getline(std::cin, description);
    std::cout << "Enter expense amount: ";
    std::cin >> amount;
    std::cout << "Is this expense tax-deductible? (y/n): ";
    std::cin >> deductible;
    expenses.push_back({ description, amount, deductible == 'y' || deductible == 'Y' });
}

double calculateDeductibleExpenses(const std::vector<Expense>& expenses) {
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

void displayExpenses(const std::vector<Expense>& expenses) {
    std::cout << "\nList of Expenses:\n";
    std::cout << std::setw(30) << std::left << "Description" << std::setw(10) << "Amount(LV)" << std::setw(15) << "Tax Deductible" << "\n";
    std::cout << "-------------------------------------------------------\n";
    for (const auto& expense : expenses) {
        std::cout << std::setw(30) << expense.description << std::setw(10) << expense.amount << std::setw(15) << (expense.isTaxDeductible ? "Yes" : "No") << "\n";
    }
}
