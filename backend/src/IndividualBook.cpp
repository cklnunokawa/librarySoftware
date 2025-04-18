#include "../include/IndividualBook.h"
#include "../include/Book.h"
#include <iostream>

using std::cout;
using std::endl;

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

string IndividualBook::getCheckedOutBy() const {
    return checkedOutBy;
}

void IndividualBook::setStatus(BookStatus newStatus) {
    status = newStatus;
}

void IndividualBook::setNotes(const string& newNote) {
    notes = newNote;
}

bool IndividualBook::isAvailable() const {
    return status == BookStatus::Available;
}

bool IndividualBook::checkOutToUser(const string& userId) {
    if (status == BookStatus::CheckedOut ||
        status == BookStatus::Damaged) {
        return false;
    }

    // Even if the book is marked as lost, we allow checkout if it "reappears"
    status = BookStatus::CheckedOut;
    checkedOutBy = userId;
    return true;
}

bool IndividualBook::returnFromUser() {
    bool wasCheckedOut = !checkedOutBy.empty();

    if (status == BookStatus::Available && !wasCheckedOut) {
        // Nothing to return
        return false;
    }

    // Clear user link no matter what
    checkedOutBy.clear();

    // If damaged, leave it marked damaged
    if (status == BookStatus::Damaged) {
        return true;
    }

    // If lost, it's now found and available again
    if (status == BookStatus::Lost) {
        status = BookStatus::Available;
        return true;
    }

    // If it was checked out, make it available again
    if (status == BookStatus::CheckedOut) {
        status = BookStatus::Available;
        return true;
    }

    return false; // fallback
}

void IndividualBook::markLost() {
    status = BookStatus::Lost;
}

void IndividualBook::markDamaged() {
    status = BookStatus::Damaged;
}
