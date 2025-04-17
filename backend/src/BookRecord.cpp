#include "../include/BookRecord.h"

// BookRecord class implementation
BookRecord::BookRecord(const string& bookId,
                       const string& titleSnapshot,
                       const string& checkoutDate,
                       const string& dueDate,
                       const string& notes)
    : bookId(bookId),
      titleSnapshot(titleSnapshot),
      checkoutDate(DateTime(checkoutDate)),
      dueDate(DateTime(dueDate)),
      notes(notes) {}

// Mark the book as returned with the return date
void BookRecord::markReturned(const string& returnDateStr) {
    returnDate = DateTime(returnDateStr);
}

// Check if the book has been returned
bool BookRecord::isReturned() const {
    return returnDate.has_value();
}
