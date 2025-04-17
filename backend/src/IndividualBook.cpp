#include "../include/IndividualBook.h"
#include "../include/Book.h"

IndividualBook::IndividualBook(const string& barcode, const Book* parentBook, BookStatus status)
    : barcode(barcode), status(status), parentBook(parentBook) {}

string IndividualBook::getBarcode() const {
    return barcode;
}

BookStatus IndividualBook::getStatus() const {
    return status;
}

string IndividualBook::getNotes() const {
    return notes;
}

const Book* IndividualBook::getBook() const {
    return parentBook;
}

void IndividualBook::setStatus(BookStatus newStatus) {
    status = newStatus;
}

void IndividualBook::setNotes(const string& newNote) {
    notes = newNote;
}
