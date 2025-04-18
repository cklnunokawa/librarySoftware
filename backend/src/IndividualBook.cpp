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

bool IndividualBook::checkOutToUser(const string& userId, const DateTime& checkoutDate, const DateTime& dueDate) {
    if (status == BookStatus::CheckedOut || status == BookStatus::Damaged) {
        return false;
    }

    if (!checkedOutBy.empty()) {
        cout << "Error: Book already has a checkedOutBy value." << endl;
        return false;
    }

    status = BookStatus::CheckedOut;
    checkedOutBy = userId;

    userRecords.emplace_back(userId, checkoutDate, dueDate);
    return true;
}


bool IndividualBook::returnFromUser(const DateTime& returnDate) {
    if (checkedOutBy.empty()) {
        cout << "Error: Book is not currently checked out by any user." << endl;
        return false;
    }

    if (userRecords.empty()) {
        cout << "Error: No checkout record found for this book." << endl;
        return false;
    }

    UserRecord& lastRecord = userRecords.back();

    if (lastRecord.getUserId() != checkedOutBy) {
        cout << "Error: Mismatch between last record and current checked out user." << endl;
        return false;
    }

    if (lastRecord.isReturned()) {
        cout << "Warning: Book already marked as returned in latest record." << endl;
        return false;
    }

    lastRecord.setReturnDate(returnDate);
    checkedOutBy.clear();

    if (status == BookStatus::Lost || status == BookStatus::CheckedOut) {
        status = BookStatus::Available;
    }

    return true;
}


void IndividualBook::markLost() {
    status = BookStatus::Lost;
}

void IndividualBook::markDamaged() {
    status = BookStatus::Damaged;
}
