#include "../include/Book.h"


Book::Book(const string& isbn, const string& title, const string& author, const string& genre)
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
  