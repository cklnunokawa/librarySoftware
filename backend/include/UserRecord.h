#ifndef USERRECORD_H
#define USERRECORD_H

#include <string>
#include <optional>
#include "DateTime.h"

using std::string;
using std::optional;

class UserRecord {
public:
    // Constructor
    UserRecord(const string& UserId,
               const DateTime& checkoutDate,
               const DateTime& dueDate,
               const string& notes = "");

    // Getters
    string getUserId() const { return userID; }
    DateTime getCheckoutDate() const { return checkoutDate; }
    DateTime getDueDate() const { return dueDate; }
    optional<DateTime> getReturnDate() const { return returnDate; }
    string getNotes() const { return notes; }

    // Setters
    void setNotes(const string& note) { notes = note; }
    void setDueDate(DateTime dueDateStr) { dueDate = dueDateStr; }
    void setReturnDate(const DateTime& returnDateStr) { returnDate = returnDateStr; }

    // Status methods
    void markReturned(const string& returnDate);
    bool isReturned() const;

private:
    string userID;
    DateTime checkoutDate;
    DateTime dueDate;
    optional<DateTime> returnDate;
    string notes;
};

#endif


