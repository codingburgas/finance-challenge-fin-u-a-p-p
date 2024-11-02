#include "FinancialQuiz.h"
#include "Color.h"
#include <iostream>

void financialQuiz() {
    int score = 0;
    std::string answer;

    setColor(CYAN);
    std::cout << "\n--- Financial Quiz ---\n" << RESET;

    // Array of questions
    std::string questions[] = {
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

    // Loop through the questions
    for (int i = 0; i < 10; ++i) {
        setColor(YELLOW);  // Set question color
        std::cout << questions[i] << " (often/rarely): ";
        setColor(RESET);  // Reset to default color

        std::cin >> answer;

        // Validate the answer and adjust the score
        if (answer == "often" || answer == "Often") {
            score++;
        }
        else if (answer != "rarely" && answer != "Rarely") {
            setColor(RED);  // Set error message color
            std::cout << "Invalid answer. Please enter 'often' or 'rarely'.\n";
            setColor(RESET);  // Reset to default color
            i--;  // Repeat the current question
        }
    }

    // Provide feedback based on the score
    setColor(CYAN);
    std::cout << "\n--- Quiz Feedback ---\n" << RESET;

    if (score >= 8) {
        setColor(RED);  // High-risk financial habits
        std::cout << "You have many habits that could harm your financial stability. "
            << "Consider making changes to improve your financial habits.\n";
    }
    else if (score >= 5) {
        setColor(YELLOW);  // Medium-risk financial habits
        std::cout << "You have some good financial habits, but there’s room for improvement. "
            << "Try to minimize impulsive spending and increase savings.\n";
    }
    else {
        setColor(GREEN);  // Good financial habits
        std::cout << "Great job! You have strong financial habits. Keep it up!\n";
    }

    setColor(CYAN);
    std::cout << "Quiz completed. Press Enter to return to the main menu.\n" << RESET;
    std::cin.ignore();  // Clear the newline character from the input buffer
    std::cin.get();     // Wait for the user to press Enter
}
