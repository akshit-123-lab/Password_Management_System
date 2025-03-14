#include <iostream>
#include "password_manager.h"
#include "auth.h"
#include "encryption.h"
#include "utils.h"

using namespace std;

int main() {
    int choice;
    cout << "1. Login\n";
    cout << "2. Reset Master Password\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 2) {
        if (forgotMasterPassword()) {
            cout << "Master password has been reset. Please restart the program.\n";
            return 0;
        } else {
            cout << "Master password reset canceled.\n";
            return 1;
        }
    }

    if (!authenticateUser()) {
        return 1;
    }

    unordered_map<string, string> passwords = loadPasswords();
    unsigned char key[KEY_SIZE], iv[IV_SIZE];
    generateKeyIV(key, iv);
    
    while (true) {
        cout << "\nPassword Manager\n";
        cout << "1. Add Password\n";
        cout << "2. Retrieve Password\n";
        cout << "3. Edit Password\n";
        cout << "4. Delete Password\n";
        cout << "5. List Stored Sites\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                addPassword(passwords, key, iv);
                break;
            case 2:
                retrievePassword(passwords, key, iv);
                break;
            case 3:
                editPassword(passwords, key, iv);
                break;
            case 4:
                deletePassword(passwords);
                break;
            case 5:
                listPasswords(passwords);
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
