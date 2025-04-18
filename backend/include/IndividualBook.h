#ifndef INDIVIDUALBOOK_H
#define INDIVIDUALBOOK_H

#include <string>
#include "BookStatus.h"
#include "UserRecord.h"
#include <vector>

class Book;  // Forward declaration

using std::string;

class IndividualBook {
private:
    string barcode;
    BookStatus status;
    string notes;
    const Book* parentBook;  // Link to owning book metadata
    string checkedOutBy;  // User ID of the person who checked it out
    vector<UserRecord> userRecords;  // History of checkouts and returns

public:
    IndividualBook(const string& barcode, const Book* parentBook, BookStatus status = BookStatus::Available);

    // Getters
    string getBarcode() const;
    BookStatus getStatus() const;
    bool isAvailable() const;
    string getNotes() const;
    const Book* getBook() const;
    string getCheckedOutBy() const;
    const vector<UserRecord>& getRecords() const { return userRecords; };

    // Setters
    void setStatus(BookStatus newStatus);
    void setNotes(const string& newNote);
    void setCheckedOutBy(const string& userId);
    bool returnFromUser(const DateTime& returnDate);
    bool IndividualBook::checkOutToUser(const string& userId, const DateTime& checkoutDate, const DateTime& dueDate) ;
    void markLost();
    void markDamaged();
};

#endif
