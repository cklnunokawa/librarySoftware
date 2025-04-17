#ifndef INDIVIDUALBOOK_H
#define INDIVIDUALBOOK_H

#include <string>
#include "BookStatus.h"

class Book;  // Forward declaration

using std::string;

class IndividualBook {
private:
    string barcode;
    BookStatus status;
    string notes;
    const Book* parentBook;  // Link to owning book metadata

public:
    IndividualBook(const string& barcode, const Book* parentBook, BookStatus status = BookStatus::Available);

    // Getters
    string getBarcode() const;
    BookStatus getStatus() const;
    string getNotes() const;
    const Book* getBook() const;

    // Setters
    void setStatus(BookStatus newStatus);
    void setNotes(const string& newNote);
};

#endif
