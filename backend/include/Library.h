// Library.h
#ifndef LIBRARY_H
#define LIBRARY_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "User.h"
#include "AdminUser.h"
#include "PatronUser.h"
#include "Book.h"
#include "IndividualBook.h"
#include "BookRecord.h"

class Library {
private:
    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::unordered_map<std::string, Book> booksByISBN;
    std::unordered_map<std::string, IndividualBook*> copiesByBarcode;

    // Additional exact-match maps
    std::unordered_map<std::string, std::string> userNameToId;
    std::unordered_map<std::string, std::vector<std::string>> titleToISBNs;

public:
    // User management
    void addUser(std::unique_ptr<User> user);
    User* getUser(const std::string& userId);
    User* getUserByName(const std::string& name);

    // Book management
    void addBook(const Book& book);
    Book* getBookByISBN(const std::string& isbn);
    std::vector<Book*> getBooksByTitle(const std::string& title);
    IndividualBook* getBookByBarcode(const std::string& barcode);

    // Copy management
    void addCopyToBook(const std::string& isbn, const std::string& barcode);

    // Checkout / return
    bool checkoutBook(const std::string& userId, const std::string& barcode, const std::string& dueDate);
    bool returnBook(const std::string& userId, const std::string& barcode, const std::string& returnDate);
};

#endif


