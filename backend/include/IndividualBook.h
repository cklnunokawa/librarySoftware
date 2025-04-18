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
    string checkedOutBy;  // User ID of the person who checked it out

public:
    IndividualBook(const string& barcode, const Book* parentBook, BookStatus status = BookStatus::Available);

    // Getters
    string getBarcode() const;
    BookStatus getStatus() const;
    bool isAvailable() const;
    string getNotes() const;
    const Book* getBook() const;
    string getCheckedOutBy() const;

    // Setters
    void setStatus(BookStatus newStatus);
    void setNotes(const string& newNote);
    void setCheckedOutBy(const string& userId);
    bool returnFromUser();
    bool checkOutToUser(const string& userId);
    void markLost();
    void markDamaged();
};

#endif
