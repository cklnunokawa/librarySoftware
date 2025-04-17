#ifndef BOOKRECORD_H
#define BOOKRECORD_H

#include <string>
#include <optional>
#include "DateTime.h"

using std::string;
using std::optional;

class BookRecord {
public:
    // Constructor
    BookRecord(const string& bookId,
               const string& titleSnapshot,
               const string& checkoutDate,
               const string& dueDate,
               const string& notes = "");

    // Getters
    string getBookId() const { return bookId; }
    string getTitleSnapshot() const { return titleSnapshot; }
    DateTime getCheckoutDate() const { return checkoutDate; }
    DateTime getDueDate() const { return dueDate; }
    optional<DateTime> getReturnDate() const { return returnDate; }
    string getNotes() const { return notes; }

    // Setters
    void setNotes(const string& note) { notes = note; }
    void setDueDate(DateTime dueDateStr) { dueDate = dueDateStr; }

    // Status methods
    void markReturned(const string& returnDate);
    bool isReturned() const;

private:
    string bookId;
    string titleSnapshot;
    DateTime checkoutDate;
    DateTime dueDate;
    optional<DateTime> returnDate;
    string notes;
};

#endif


