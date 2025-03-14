#ifndef UTILS_H
#define UTILS_H

#include <string>
std::string hashPassword(const std::string& password);
std::string generateRandomPassword(int length = 12);

#endif