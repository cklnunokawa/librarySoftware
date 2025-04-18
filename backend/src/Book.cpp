#include "../include/Book.h"
#include <iostream>

using std::cout;


Book::Book(const std::string& isbn,
    const std::string& title,
    const std::string& author,
    const std::string& genre)
: isbn(isbn), title(title), author(author), genre(genre) {}

string Book::getISBN() const {
    return isbn;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getGenre() const {
    return genre;
}

const std::vector<IndividualBook>& Book::getCopies() const {
    return copies;
}

std::vector<IndividualBook>& Book::getCopies() {
    return copies;
}


void Book::addCopy(const string& barcode) {
    copies.emplace_back(barcode, this);
}

int Book::getAvailableCount() const {
    int count = 0;
    for (const auto& copy : copies) {
        if (copy.getStatus() == BookStatus::Available) {
            count++;
        }
    }
    return count;
}



string Book::statusToString(BookStatus status) const {
    switch (status) {
        case BookStatus::Available: return "Available";
        case BookStatus::CheckedOut: return "Checked Out";
        case BookStatus::Lost: return "Lost";
        case BookStatus::Reserved: return "Reserved";
        default: return "Unknown";
    }
}

void Book::printInfo() const {
    cout << "Book Title: " << title << "\n"
         << "Author: " << author << "\n"
         << "Genre: " << genre << "\n"
         << "ISBN: " << isbn << "\n"
         << "Total Copies: " << copies.size() << "\n"
         << "Available: " << getAvailableCount() << "\n";

    cout << "Copies:\n";
    for (const auto& copy : copies) {
        cout << "  Barcode: " << copy.getBarcode()
             << " | Status: " << statusToString(copy.getStatus());

        const std::string& userId = copy.getCheckedOutBy();
        if (!userId.empty()) {
            cout << " | Checked out by: " << userId;
        }
        if (!copy.getNotes().empty()) {
            cout << " | Notes: " << copy.getNotes();
        }

        cout << "\n";
    }
}
