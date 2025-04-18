#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <chrono>

using std::string;
using std::chrono::system_clock;


class DateTime {
private:
    system_clock::time_point timePoint;

public:
    DateTime();  // Defaults to now()
    DateTime(const string& datetimeStr);  // From "YYYY-MM-DD HH:MM:SS" converts to DateTime
    static DateTime now();

    string toString() const; // Converts DateTime to "YYYY-MM-DD HH:MM:SS"
    bool isBefore(const DateTime& other) const; // Compares if this DateTime is before another
    bool isAfter(const DateTime& other) const; // Compares if this DateTime is after another
    static bool isValidDateTimeFormat(const std::string& dateTime); // Validates the format
};
#endif
