// main.cpp
#include <iostream>
#include "Library.h"
#include "AdminUser.h"
#include "PatronUser.h"

int main() {
    Library library;

    // === Add Users ===
    library.addUser(std::make_unique<AdminUser>("admin001", "Alice Admin"));
    library.addUser(std::make_unique<PatronUser>("user123", "Bob Patron"));

    // === Add a Book ===
    Book book("9780141439518", "Pride and Prejudice", "Jane Austen", "Fiction");
    library.addBook(book);
    library.addCopyToBook("9780141439518", "BC001"); // barcode

    // === Checkout ===
    bool checkoutSuccess = library.checkoutBook("user123", "BC001", "2025-05-01 12:00:00");
    std::cout << (checkoutSuccess ? "Checkout successful.\n" : "Checkout failed.\n");

    // === Return ===
    bool returnSuccess = library.returnBook("user123", "BC001", "2025-04-20 10:30:00");
    std::cout << (returnSuccess ? "Return successful.\n" : "Return failed.\n");

    // === Search Tests ===
    std::cout << "\n=== Lookup Book by Title ===\n";
    auto books = library.getBooksByTitle("Pride and Prejudice");
    for (const auto& b : books) {
        std::cout << b->getTitle() << " by " << b->getAuthor() << "\n";
    }

    std::cout << "\n=== Lookup User by Name ===\n";
    User* user = library.getUserByName("Bob Patron");
    if (user) {
        std::cout << "Found user: " << user->getName() << " (" << user->getUserId() << ")\n";
    }

    return 0;
}
