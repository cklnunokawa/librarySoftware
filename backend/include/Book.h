#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "IndividualBook.h"

using std::string;
using std::vector;

class Book {
private:
    string isbn; // ISBN number
    string title; // Title of the book
    string author; // Author of the book
    string genre; // Genre of the book
    vector<IndividualBook> copies; // Copies of the book

public:
    Book(const string& isbn,
        const string& title,
        const string& author,
        const string& genre);

    // Getters
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    // Add both versions to support read-only and mutable access:
    const vector<IndividualBook>& getCopies() const; // for const contexts
    vector<IndividualBook>& getCopies();             // for modification
    int getTotalCopies() const;


    // Methods
    void addCopy(const string& barcode); // Adds a new copy to the book
    int getAvailableCount() const; // Returns the number of available copies
    void printInfo() const; // Prints book information
    string Book::statusToString(BookStatus status) const; // Helper function to convert status to string
};

#endif
