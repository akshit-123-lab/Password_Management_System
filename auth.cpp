#include "auth.h"
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"

const std::string USER_FILE = "user.dat";

bool authenticateUser() {
    std::ifstream file(USER_FILE);
    std::string storedHash, inputPassword;
    
    if (!file) {
        resetMasterPassword();
        return true;
    }
    
    getline(file, storedHash);
    file.close();
    
    std::cout << "Enter master password: ";
    getline(std::cin, inputPassword);
    
    return hashPassword(inputPassword) == storedHash;
}

void resetMasterPassword() {
    std::string inputPassword;
    std::cout << "Resetting master password. Enter a new password: ";
    getline(std::cin, inputPassword);
    
    std::ofstream outFile(USER_FILE);
    outFile << hashPassword(inputPassword);
    outFile.close();
    std::cout << "Master password reset successfully!\n";
}

bool forgotMasterPassword() {
    char choice;
    std::cout << "WARNING: Resetting the master password will delete all stored passwords!\n";
    std::cout << "Do you want to continue? (y/n): ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        std::remove(USER_FILE.c_str());
        std::remove("passwords.dat"); // Deletes stored passwords
        resetMasterPassword();
        return true;
    }
    return false;
}
