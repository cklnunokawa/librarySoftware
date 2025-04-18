#include "../include/Library.h"
#include "../include/User.h"
#include "../include/AdminUser.h"
#include "../include/PatronUser.h"
#include "../include/Book.h"
#include "../include/IndividualBook.h"
#include "../include/BookRecord.h"
#include "../include/DateTime.h"
#include <iostream>

using std::cout;
using std::cin;
using std::streamsize;
using std::numeric_limits;
using std::make_unique;

void Library::promptAddUser() {
    int userType;
    while (true) {
        cout << "\nWhat type of user would you like to add?\n";
        cout << "1. Patron\n";
        cout << "2. Admin\n";
        cout << "Enter your choice: ";

        if (cin >> userType && (userType == 1 || userType == 2)) {
            cin.ignore();
            break;
        } else {
            cout << "Invalid input. Please enter 1 for Patron or 2 for Admin.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string id, name;
    cout << "Enter user ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter user name: ";
    getline(cin, name);

    if (userType == 1) {
        if (addUser(make_unique<PatronUser>(id, name))) {
            cout << "Patron user added successfully.\n";
        } else {
            cout << "User with ID already exists.\n";
        }
    } else {
        if (addUser(make_unique<AdminUser>(id, name))) {
            cout << "Admin user added successfully.\n";
        } else {
            cout << "User with ID already exists.\n";
        }
    }
}

void Library::promptAddBook() {
    string isbn, title, author, genre, barcode;

    cout << "Enter Book ISBN: ";
    getline(cin, isbn);

    cout << "Enter Barcode for this specific copy: ";
    getline(cin, barcode);

    auto bookIt = booksByISBN.find(isbn);
    if (bookIt != booksByISBN.end()) {
        if (copiesByBarcode.find(barcode) != copiesByBarcode.end()) {
            cout << "Barcode already exists.\n";
        } else {
            addCopyToBook(isbn, barcode);
            cout << "Added new copy to existing book.\n";
        }
    } else {
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Genre: ";
        getline(cin, genre);

        Book newBook(isbn, title, author, genre);
        addBook(newBook);
        addCopyToBook(isbn, barcode);
        cout << "New book and copy added successfully.\n";
    }
}

void Library::promptAddCopy() {
    string isbn, barcode;
    cout << "Enter ISBN of the book to add a copy to: ";
    getline(cin, isbn);

    cout << "Enter new barcode for the copy: ";
    getline(cin, barcode);

    if (copiesByBarcode.find(barcode) != copiesByBarcode.end()) {
        cout << "Barcode already exists.\n";
        return;
    }

    if (booksByISBN.find(isbn) == booksByISBN.end()) {
        cout << "Book with given ISBN not found.\n";
        return;
    }

    addCopyToBook(isbn, barcode);
    cout << "Copy added successfully.\n";
}

void Library::promptCheckoutBook() {
    string userId, barcode, dueDate;

    cout << "Enter User ID: ";
    cin.ignore();
    getline(cin, userId);

    cout << "Enter Book Barcode: ";
    getline(cin, barcode);

    while (true) {
        cout << "Enter Due Date (YYYY-MM-DD HH:MM:SS): ";
        getline(cin, dueDate);
        if (DateTime::isValidDateTimeFormat(dueDate)) break;
        cout << "Invalid date format. Please use YYYY-MM-DD HH:MM:SS.\n";
    }

    if (!getUser(userId)) {
        cout << "No user found with ID: " << userId << "\n";
        return;
    }
    if (!getBookByBarcode(barcode)) {
        cout << "No book copy found with barcode: " << barcode << "\n";
        return;
    }

    if (checkoutBook(userId, barcode, dueDate)) {
        cout << "Book checked out successfully.\n";
    } else {
        cout << "Failed to check out book. It may already be checked out or unavailable.\n";
    }
}

void Library::promptReturnBook() {
    string barcode, returnDate;

    cout << "Enter Book Barcode: ";
    cin.ignore();
    getline(cin, barcode);

    while (true) {
        cout << "Enter Return Date (YYYY-MM-DD HH:MM:SS): ";
        getline(cin, returnDate);
        if (DateTime::isValidDateTimeFormat(returnDate)) break;
        cout << "Invalid date format. Please use YYYY-MM-DD HH:MM:SS.\n";
    }

    if (!getBookByBarcode(barcode)) {
        cout << "No book found with that barcode.\n";
        return;
    }

    if (returnBook(barcode, returnDate)) {
        cout << "Book returned successfully.\n";
    } else {
        cout << "Return failed. Book may not be checked out.\n";
    }
}

bool Library::addUser(std::unique_ptr<User> user) {
    const std::string& id = user->getUserId();
    if (users.find(id) != users.end()) return false;
    userNameToId[user->getName()] = id;
    users[id] = std::move(user);
    return true;
}

void Library::addBook(const Book& book) {
    const std::string& isbn = book.getISBN();
    if (booksByISBN.find(isbn) == booksByISBN.end()) {
        booksByISBN.insert({ isbn, book });
        titleToISBNs[book.getTitle()].push_back(isbn);
    }
}

User* Library::getUser(const std::string& userId) {
    auto it = users.find(userId);
    return (it != users.end()) ? it->second.get() : nullptr;
}

User* Library::getUserByName(const std::string& name) {
    auto it = userNameToId.find(name);
    return (it != userNameToId.end()) ? getUser(it->second) : nullptr;
}

Book* Library::getBookByISBN(const std::string& isbn) {
    auto it = booksByISBN.find(isbn);
    return (it != booksByISBN.end()) ? &(it->second) : nullptr;
}

std::vector<Book*> Library::getBooksByTitle(const std::string& title) {
    std::vector<Book*> results;
    auto it = titleToISBNs.find(title);
    if (it != titleToISBNs.end()) {
        for (const auto& isbn : it->second) {
            Book* book = getBookByISBN(isbn);
            if (book) results.push_back(book);
        }
    }
    return results;
}

IndividualBook* Library::getBookByBarcode(const std::string& barcode) {
    auto it = copiesByBarcode.find(barcode);
    return (it != copiesByBarcode.end()) ? it->second : nullptr;
}

void Library::addCopyToBook(const std::string& isbn, const std::string& barcode) {
    auto it = booksByISBN.find(isbn);
    if (it != booksByISBN.end()) {
        it->second.addCopy(barcode);
        IndividualBook& newCopy = it->second.getCopies().back();
        copiesByBarcode[barcode] = &newCopy;
    } else {
        std::cerr << "Book with ISBN " << isbn << " not found.";
    }
}

bool Library::checkoutBook(const std::string& userId, const std::string& barcode, const std::string& dueDate) {
    User* user = getUser(userId);
    IndividualBook* copy = getBookByBarcode(barcode);
    if (!user || !copy) return false;

    if (!copy->checkOutToUser(userId)) return false;

    const Book* book = copy->getBook();
    BookRecord record(barcode, book->getTitle(), DateTime::now().toString(), dueDate);
    user->checkoutBook(record);

    return true;
}

bool Library::returnBook(const std::string& barcode, const std::string& returnDate) {
    IndividualBook* copy = getBookByBarcode(barcode);
    if (!copy) return false;

    std::string userId = copy->getCheckedOutBy();
    if (userId.empty()) return false;

    User* user = getUser(userId);
    if (!user) return false;

    if (!copy->returnFromUser()) return false;

    user->returnBook(barcode, returnDate);
    return true;
}
