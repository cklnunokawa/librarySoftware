#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"

class AdminUser : public User {
public:
    // Constructor
    AdminUser(const string& userId, const string& name);
    
    //return role
    string getRole() const override { return "Admin"; }

    // Admin-specific methods
    void addBookToLibrary(); // Add a book to the library
    void removeBookFromLibrary(); // Remove a book from the library
    void addUser(); // Add a new user to the library
    void removeUser(); // Remove a user from the library
};

#endif
