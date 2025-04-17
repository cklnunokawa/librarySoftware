#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "BookRecord.h"

using std::string;
using std::vector;

class User {
protected:
    string userId;
    string name;
    vector<BookRecord> currentCheckouts;
    vector<BookRecord> borrowHistory;

public:
    User(const string& userId, const string& name);

    // Virtual destructor for inheritance
    virtual ~User() = default;

    // Role-based support
    virtual string getRole() const { return "User"; }

    // Getters
    string getUserId() const;
    string getName() const;
    const vector<BookRecord>& getCurrentCheckouts() const;
    const vector<BookRecord>& getBorrowHistory() const;

    // Setters
    void setUserId(const string& id);
    void setName(const string& name);

    // Book actions
    virtual void checkoutBook(const BookRecord& record);
    virtual void returnBook(const string& bookId, const string& returnDate);

    void listCurrentCheckouts() const;
    void listBorrowHistory() const;
};

#endif
