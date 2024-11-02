#include "DataAnalysis.h"
#include <iostream>

void dataAnalysis() {
    double calendar[12][31] = { 0 };
    calendar[11][27] = 5;
    calendar[11][28] = 6;
    calendar[11][29] = 7;
    calendar[11][30] = 9;

    std::cout << "\n--- Data Analysis ---\n";
    std::cout << "Sample data for December:\n";

    for (int i = 27; i <= 30; i++) {
        std::cout << "December " << i + 1 << ": " << calendar[11][i] << " units\n";
    }

    std::cout << "Data analysis completed. Press Enter to return to the main menu.\n";
    std::cin.ignore();
    std::cin.get();
}
