#include "../include/Library.h"
#include <iostream>

using std::cout;
using std::cin;

void showMenu() {
    cout << "\nLibrary System Menu:\n";
    cout << "1. Add User\n";
    cout << "2. Add Book (or Add Copy)\n";
    cout << "3. Add Copy to Existing Book\n";
    cout << "4. Check Out Book\n";
    cout << "5. Return Book\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Library lib;
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(); // discard newline from input buffer

        switch (choice) {
            case 1:
                lib.promptAddUser();
                break;
            case 2:
                lib.promptAddBook();
                break;
            case 3:
                lib.promptAddCopy();
                break;
            case 4:
                lib.promptCheckoutBook();
                break;
            case 5:
                lib.promptReturnBook();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
