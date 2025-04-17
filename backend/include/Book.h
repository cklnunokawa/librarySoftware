#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "IndividualBook.h"

using std::string;
using std::vector;

class Book {
private:
    string isbn;
    string title;
    string author;
    string genre;
    vector<IndividualBook> copies;

public:
    Book(const string& isbn, const string& title, const string& author, const string& genre);

    // Getters
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    // Add both versions to support read-only and mutable access:
    const std::vector<IndividualBook>& getCopies() const; // for const contexts
    std::vector<IndividualBook>& getCopies();             // for modification


    // Methods
    void addCopy(const string& barcode);
    int getAvailableCount() const;
};

#endif
