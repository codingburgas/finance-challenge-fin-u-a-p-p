#ifndef COLOR_H
#define COLOR_H

#include <iostream>

// Function to set text color
inline void setColor(const std::string& colorCode) {
    std::cout << colorCode;
}

// Color Codes
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

#endif
#pragma once
