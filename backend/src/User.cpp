#include "../include/User.h"
#include <iostream>

//create a new user
// User constructor
User::User(const string& userId, const string& name)
    : userId(userId), name(name) {}

// User methods
// Check out a book and add it to the current checkouts
void User::checkoutBook(const BookRecord& record) {
    //adds to current checkouts
    currentCheckouts.push_back(record);
    //adds to borrow history to allow for all time tracking
    borrowHistory.push_back(record);  // Track all-time history
}

// Return a book and update the current checkouts
void User::returnBook(const string& bookId, const string& returnDate) {
    // Find and remove from currentCheckouts
    for (auto it = currentCheckouts.begin(); it != currentCheckouts.end(); ++it) {
        if (it->getBookId() == bookId) {
            it->markReturned(returnDate);
            currentCheckouts.erase(it);  // ✅ Remove it from current list
            break;
        }
    }

    // Also mark as returned in borrowHistory
    for (BookRecord& record : borrowHistory) {
        if (record.getBookId() == bookId && !record.isReturned()) {
            record.markReturned(returnDate);
            break;
        }
    }
}


// List currently checked out books
void User::listCurrentCheckouts() const {
    std::cout << "Currently checked out by " << name << ":\n";
    for (const auto& record : currentCheckouts) {
        std::cout << " - " << record.getBookId() << " (Due: " << record.getDueDate().toString() << ")\n";
    }
}

// List all borrow history
void User::listBorrowHistory() const {
    std::cout << "Borrow history for " << name << ":\n";
    for (const auto& record : borrowHistory) {
        std::cout << " - " << record.getBookId() 
                  << " (Checked out: " << record.getCheckoutDate().toString()
                  << ", Returned: " << (record.isReturned() ? record.getReturnDate()->toString() : "Not returned")
                  << ")\n";
    }
}

void User::printInfo() {
    std::cout << "User ID: " << userId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Role: " << getRole() << "\n";
    std::cout << "Current Checkouts:\n";
    listCurrentCheckouts();
    std::cout << "Borrow History:\n";
    listBorrowHistory();
}

