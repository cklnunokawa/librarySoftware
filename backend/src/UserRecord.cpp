#include "../include/UserRecord.h"

// BookRecord class implementation
UserRecord::UserRecord(const string& UserId,
    const DateTime& checkoutDate,
    const DateTime& dueDate,
    const string& notes = "")
    : userID(UserId),
      checkoutDate(checkoutDate),
      dueDate(dueDate),
      notes(notes) 
      {

}


// Status methods
void UserRecord::markReturned(const string& returnDate){
    this->returnDate = DateTime(returnDate);
}
bool UserRecord::isReturned() const{
    return returnDate.has_value();

}