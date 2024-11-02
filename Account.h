
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <unordered_map>
#include <string>

void createAccount(std::unordered_map<std::string, std::string>& accounts);
bool login(const std::unordered_map<std::string, std::string>& accounts);

#endif