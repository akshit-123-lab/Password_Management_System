#include "password_manager.h"
#include <fstream>

const string DATA_FILE = "passwords.dat";

unordered_map<string, string> loadPasswords() {
    unordered_map<string, string> passwords;
    ifstream file(DATA_FILE);
    string site, password;
    while (file >> site >> password) {
        passwords[site] = password;
    }
    return passwords;
}

void savePasswords(const unordered_map<string, string>& passwords) {
    ofstream file(DATA_FILE, ios::binary);
    for (const auto& pair : passwords) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
}

void addPassword(unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv) {
    string site, password;
    cout << "Enter site: ";
    getline(cin, site);
    
    cout << "Do you want to generate a strong password? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        password = generateRandomPassword();
        cout << "Generated Password: " << password << "\n";
    } else {
        cout << "Enter password: ";
        getline(cin, password);
    }
    
    passwords[site] = encryptPassword(password, key, iv);
    savePasswords(passwords);
    cout << "Password saved!\n";
}

void retrievePassword(const unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv) {
    string site;
    cout << "Enter site: ";
    getline(cin, site);
    if (passwords.find(site) != passwords.end()) {
        cout << "Password: " << decryptPassword(passwords.at(site), key, iv) << "\n";
    } else {
        cout << "No password found for this site.\n";
    }
}

void editPassword(unordered_map<string, string>& passwords, unsigned char* key, unsigned char* iv) {
    string site, newPassword;
    cout << "Enter site to edit password: ";
    getline(cin, site);
    
    if (passwords.find(site) == passwords.end()) {
        cout << "No password found for this site.\n";
        return;
    }
    
    cout << "Enter new password: ";
    getline(cin, newPassword);
    passwords[site] = encryptPassword(newPassword, key, iv);
    savePasswords(passwords);
    cout << "Password updated successfully!\n";
}

void deletePassword(unordered_map<string, string>& passwords) {
    string site;
    cout << "Enter site to delete: ";
    getline(cin, site);
    if (passwords.erase(site)) {
        savePasswords(passwords);
        cout << "Password deleted successfully.\n";
    } else {
        cout << "No password found for this site.\n";
    }
}

void listPasswords(const unordered_map<string, string>& passwords) {
    cout << "Stored Sites:\n";
    for (const auto& pair : passwords) {
        cout << "- " << pair.first << "\n";
    }
}
