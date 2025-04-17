// Library.cpp
#include "../include/Library.h"
#include <iostream>

void Library::addUser(std::unique_ptr<User> user) {
    userNameToId[user->getName()] = user->getUserId();
    users[user->getUserId()] = std::move(user);
}

User* Library::getUser(const std::string& userId) {
    auto it = users.find(userId);
    return (it != users.end()) ? it->second.get() : nullptr;
}

User* Library::getUserByName(const std::string& name) {
    auto it = userNameToId.find(name);
    if (it != userNameToId.end()) {
        return getUser(it->second);
    }
    return nullptr;
}

void Library::addBook(const Book& book) {
    booksByISBN[book.getISBN()] = book;
    titleToISBNs[book.getTitle()].push_back(book.getISBN());
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
        std::cerr << "Book with ISBN " << isbn << " not found.\n";
    }
}

bool Library::checkoutBook(const std::string& userId, const std::string& barcode, const std::string& dueDate) {
    User* user = getUser(userId);
    IndividualBook* copy = getBookByBarcode(barcode);
    if (!user || !copy || copy->getStatus() != BookStatus::Available) return false;

    const Book* book = copy->getBook();
    copy->setStatus(BookStatus::CheckedOut);

    BookRecord record(barcode, book->getTitle(), DateTime::now().toString(), dueDate);
    user->checkoutBook(record);
    return true;
}

bool Library::returnBook(const std::string& userId, const std::string& barcode, const std::string& returnDate) {
    User* user = getUser(userId);
    IndividualBook* copy = getBookByBarcode(barcode);
    if (!user || !copy || copy->getStatus() != BookStatus::CheckedOut) return false;

    user->returnBook(barcode, returnDate);
    copy->setStatus(BookStatus::Available);
    return true;
}
