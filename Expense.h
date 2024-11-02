#ifndef EXPENSE_H
#define EXPENSE_H

#include <vector>
#include <string>

struct Expense {
    std::string description;
    double amount;
    bool isTaxDeductible;
};

void addExpense(std::vector<Expense>& expenses);
double calculateDeductibleExpenses(const std::vector<Expense>& expenses);
double calculateTax(double income, double deductibleExpenses, double taxRate);
void displayExpenses(const std::vector<Expense>& expenses);

#endif

