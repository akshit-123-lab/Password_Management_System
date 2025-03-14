#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

const int KEY_SIZE = 32;
const int IV_SIZE = 16;

void generateKeyIV(unsigned char* key, unsigned char* iv);
std::string encryptPassword(const std::string& password, unsigned char* key, unsigned char* iv);
std::string decryptPassword(const std::string& encrypted, unsigned char* key, unsigned char* iv);

#endif