#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class PasswordManager {
private:
    string filename = "data.txt";
    string key = "securekey";

    string encryptDecrypt(string data) {
        for (int i = 0; i < data.size(); i++)
            data[i] = data[i] ^ key[i % key.size()];
        return data;
    }

public:
    void addAccount() {
        string website, username, password;

        cout << "Enter Website: ";
        cin >> website;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << encryptDecrypt(website) << " "
                << encryptDecrypt(username) << " "
                << encryptDecrypt(password) << endl;
            file.close();
            cout << "Account Saved Successfully!\n";
        }
        else {
            cout << "Error opening file.\n";
        }
    }

    void viewAccounts() {
        ifstream file(filename);
        string website, username, password;

        if (file.is_open()) {
            while (file >> website >> username >> password) {
                cout << "Website: " << encryptDecrypt(website)
                    << " | Username: " << encryptDecrypt(username)
                    << " | Password: " << encryptDecrypt(password)
                    << endl;
            }
            file.close();
        }
        else {
            cout << "No data found.\n";
        }
    }
};

int main() {
    PasswordManager pm;
    int choice;

    while (true) {
        cout << "\n--- Secure Password Manager ---\n";
        cout << "1. Add Account\n";
        cout << "2. View Accounts\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            pm.addAccount();
            break;
        case 2:
            pm.viewAccounts();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}