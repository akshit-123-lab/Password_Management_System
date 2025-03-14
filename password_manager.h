#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <iostream>
#include <unordered_map>
#include "encryption.h"
#include "utils.h"

using namespace std;

void addPassword(unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv);
void retrievePassword(const unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv);
void editPassword(unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv);
void deletePassword(unordered_map<string, string>& passwords);
void listPasswords(const unordered_map<string, string>& passwords);
unordered_map<string, string> loadPasswords();
void savePasswords(const unordered_map<string, string>& passwords);

#endif