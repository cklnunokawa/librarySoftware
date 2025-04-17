#include "../include/DateTime.h"
#include <iomanip>
#include <sstream>

using std::istringstream;
using std::ostringstream;
using std::put_time;
using std::get_time;

// DateTime class implementation
DateTime::DateTime() {
    timePoint = system_clock::now();
}

// Constructor that takes a string in the format "YYYY-MM-DD HH:MM:SS"
DateTime::DateTime(const string& datetimeStr) {
    tm tm = {};
    istringstream ss(datetimeStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (ss.fail()) {
        timePoint = system_clock::now(); // fallback
    } else {
        time_t timeT = mktime(&tm);
        timePoint = system_clock::from_time_t(timeT);
    }
}

// Static method to get the current date and time
DateTime DateTime::now() {
    return DateTime();
}

// Converts the DateTime object to a string in the format "YYYY-MM-DD HH:MM:SS"
string DateTime::toString() const {
    time_t timeT = system_clock::to_time_t(timePoint);
    ostringstream ss;
    ss << put_time(localtime(&timeT), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Check if this DateTime is before another DateTime
bool DateTime::isBefore(const DateTime& other) const {
    return timePoint < other.timePoint;
}

// Check if this DateTime is after another DateTime
bool DateTime::isAfter(const DateTime& other) const {
    return timePoint > other.timePoint;
}
