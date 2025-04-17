#ifndef PATRONUSER_H
#define PATRONUSER_H

#include "User.h"

class PatronUser : public User {
private:
public:
    PatronUser(const std::string& userId, const std::string& name);
    std::string getRole() const override { return "Patron"; }

};

#endif
